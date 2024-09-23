#include "common_funcs.h"

void display_error(wchar_t* error)
{
    wprintf(L">-< ERROR : %ls\n", error);
} 

void quit()
{
    printf("<-> Exiting Shadow Shell (Version : %s, Author : Parth)\nThanks for using the shell.\n", VERSION );
    exit(0);
}

void display_author()
{
    printf("<-> Shadow Shell (Version : %s, Author : Parth)\n", VERSION );
}