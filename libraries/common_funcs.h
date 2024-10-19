#pragma once
#include "../config/config.h"

void display_error(wchar_t* error);
void quit();
void display_author();
void clear_input_buffer();
wchar_t *user_input();
wchar_t **tokenize(wchar_t *input, int *tokens, int *max_token_len);
int count_word_num(wchar_t* str);
wchar_t *char_to_wchar(char* str);