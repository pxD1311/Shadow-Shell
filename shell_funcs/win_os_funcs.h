#include <windows.h>
#include "../config/config.h"
#include "common_funcs.h"

wchar_t *get_cwd();
void display_cwd();
BOOL is_path_valid(const wchar_t *path);
BOOL set_cwd(const wchar_t *path);
BOOL get_dir_items(const wchar_t *search_path, int *objects, int *files, int *dirs);
WIN32_FIND_DATAW **get_list_dir(const wchar_t *search_path);
void display_list_dir(const wchar_t *path);
BOOL create_file(const wchar_t *path);
BOOL create_directory(const wchar_t *path);
int clear_screen();