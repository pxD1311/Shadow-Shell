#pragma once

#include "config/config.h"
#include "libraries/common_funcs.h"

#if defined(_WIN32) || defined(_WIN64)
    #include "libraries/win_os_funcs.h"
    void win_shell(wchar_t* WIN_COMMANDS_PATH);

#elif (defined(__APPLE__) && defined(__MACH__)) || defined(__linux__)
    #include "libraries/unix_os_funcs.h"
    void unix_shell(char* UNIX_COMMANDS_PATH);

#endif