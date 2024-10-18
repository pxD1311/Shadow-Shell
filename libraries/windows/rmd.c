#include "../win_os_funcs.h"

int wmain(int argc, wchar_t *argv[])
{
    for(int i = 1; i < argc; i++){
        if (argc >= 2)
        {
            if (!is_path_valid(argv[i]))
                wprintf(L"Error %lu : Invalid Path or directory doesnt exist.", GetLastError());
            remove_dir(argv[i]);
        }
    }
    display_error(L"No directory was given to remove.");
    return 1;
}

