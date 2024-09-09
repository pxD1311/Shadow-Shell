#include "shell_funcs.h"

char* user_input()
{
    char* input = (char*)malloc(sizeof(char)*MAX_INPUT_LENGTH);
    if(input == NULL)
    {
        raise_insufficient_memory_error();
        return (char*)NULL;
    }
    printf("<<< ");
    if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL)
    {
        raise_invalid_input_error();
        free(input);
        return (char*)NULL;
    }
    int len = strlen(input);

    //removing '\n' if present in the input string
    if (len > 0 && input[len - 1] == '\n')
    {
        input[len - 1] = '\0';
    }
    return input;
}

int execute_no_arg_command(char* command)
{
    if (system(command) != 0)
    {
        raise_command_failed_error();
        return 1;
    }
    return 0;
}

int execute_arg_command(char* command, char* args)
{
    //+1 for space between command and arguement and +1 for null char
    int command_len = strlen(command) + strlen(args) + 2;
    char* create_command = (char*)malloc(command_len);
    if (create_command == NULL){
        raise_insufficient_memory_error();
        return 1;
    }
    strcpy(create_command, command);
    strcat(create_command, " ");
    strcat(create_command, args);
    if (system(create_command) != 0){
        raise_command_failed_error();
        free(create_command);
        return 1;
    }
    free(create_command);
    return 0;
}

void quit_shell()
{
    printf("ALERT : CLOSING the shell\n");
    exit(0);
}