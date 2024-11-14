#include "win_os_funcs.h"

// returns current working directory.
wchar_t *get_cwd()
{
    unsigned long buffer_size = MAX_PATH;
    wchar_t *buffer = (wchar_t *)malloc(buffer_size * sizeof(wchar_t));
    if (buffer == NULL)
        return (wchar_t *)NULL;
    if (GetCurrentDirectoryW(buffer_size, buffer) == 0)
    {
        free(buffer);
        return (wchar_t *)NULL;
    }
    return buffer;
}

// displays current working directory.
void display_cwd()
{
    wchar_t *cwd = get_cwd();
    // NULL is used to indicate that get_cwd function failed.
    if (cwd == NULL)
    {
        display_error(L"Failed to get current working directory.\n");
        return;
    }
    wprintf(L">>> %ls\n", cwd);
    free(cwd);
}

// checks if a path is valid in windows or not
BOOL is_path_valid(const wchar_t *path)
{
    return (GetFileAttributesW(path) != INVALID_FILE_ATTRIBUTES);
}

// sets current working directory to the given path
BOOL set_cwd(const wchar_t *path) {
    if (!is_path_valid(path)) {
        wprintf(L"Invalid path: <%ls>\n", path);
        return FALSE;
    }

    if (!SetCurrentDirectoryW(path)) {
        unsigned long error = GetLastError();
        wprintf(L"Command failed. Error code: %lu\n", error);

        if (error == ERROR_FILE_NOT_FOUND) {
            display_error(L"Directory not found.\n");
        } else if (error == ERROR_ACCESS_DENIED) {
            display_error(L"Access denied.\n");
        } else {
            display_error(L"Unknown error.\n");
        }
        return FALSE;
    }

    return TRUE;
}

// gets total number of items/objects, directoriesand files in a given directory,
BOOL get_dir_items(const wchar_t *search_path, int *objects, int *files, int *dirs)
{
    // contains information about a file like creation time, name, etc..
    WIN32_FIND_DATAW file_data_obj;

    // adding a wildcard "\*" so that all files in a folder are searched.
    wchar_t path[MAX_PATH];
    _snwprintf(path, MAX_PATH, L"%s\\*", search_path);

    // creating a process to iterate over a directory.
    HANDLE handle_find = FindFirstFileW(path, &file_data_obj);

    // if process fails then raising error
    if (handle_find == INVALID_HANDLE_VALUE)
    {
        wchar_t error[MAX_PATH];
        _snwprintf(error, MAX_PATH, L"Invalid Path: %s", path);
        display_error(error);
        return FALSE;
    }

    // iterating over the given directry to count the items
    do
    {
        // checking if the object is a file
        if (!(file_data_obj.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
            (*files)++;
        (*objects)++;
    } while (FindNextFileW(handle_find, &file_data_obj) != 0);

    *dirs = *objects - *files;
    FindClose(handle_find);
    return TRUE;
}

// to get a list of items in the given path
WIN32_FIND_DATAW **get_list_dir(const wchar_t *search_path)
{
    int objects = 0, files = 0, dirs = 0;

    // if the function fails raising error (already done in the prev function)
    if (get_dir_items(search_path, &objects, &files, &dirs) == FALSE)
    {
        return (WIN32_FIND_DATAW **)NULL;
    }

    // Allocating memory for the directory entries
    WIN32_FIND_DATAW **dir = (WIN32_FIND_DATAW **)malloc(sizeof(WIN32_FIND_DATAW *) * objects);
    if (dir == NULL)
    {
        display_error(L"Memory Allocation Error.");
        return (WIN32_FIND_DATAW **)NULL;
    }

    for (int i = 0; i < objects; i++)
    {
        dir[i] = (WIN32_FIND_DATAW *)malloc(sizeof(WIN32_FIND_DATAW));
        // freeing the allocated memory in case the memory is not enough for further indexes and raising error
        if (dir[i] == NULL)
        {
            display_error(L"Memory Allocation Error.");
            for (int j = 0; j < i; j++)
                free(dir[j]);
            free(dir);
            return (WIN32_FIND_DATAW **)NULL;
        }
    }

    // adding wildcard "\*" to path
    wchar_t path[MAX_PATH];
    _snwprintf(path, MAX_PATH, L"%s\\*", search_path);

    // creating process to get info about directory items
    HANDLE handle_find = FindFirstFileW(path, dir[0]);
    if (handle_find == INVALID_HANDLE_VALUE)
    {
        wchar_t error[MAX_PATH];
        _snwprintf(error, MAX_PATH, L"Invalid Path: %s", path);
        display_error(error);

        // freeing the allocated memory and raising error
        for (int i = 0; i < objects; i++)
            free(dir[i]);
        free(dir);
        return (WIN32_FIND_DATAW **)NULL;
    }

    // adding directory details into the array
    int i = 1;
    while (i < objects && FindNextFileW(handle_find, dir[i]) != 0)
    {
        i++;
    }
    // ending the process
    FindClose(handle_find);
    return dir;
}

void display_list_dir(const wchar_t *path)
{
    WIN32_FIND_DATAW **dir = get_list_dir(path);
    int objs = 0, files = 0, dirs = 0;
    get_dir_items(path, &objs, &files, &dirs);

    wprintf(L">>> Dir : <%ls>\n", path);
    for (int i = 0; i < objs; i++)
    {
        if (dir[i] != NULL && dir[i]->cFileName != NULL)
            wprintf(L"%d - %ls\n", i, dir[i]->cFileName);
    }
    printf("FILES : %d    DIRECTORIES : %d    TOTAL : %d\n", files, dirs, objs);
}

// creates a file in the given path
BOOL create_file(const wchar_t *path)
{
    FILE *fptr = _wfopen(path, L"w");
    if (fptr == NULL)
        return FALSE;
    fclose(fptr);
    return TRUE;
}

// creates a directory in the given path
BOOL create_directory(const wchar_t *path)
{
    return CreateDirectoryW(path, NULL);
}

// clear terminal screen
BOOL clear_screen()
{
    return system("cls");
}

BOOL copy_file(const wchar_t *source_path, const wchar_t *destination_path)
{
    FILE *fptr_s = _wfopen(source_path, L"r");
    FILE *fptr_d = _wfopen(destination_path, L"w");
    if (fptr_s == NULL || fptr_d == NULL)
    {
        if (fptr_s != NULL)
            fclose(fptr_s);
        if (fptr_d != NULL)
        {
            remove_file(destination_path);
            fclose(fptr_d);
        }
        return FALSE;
    }
    wchar_t chr;

    while ((chr = getwc(fptr_s)) != WEOF)
    {
        if (putwc(chr, fptr_d) == WEOF)
        {
            fclose(fptr_s);
            fclose(fptr_d);
            remove_file(destination_path);
            return FALSE;
        }
    }
    fclose(fptr_s);
    fclose(fptr_d);
    return TRUE;
}

BOOL move_file(const wchar_t *source_path, const wchar_t *destination_path)
{
    if (copy_file(source_path, destination_path) == TRUE)
        return remove_file(source_path);
    return FALSE;
}

BOOL remove_file(const wchar_t *path)
{
    return DeleteFileW(path);
}

BOOL copy_dir(const wchar_t *source_path, const wchar_t *destination_path)
{
    int files = 0, dirs = 0, objs = 0;
    get_dir_items(source_path, &objs, &files, &dirs);
    WIN32_FIND_DATAW **dir = get_list_dir(source_path);

    if(!is_path_valid(destination_path))
        if (create_directory(destination_path) == FALSE)
            return FALSE;

    for (int i = 0; i < objs; i++)
    {
        if (dir[i] != NULL && dir[i]->cFileName != NULL)
        {
            // Skipping "." and ".." as it will copy everything everywhere if not skipped
            if (wcscmp(dir[i]->cFileName, L".") == 0 || wcscmp(dir[i]->cFileName, L"..") == 0)
            {
                continue;
            }

            // making a new path to each file/sub-dir in the source dir
            wchar_t full_source_path[MAX_PATH];
            wcscpy(full_source_path, source_path);
            wcscat(full_source_path, L"\\");
            wcscat(full_source_path, dir[i]->cFileName);

            // making a new path to each file/sub-dir in the destination dir
            wchar_t full_destination_path[MAX_PATH];
            wcscpy(full_destination_path, destination_path);
            wcscat(full_destination_path, L"\\");
            wcscat(full_destination_path, dir[i]->cFileName);

            // file
            if (!(dir[i]->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
            {
                if (copy_file(full_source_path, full_destination_path) == FALSE)
                {
                    wprintf(L">-< Failed to copy file <%ls> to <%ls>.\n", full_source_path, full_destination_path);
                }
            }
            // sub-directory
            else
            {
                if (copy_dir(full_source_path, full_destination_path) == FALSE)
                {
                    wprintf(L">-< Failed to move directory <%ls> to <%ls>.\n", full_source_path, full_destination_path);
                }
            }
        }
    }

    for (int i = 0; i < objs; i++)
        free(dir[i]);
    free(dir);

    return TRUE;
}

BOOL move_dir(const wchar_t *source_path, const wchar_t *destination_path)
{
    if (copy_dir(source_path, destination_path) == TRUE)
        return remove_dir(source_path);
    return FALSE;
}

BOOL remove_dir(const wchar_t *path)
{
    int files = 0, dirs = 0, objs = 0;
    get_dir_items(path, &objs, &files, &dirs);
    WIN32_FIND_DATAW **dir = get_list_dir(path);

    for (int i = 0; i < objs; i++)
    {
        if (dir[i] != NULL && dir[i]->cFileName != NULL)
        {
            // Skipping "." and ".." as it will destroy everything if not skipped
            if (wcscmp(dir[i]->cFileName, L".") == 0 || wcscmp(dir[i]->cFileName, L"..") == 0)
            {
                continue;
            }

            // making a new path to each file/sub-dir in the dir
            wchar_t fullPath[MAX_PATH];
            wcscpy(fullPath, path);
            wcscat(fullPath, L"\\");
            wcscat(fullPath, dir[i]->cFileName);

            // file
            if (!(dir[i]->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
            {
                if (remove_file(fullPath) == FALSE)
                {
                    wprintf(L">-< Failed to remove file <%ls>.\n", fullPath);
                }
            }
            // sub-directory
            else
            {
                if (remove_dir(fullPath) == FALSE)
                {
                    wprintf(L">-< Failed to remove directory <%ls>.\n", fullPath);
                }
            }
        }
    }

    for (int i = 0; i < objs; i++)
        free(dir[i]);
    free(dir);

    return RemoveDirectoryW(path);
}

BOOL display_file(const wchar_t *path)
{
    FILE *fptr = _wfopen(path, L"r");
    if(fptr == NULL)
        return FALSE;

    wchar_t chr;
    while ((chr = getwc(fptr)) != WEOF)
    {
        if (wprintf(L"%lc", chr) < 0)
        {
            fclose(fptr);
            return FALSE;
        }
    }
    printf("\n\n");
    fclose(fptr);
    return TRUE;
}

BOOL display_file_word_num(const wchar_t *path)
{
    FILE *fptr = _wfopen(path, L"r");
    if(fptr == NULL)
        return FALSE;

    wchar_t chr;
    int buff_len = 0;
    while ((chr = getwc(fptr)) != WEOF)
    {
        buff_len++;
    }

    rewind(fptr);
    wchar_t* buffer = (wchar_t*)malloc((buff_len+1)*sizeof(wchar_t));

    if(buffer == NULL)
    {
        display_error(L"Insufficient memory.");
        fclose(fptr);
        return FALSE;
    }

    for (int i = 0; (chr = getwc(fptr)) != WEOF; i++)
        buffer[i] = chr;

    buffer[buff_len] = '\0';

    wprintf(L"%d words/tokens in the file <%ls>.\n", count_word_num(buffer), path);
    free(buffer);
    fclose(fptr);
    return TRUE;
}