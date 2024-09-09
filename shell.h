#pragma once

#include <stdio.h>
#include <string.h>

#include "os.h"
#include "shell_funcs.h"

void display_opening_text();
void mainloop(OS_CMDS* commands);
void display_closing_text();
