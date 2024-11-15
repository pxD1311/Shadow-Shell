#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <wctype.h>
#include <wchar.h>

//config
#define MAX_BUFF_LEN 1000

typedef enum OPERATING_SYSTEM {WIN, APPLE, LINUX, INVALID} OS;
extern char* VERSION;