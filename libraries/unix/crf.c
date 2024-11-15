#include "../unix_os_funcs.h"

int main(int argc, char *argv[])
{
    if (argc >= 2)
    {
        for (int i = 1; i < argc; i++)
        {
            if (create_file(argv[i]) == FALSE)
                printf("ERROR : Failed to create file %s\n", argv[i]);
            else
                printf("Successfully created file <%s>\n", argv[i]);
        }
        return 0;
    }
    return 1;
}
