#include "../unix_os_funcs.h"

int main(int argc, char *argv[])
{
    if (argc >= 2)
    {
        for (int i = 1; i < argc; i++)
        {
            if (create_directory(argv[i]) == FALSE)
                printf("ERROR : Failed to create directory %s\n", argv[i]);
        }
        return 0;
    }
    return 1;
}