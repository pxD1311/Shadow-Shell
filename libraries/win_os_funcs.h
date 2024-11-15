#pragma once

#include <windows.h>
#include "../config/config.h"
#include "common_funcs.h"

wchar_t *get_cwd();
void display_cwd();
BOOL set_cwd(const wchar_t *path);

BOOL is_path_valid(const wchar_t *path);

BOOL get_dir_items(const wchar_t *search_path, int *objects, int *files, int *dirs);
WIN32_FIND_DATAW **get_list_dir(const wchar_t *search_path);
void FileTimeToString(FILETIME *ft, wchar_t *buffer, size_t bufferSize);
void display_list_dir(const wchar_t *path);

BOOL create_file(const wchar_t *path);
BOOL create_directory(const wchar_t *path);

BOOL copy_file(const wchar_t *source_path, const wchar_t *destination_path);
BOOL move_file(const wchar_t *source_path, const wchar_t *destination_path);
BOOL display_file(const wchar_t *path);
BOOL display_file_word_num(const wchar_t *path);
BOOL remove_file(const wchar_t *path);

BOOL copy_dir(const wchar_t *source_path, const wchar_t *destination_path);
BOOL move_dir(const wchar_t *source_path, const wchar_t *destination_path);
BOOL remove_dir(const wchar_t *path);

int clear_screen();