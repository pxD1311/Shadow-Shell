#include "shell.h"

int mainloop(OS_CMDS *commands)
{
    char command[10];
    char* input;
    while(1)
    {
        if (scanf("%s", command) != 1)
        {
            raise_invalid_input_error();
            continue;
        }
        input = user_input();
        
        if (command == CMD_PRINT_CWD)
        {
            printf(">>> ");
            if(!execute_no_arg_command(commands->print_current_dir)){
                raise_command_failed_error();
                continue;
            }
        }
    }
}

void display_opening_text()
{
    printf("\nStarting <SHADOW-SHELL> (Version : %s)\n", VERSION);
}

void display_opening_text()
{
    printf("\nClosing  <SHADOW-SHELL> (Version : %s)\n", VERSION);
}