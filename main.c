#include "shell.h"

int main(int argc, char *argv[])
{
    display_author();

    char *FILE_PATH = argv[0];

#if defined(_WIN32) || defined(_WIN64)
    int COMMAND_PATH_LEN = strlen(FILE_PATH) - strlen("\\shadowShell.exe");
#elif (defined(__APPLE__) && defined(__MACH__)) || defined(__linux__)
    int COMMAND_PATH_LEN = strlen(FILE_PATH) - strlen("\\shadowShell");
#else
    display_error(L"Invalid Operating System.");
    quit();
#endif

    char *COMMAND_PATH = (char *)malloc(COMMAND_PATH_LEN + 1);
    if (COMMAND_PATH == NULL)
    {
        display_error(L"Invalid command path.");
        return 1;
    }
    strncpy(COMMAND_PATH, FILE_PATH, COMMAND_PATH_LEN);
    COMMAND_PATH[COMMAND_PATH_LEN] = '\0';

#if defined(_WIN32) || defined(_WIN64)
    wchar_t *WIN_COMMANDS_PATH = char_to_wchar(COMMAND_PATH);
    win_shell(WIN_COMMANDS_PATH);
#elif (defined(__APPLE__) && defined(__MACH__)) || defined(__linux__)
    char *UNIX_COMMANDS_PATH = COMMAND_PATH;
    unix_shell(COMMAND_PATH);
#endif

    free(COMMAND_PATH);
    return 0;
}