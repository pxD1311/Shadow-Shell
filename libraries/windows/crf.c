#include "../win_os_funcs.h"

int wmain(int argc, wchar_t *argv[])
{
    if (argc >= 2)
    {
        for (int i = 1; i < argc; i++)
        {
            if (create_file(argv[i]) == FALSE)
                wprintf(L"ERROR %lu : Failed to create file %ls\n", GetLastError(), argv[i]);
            else
                wprintf(L"Successfully created file <%ls>\n", argv[i]);
        }
        return 0;
    }
    return 1;
}
