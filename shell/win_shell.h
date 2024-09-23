#pragma once

#include "../config/config.h"
#include "../shell_funcs/win_os_funcs.h"

void mainloop();
void cmd_exec(const wchar_t* cmd);
