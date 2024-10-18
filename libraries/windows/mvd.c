#include "../win_os_funcs.h"

int wmain(int argc, wchar_t* argv[])
{
    if (argc >= 3)
    {
        if (!is_path_valid(argv[1]) || !is_path_valid(argv[2]))
        {
            display_error(L"Invalid Path.");
            return 1;
        }
        return move_dir(argv[1], argv[2]);
    }
    display_error(L"Failed to move directory.");
    return 1;
} 
