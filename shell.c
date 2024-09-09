#include "shell.h"

void mainloop(OS_CMDS *commands)
{
    char command[10];
    char* input;
    while(1)
    {
        printf("<<< ");
        if (scanf("%s", command) != 1)
        {
            raise_invalid_input_error();
            continue;
        }
        input = user_input();
        
        if (!strcmp(command, CMD_PRINT_CWD))
        {
            printf(">>> ");
            if(execute_no_arg_command(commands->print_current_dir)){
                raise_command_failed_error();
            }
        }
        else if(!strcmp(command, CMD_CHANGE_DIR))
        {
            if(execute_arg_command(commands->change_dir, input)){
                raise_command_failed_error();
            }
        }
        else if(!strcmp(command, CMD_MAKE_DIR))
        {
            if(execute_arg_command(commands->create_dir, input)){
                raise_command_failed_error();
            }
        }
        else if(!strcmp(command, CMD_MAKE_FILE))
        {
            if(execute_arg_command(commands->create_file, input)){
                raise_command_failed_error();
            }
        }
        else if(!strcmp(command, CMD_RM_FILE))
        {
            if(execute_arg_command(commands->rm_file, input)){
                raise_command_failed_error();
            }
        }
        else if(!strcmp(command, CMD_RM_FILE))
        {
            if(execute_arg_command(commands->rm_dir, input)){
                raise_command_failed_error();
            }
        }
        else if(!strcmp(command, CMD_QUIT))
        {
            quit_shell();
        }
        else
        {
            raise_command_not_found_error();
        }
    }
}

void display_opening_text()
{
    printf("\nStarting <SHADOW-SHELL> (Version : %s)\n", VERSION);
}

void display_closing_text()
{
    printf("\nClosing  <SHADOW-SHELL> (Version : %s)\n", VERSION);
}