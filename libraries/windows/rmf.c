#include "../win_os_funcs.h"

int wmain(int argc, wchar_t *argv[])
{
    if(argc >= 2){
        for(int i = 1; i < argc; i++){
            if (argc >= 2)
            {
                if (!is_path_valid(argv[i]))
                    wprintf(L"Error %lu : Invalid Path or file doesnt exist.", GetLastError());
                else
                    remove_file(argv[i]);
            }
        }
        return 0;
    }
    display_error(L"No file was given to remove.");
    return 1;
}
