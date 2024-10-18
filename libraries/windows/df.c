#include "../win_os_funcs.h"

int wmain(int argc, wchar_t* argv[])
{
    if(argc >= 2)
    {
        for (int i = 1; i < argc; i++)
        {
            if (!is_path_valid(argv[i]))
            {
                display_error(L"Invalid Path.");
                continue;
            }
            wprintf(L"file <%ls>\n", argv[i]);
            if(!display_file(argv[i]))
                wprintf(L"Error %lu : printing file %ls.\n", GetLastError(), argv[i]);
        }
        return 0;
    }
    display_error(L"Error : no file name as given.");
    return 1;
} 
