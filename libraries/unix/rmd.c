#include "../unix_os_funcs.h"

int main(int argc, char *argv[])
{
    if(argc >= 2){
        for(int i = 1; i < argc; i++){
            if (argc >= 2)
            {
                if (!is_path_valid(argv[i]))
                    printf("Error : Invalid Path or directory doesnt exist.");
                else
                    remove_dir(argv[i]);
            }
        }
        return 0;
    }
    display_error(L"No directory was given to remove.");
    return 1;
}