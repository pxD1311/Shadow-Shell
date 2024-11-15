#include "config.h"

char *VERSION = "1.6.0-ALPHA";

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