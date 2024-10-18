#include "config.h"

char *VERSION = "1.5.0-ALPHA";

wchar_t* WIN_COMMANDS_PATH = L"commands/windows/";   
wchar_t* UNIX_COMMANDS_PATH = L"commands/unix/"; 

//funcs
OS get_os()
{
    #if defined(__WIN32__) 
        return WIN;
    #elif defined(__APPLE__) 
        return APPLE;
    #elif defined(__linux__)
        return LINUX;
    #else 
        return INVALID;
    #endif
}