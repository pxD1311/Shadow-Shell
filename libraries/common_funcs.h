#pragma once
#include "../config/config.h"

int count_word_num(wchar_t *str);
int count_word_num_char(char *str);
void display_error(wchar_t *error);
void display_author();
void quit();

void clear_input_buffer();
wchar_t *user_input();
char *user_input_char();
wchar_t **tokenize(wchar_t *input, int *tokens, int *max_token_len);
char **tokenize_char(char *input, int *tokens, int *max_token_len);

wchar_t *char_to_wchar(char *str);
char *wchar_to_char(wchar_t *wstr);