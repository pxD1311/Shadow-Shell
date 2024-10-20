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

void clear_input_buffer()
{
    while (getwchar() != L'\n');
}

wchar_t* user_input()
{
    wchar_t* input = (wchar_t*)malloc(sizeof(wchar_t)*MAX_BUFF_LEN);
    if(input == NULL)
    {
        display_error(L"Insufficient memory.");
        return (wchar_t*)NULL; 
    }
    fgetws(input, MAX_BUFF_LEN, stdin);

    return input;
}

wchar_t **tokenize(wchar_t *input, int *tokens, int *max_token_len)
{
    *tokens = 0;
    *max_token_len = 0;
    int token_len = 0;

    int input_len = wcslen(input);

    for (int i = 0; i < input_len; i++)
    {
        if (!isspace(input[i]))
            token_len++;
        else
        {
            if (token_len > *max_token_len)
                *max_token_len = token_len;
            token_len = 0;
        }

        if ((i == 0 || isspace(input[i])) && !isspace(input[i - 1]))
            (*tokens)++;
        if (i == input_len - 1 && isspace(input[input_len - 1]))
            (*tokens)--;
    }

    wchar_t **output = (wchar_t **)malloc(*tokens * sizeof(wchar_t*));
    if (output == NULL)
        display_error(L"Insufficient memory.");

    for (int i = 0; i < *tokens; i++)
    {
        output[i] = (wchar_t *)malloc((*max_token_len + 1)*sizeof(wchar_t));
        if (output[i] == NULL)
        {
            display_error(L"Insufficient memory.");
            for (int j = 0; j <= i; j++)
                free(output[i]);
            free(output);
        }
    }

    int notspace = 0;
    for (int i = 0, j = 0, k = 0; i < input_len; i++)
    {
        if(!isspace(input[i]))
        {
            output[j][k] = input[i];
            notspace = 1;
            k++;
        }
        else
        {
            if(notspace == 1)
            {
                output[j][k] = '\0';
                j++;
            }
            else if(i == input_len-1)
                break;
            notspace = k = 0;
        }
    }

    return output;
}

int count_word_num(wchar_t* str)
{
    int words = 0;
    int str_len = wcslen(str);

    for(int i = 0; i < str_len; i++)
    {
        if ((i == 0 || isspace(str[i])) && !isspace(str[i - 1]))
            words++;
        if (i == str_len - 1 && isspace(str[str_len - 1]))
            words--;
    }
    return words;
}

wchar_t *char_to_wchar(char* str)
{
    int len = mbstowcs(NULL, str, 0);
    if (len < 0) 
        return (wchar_t*)NULL;
    wchar_t *wstr = (wchar_t*)malloc(sizeof(wchar_t)*(len+1));
    if (wstr == NULL) 
        return (wchar_t*)NULL;
    mbstowcs(wstr, str, len);
    wstr[len] = L'\0';
    return wstr;
}