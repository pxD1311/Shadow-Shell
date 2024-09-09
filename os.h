#pragma once

enum OPERATING_SYSTEM {OS_WIN, OS_APPLE, OS_LINUX, OS_INVALID};

typedef struct {
    const char* print_current_dir;
    const char* create_dir;
    const char* change_dir;
    const char* rm_file;
    const char* rm_dir;
    const char* create_file;
} OS_CMDS;

enum OPERATING_SYSTEM getos();
void initialize_shell_commands(OS_CMDS *cmd, enum OPERATING_SYSTEM OS);

