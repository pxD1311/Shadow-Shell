#pragma once

#include <string.h>
#include <stdlib.h>

#include "config.h"
#include "error.h"

char* user_input();
int execute_no_arg_command(const char* command);
int execute_arg_command(const char* command, const char* args);
void quit_shell();
