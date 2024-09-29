#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <wchar.h>

#include "os.h"
#include "types.h"

extern char* VERSION;   
extern OS current_os;
extern unsigned long int MAX_BUFF_LEN;
extern unsigned long int MAX_CMD_LEN;

extern const wchar_t* CMD_DISPLAY_DIR;
extern const wchar_t* CMD_DISPLAY_CWD;
extern const wchar_t* CMD_CHANGE_CWD;
extern const wchar_t* CMD_MOVE_FILE;
extern const wchar_t* CMD_COPY_FILE;
extern const wchar_t* CMD_COPY_DIR;
extern const wchar_t* CMD_MOVE_DIR;
extern const wchar_t* CMD_CREATE_FILE;
extern const wchar_t* CMD_CREATE_DIR;
extern const wchar_t* CMD_CLEAR_SCREEN;
extern const wchar_t *CMD_REMOVE_FILE;
extern const wchar_t *CMD_REMOVE_DIR;
extern const wchar_t* CMD_QUIT;

