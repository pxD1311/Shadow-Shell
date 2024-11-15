#include "../unix_os_funcs.h"

int main(int argc, char *argv[])
{
    if (argc >= 3)
    {
        if (!is_path_valid(argv[1]))
        {
            display_error(L"Invalid Path.");
            return 1;
        }
        if( copy_dir(argv[1], argv[2]) == TRUE )
        {
            printf("Successfully moved <%s> to <%s>.\n", argv[1], argv[2]);
            return 0;
        }
    }
    display_error(L"Failed to copy directory.");
    return 1;
}