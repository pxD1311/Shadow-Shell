#include "../unix_os_funcs.h"

int main(int argc, char *argv[])
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
            printf("\n\nfile <%s>\n", argv[i]);
            if(!display_file(argv[i]))
                printf("Error : printing file %s.\n", argv[i]);
        }
        return 0;
    }
    display_error(L"Error : no file name as given.");
    return 1;
}