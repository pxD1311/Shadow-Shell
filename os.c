#include "os.h"

enum OPERATING_SYSTEM getos()
{
#ifdef _WIN32
    return OS_WIN;
#elif __APPLE__
    return OS_APPLE;
#elif __linux__
    return OS_LINUX;
#else
    return OS_INVALID;
#endif
}

void initialize_shell_commands(OS_CMDS *cmd, enum OPERATING_SYSTEM OS)
{
    switch (OS)
    {
    case OS_WIN:
        cmd->print_current_dir = "dir";
        cmd->create_dir = "mkdir";
        cmd->change_dir = "cd";
        cmd->rm_file = "del";
        cmd->rm_dir = "rmdir";
        cmd->create_file = "copy nul";
        break;
    case OS_APPLE:
    case OS_LINUX:
        cmd->print_current_dir = "pwd";
        cmd->create_dir = "mkdir";
        cmd->change_dir = "cd";
        cmd->rm_file = "rm";
        cmd->rm_dir = "rm -r";
        cmd->create_file = "touch";
        break;
    default:
        cmd->print_current_dir = 0;
        cmd->create_dir = 0;
        cmd->change_dir = 0;
        cmd->rm_file = 0;
        cmd->rm_dir = 0;
        cmd->create_file = 0;
        break;
    }
}