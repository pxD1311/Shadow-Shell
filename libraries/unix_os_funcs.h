#pragma once

#define _GNU_SOURCE

#include <time.h>
#include <wchar.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <errno.h>
#include <ftw.h>
#include <linux/limits.h>

#include "../config/config.h"
#include "common_funcs.h"

typedef const int BOOL;

struct FTW;

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

typedef struct
{
    char *name;
    unsigned char is_directory;
    off_t size;
    time_t created_time;
    time_t last_accessed;
    time_t last_modified;
} DirItem;

char *get_cwd();
void display_cwd();
BOOL set_cwd(const char *path);

BOOL is_path_valid(const char *path);

BOOL get_dir_items(const char *search_path, int *objects, int *files, int *dirs);
void display_list_dir(const char *path);
void FileTimeToString(time_t file_time, char *buffer, size_t buffer_size);
DIR *open_dir(const char *search_path);
DirItem **get_list_dir(const char *search_path);
void free_list_dir(DirItem **list);

BOOL create_file(const char *path);
BOOL create_directory(const char *path);

BOOL copy_file(const char *source_path, const char *destination_path);
BOOL move_file(const char *source_path, const char *destination_path);
BOOL display_file(const char *path);
BOOL display_file_word_num(const char *path);
BOOL remove_file(const char *path);

BOOL copy_dir(const char *source_path, const char *destination_path);
BOOL move_dir(const char *source_path, const char *destination_path);
static int unlink_callback(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf);
BOOL remove_dir(const char *path);

int clear_screen();