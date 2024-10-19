#include "shell.h"

#if defined(_WIN32) || defined(_WIN64)
    #define CURRENT_OS WIN
#elif defined(__APPLE__) && defined(__MACH__)
    #define CURRENT_OS APPLE
#elif defined(__linux__)
    #define CURRENT_OS LINUX
#else
    #define CURRENT_OS INVALID
#endif

int main(int argc, char *argv[])
{
    display_author();

    char *EXE_FILE_PATH = argv[0];
    int COMMAND_PATH_LEN = strlen(EXE_FILE_PATH) - strlen("\\shadowShell.exe");

    char *COMMAND_PATH = (char*)malloc(COMMAND_PATH_LEN + 1);
    if (COMMAND_PATH == NULL)
        return 1;

    strncpy(COMMAND_PATH, EXE_FILE_PATH, COMMAND_PATH_LEN);
    COMMAND_PATH[COMMAND_PATH_LEN] = '\0';

    switch(CURRENT_OS)
    {
        case WIN:
            wchar_t* WIN_COMMANDS_PATH = char_to_wchar(COMMAND_PATH);
            win_shell(WIN_COMMANDS_PATH);
            free(WIN_COMMANDS_PATH);
            break;

        //to be implemented
        case LINUX:
        case APPLE:
            unix_shell();
            break;

        case INVALID:
        default:
            display_error(L"Invalid Operating System.");
            quit();
            break;
    }

    return 0;
}