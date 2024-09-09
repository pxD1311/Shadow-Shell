#include <stdio.h>
#include <stdlib.h>

#include "shell.h"

int main()
{
    enum OPERATING_SYSTEM OS = getos();
    OS_CMDS* commands = (OS_CMDS*)malloc(sizeof(OS_CMDS));
    initialize_shell_commands(commands, OS);

    display_opening_text();
    mainloop(commands);
    display_closing_text();
    return 0;
}
