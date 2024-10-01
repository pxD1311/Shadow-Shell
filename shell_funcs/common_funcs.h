#pragma once
#include "..\config\config.h"

void display_error(wchar_t* error);
void quit();
void display_author();
wchar_t **tokenize(wchar_t *input, int *tokens, int *max_token_len);