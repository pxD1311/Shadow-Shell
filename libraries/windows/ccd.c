#include "../win_os_funcs.h"

int wmain(int argc, wchar_t* argv[])
{
    if (argc >= 2){
        if (!is_path_valid(argv[1]))
            return 1;
        return !set_cwd(argv[1]);
    }
    return 0;
} 
