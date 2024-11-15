#include "unix_os_funcs.h"

char *get_cwd()
{
    char *cwd = (char *)malloc(PATH_MAX);
    if (cwd == NULL)
    {
        display_error(L"Memory allocation failed for current working directory.\n");
        return NULL;
    }

    if (getcwd(cwd, PATH_MAX) == NULL)
    {
        display_error(L"Can't get current working directory.\n");
        free(cwd);
        return NULL;
    }

    return cwd;
}

void display_cwd()
{
    char *cwd = get_cwd();
    if (cwd == NULL)
    {
        display_error(L"Failed to get current working directory.\n");
        return;
    }

    printf(">>> %s\n", cwd);
    free(cwd);
}

BOOL set_cwd(const char *path)
{
    if (chdir(path) != 0)
    {
        display_error(L"Failed to change current working directory.");
        return FALSE;
    }
    return TRUE;
}

BOOL is_path_valid(const char *path)
{
    return !access(path, F_OK);
}

BOOL get_dir_items(const char *search_path, int *objects, int *files, int *dirs)
{
    *objects = *files = *dirs = 0;
    DIR *dir = opendir(search_path);
    if (dir == NULL)
    {
        display_error(L"Can't get directory items.");
        return 0;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_type == DT_DIR)
        {
            (*dirs)++;
        }
        else if (entry->d_type == DT_REG)
        {
            (*files)++;
        }
        (*objects)++;
    }
    closedir(dir);
    return 1;
}

DIR *open_dir(const char *search_path)
{
    DIR *dir = opendir(search_path);
    if (dir == NULL)
    {
        perror("opendir");
        return NULL;
    }
    return dir;
}

DirItem **get_list_dir(const char *search_path)
{
    DIR *dir = open_dir(search_path);
    if (dir == NULL)
    {
        return NULL;
    }

    DirItem **list = malloc(sizeof(DirItem *) * 100); // Allocating space for 100 entries (adjust as needed)
    if (!list)
    {
        perror("malloc");
        closedir(dir);
        return NULL;
    }

    struct dirent *entry;
    int i = 0;
    while ((entry = readdir(dir)) != NULL)
    {
        // Ignore the "." and ".." directories
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }

        DirItem *item = malloc(sizeof(DirItem));
        if (!item)
        {
            perror("malloc");
            closedir(dir);
            free(list);
            return NULL;
        }

        item->name = strdup(entry->d_name);
        item->is_directory = (entry->d_type == DT_DIR);

        list[i++] = item;
    }
    list[i] = NULL; // Null-terminate the list

    closedir(dir);
    return list;
}

void free_list_dir(DirItem **list)
{
    if (list)
    {
        for (int i = 0; list[i] != NULL; i++)
        {
            free(list[i]->name);
            free(list[i]);
        }
        free(list);
    }
}

void FileTimeToString(time_t file_time, char *buffer, size_t buffer_size)
{
    struct tm *time_info = localtime(&file_time);
    strftime(buffer, buffer_size, "%Y-%m-%d %H:%M:%S", time_info);
}

void display_list_dir(const char *path)
{
    DIR *dir = opendir(path);
    if (dir == NULL)
    {
        perror("Error opening directory");
        return;
    }

    struct dirent *entry;
    struct stat file_stat;
    DirItem *dir_list = malloc(sizeof(DirItem) * 100); // Memory for 100 items
    int count = 0;

    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char full_path[512];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        if (stat(full_path, &file_stat) == -1)
        {
            perror("Error getting file stats");
            continue;
        }

        dir_list[count].name = strdup(entry->d_name);
        dir_list[count].is_directory = S_ISDIR(file_stat.st_mode);
        dir_list[count].size = S_ISDIR(file_stat.st_mode) ? 0 : file_stat.st_size;
        dir_list[count].created_time = file_stat.st_ctime;
        dir_list[count].last_accessed = file_stat.st_atime;
        dir_list[count].last_modified = file_stat.st_mtime;

        count++;
    }

    closedir(dir);

    printf("%-4s | %-30s | %-10s | %-15s | %-20s | %-20s | %-20s\n",
           "Index", "Name", "Type", "Size", "Created", "Last Accessed", "Last Modified");
    printf("-----------------------------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++)
    {
        char created_str[20], last_accessed_str[20], last_modified_str[20];

        FileTimeToString(dir_list[i].created_time, created_str, sizeof(created_str));
        FileTimeToString(dir_list[i].last_accessed, last_accessed_str, sizeof(last_accessed_str));
        FileTimeToString(dir_list[i].last_modified, last_modified_str, sizeof(last_modified_str));

        printf("%-5d | %-30s | %-10s | %-9ld bytes | %-20s | %-20s | %-20s\n",
               i,
               dir_list[i].name,
               dir_list[i].is_directory ? "Directory" : "File",
               dir_list[i].size,
               created_str,
               last_accessed_str,
               last_modified_str);

        free(dir_list[i].name); // Freeing dynamically allocated memory
    }

    free(dir_list);
}

BOOL create_file(const char *path)
{
    FILE *file = fopen(path, "w");
    if (file == NULL)
    {
        display_error(L"Can't create file.");
        return FALSE;
    }
    fclose(file);
    return TRUE;
}

BOOL create_directory(const char *path)
{
    if (!mkdir(path, 0755))
    {
        display_error(L"Can't create directory.");
        return FALSE;
    }
    return TRUE;
}

BOOL copy_file(const char *source_path, const char *destination_path)
{
    FILE *src = fopen(source_path, "rb");
    FILE *dest = fopen(destination_path, "wb");
    if (src == NULL || dest == NULL)
    {
        if (src)
            fclose(src);
        if (dest)
            fclose(dest);
        perror("Error copying file");
        return FALSE;
    }

    char buffer[4096];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0)
    {
        if (fwrite(buffer, 1, bytes, dest) != bytes)
        {
            perror("Write error");
            fclose(src);
            fclose(dest);
            return FALSE;
        }
    }

    fclose(src);
    fclose(dest);
    return TRUE;
}

BOOL move_file(const char *source_path, const char *destination_path)
{
    if (copy_file(source_path, destination_path) == TRUE)
        return remove_file(source_path);
    return FALSE;
}

BOOL display_file(const char *path)
{
    FILE *fptr = fopen(path, "r");
    if (fptr == NULL)
        return FALSE;

    char chr;
    while ((chr = getc(fptr)) != EOF)
    {
        if (printf("%c", chr) < 0)
        {
            fclose(fptr);
            return FALSE;
        }
    }
    printf("\n\n");
    fclose(fptr);
    return TRUE;
}

BOOL display_file_word_num(const char *path)
{
    FILE *fptr = fopen(path, "r");
    if (fptr == NULL)
        return FALSE;

    char chr;
    int buff_len = 0;
    while ((chr = getc(fptr)) != EOF)
        buff_len++;

    rewind(fptr);
    char *buffer = (char *)malloc(buff_len + 1);

    if (buffer == NULL)
    {
        display_error(L"Insufficient memory.");
        fclose(fptr);
        return FALSE;
    }

    for (int i = 0; (chr = getc(fptr)) != EOF; i++)
        buffer[i] = chr;

    buffer[buff_len] = '\0';

    printf("%d words/tokens in the file <%s>.\n", count_word_num_char(buffer), path);
    free(buffer);
    fclose(fptr);
    return TRUE;
}

BOOL remove_file(const char *path)
{
    return !remove(path);
}

int copy_dir(const char *source_dir, const char *destination_dir)
{
    struct dirent *entry;
    DIR *dir = opendir(source_dir);

    if (!dir)
    {
        perror("opendir error");
        return -1;
    }

    // Create the destination directory if it doesn't exist
    if (mkdir(destination_dir, 0755) != 0 && errno != EEXIST)
    {
        perror("mkdir error");
        closedir(dir);
        return -1;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        // Skip the "." and ".." entries
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }

        char src_path[1024], dst_path[1024];
        snprintf(src_path, sizeof(src_path), "%s/%s", source_dir, entry->d_name);
        snprintf(dst_path, sizeof(dst_path), "%s/%s", destination_dir, entry->d_name);

        if (entry->d_type == DT_DIR)
        {
            // If it's a directory, copy recursively
            if (copy_dir(src_path, dst_path) != 0)
            {
                closedir(dir);
                return -1;
            }
        }
        else if (entry->d_type == DT_REG)
        {
            // If it's a regular file, copy it
            if (copy_file(src_path, dst_path) != 0)
            {
                closedir(dir);
                return -1;
            }
        }
    }

    closedir(dir);
    return 0;
}

int move_dir(const char *source_dir, const char *destination_dir)
{
    // Try to rename (move) the directory
    if (rename(source_dir, destination_dir) != 0)
    {
        perror("rename error");
        return -1; // In case of failure, manually copy and delete
    }
    return 0;
}

static int unlink_callback(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf)
{
    return (typeflag == FTW_D || typeflag == FTW_DP) ? rmdir(fpath) : unlink(fpath);
}

BOOL remove_dir(const char *path)
{
    return nftw(path, unlink_callback, 64, FTW_DEPTH | FTW_PHYS) == 0;
}

int clear_screen()
{
    return system("clear");
}