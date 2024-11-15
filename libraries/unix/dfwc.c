#include "../unix_os_funcs.h"

int main(int argc, char *argv[])
{
    if(argc >= 2)
    {
        for(int i = 1; i < argc; i++)
            if (!display_file_word_num(argv[i]))
                printf("Error : failed to display file<%s>\n", argv[i]);
    }
    printf("Error : no files provided.\n");
    return 0;
}