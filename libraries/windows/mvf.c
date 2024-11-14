#include "../win_os_funcs.h"

int wmain(int argc, wchar_t *argv[])
{
    if (argc >= 3)
    {
        if (!is_path_valid(argv[1]))
        {
            display_error(L"Invalid Path.");
            return 1;
        }

        if( move_file(argv[1], argv[2]))
        {
            wprintf(L"Successfully moved <%ls> to <%ls>.\n", argv[1], argv[2]);
            return 0;
        }
    }
    display_error(L"Failed to move file.");
    return 1;
}
