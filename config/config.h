#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <wchar.h>

//config
#define MAX_BUFF_LEN 1000

typedef enum OPERATING_SYSTEM {WIN, APPLE, LINUX, INVALID} OS;
extern char* VERSION;   

extern wchar_t* WIN_COMMANDS_PATH;   
extern wchar_t* UNIX_COMMANDS_PATH;   
