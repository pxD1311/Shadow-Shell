#include "../unix_os_funcs.h"

int main(int argc, char *argv[])
{
    if(argc == 1)
        display_list_dir(".");
    else
        display_list_dir(argv[1]);
    return 0;
}


