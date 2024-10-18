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

int main()
{
    display_author();

    switch(CURRENT_OS)
    {
        case WIN:
            win_shell();
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