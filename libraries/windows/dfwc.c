#include "../win_os_funcs.h"

int wmain(int argc, wchar_t* argv[])
{
    if(argc >= 2)
    {
        for(int i = 1; i < argc; i++)
            if (!display_file_word_num(argv[i]))
            {
                wprintf(L"Error : failed to display file<%ls>\n", argv[i]);
            }
    }
    wprintf(L"Error %lu : no files provided.\n");
    return 0;
}
