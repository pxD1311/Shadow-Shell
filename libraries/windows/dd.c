#include "../win_os_funcs.h"

int wmain(int argc, wchar_t* argv[])
{
    if(argc == 1)
        display_list_dir(L".");
    else
        display_list_dir(argv[1]);
    return 0;
}
