#include "common_funcs.h"

void display_error(wchar_t *error)
{
    wprintf(L">-< ERROR : %ls\n", error);
}

void quit()
{
    printf("<-> Exiting Shadow Shell (Version : %s, Author : Parth)\nThanks for using the shell.\n", VERSION);
    exit(0);
}

void display_author()
{
    printf("<-> Shadow Shell (Version : %s, Author : Parth)\n", VERSION);
}

void clear_input_buffer()
{
    while (getwchar() != L'\n')
        ;
}

wchar_t *user_input()
{
    wchar_t *input = (wchar_t *)malloc(sizeof(wchar_t) * MAX_BUFF_LEN);
    if (input == NULL)
    {
        display_error(L"Insufficient memory.");
        return (wchar_t *)NULL;
    }
    fgetws(input, MAX_BUFF_LEN, stdin);

    return input;
}

char *user_input_char()
{
    char *input = (char *)malloc(MAX_BUFF_LEN);
    if (input == NULL)
    {
        display_error(L"Insufficient memory.");
        return (char *)NULL;
    }
    fgets(input, MAX_BUFF_LEN, stdin);
    return input;
}

wchar_t **tokenize(wchar_t *input, int *tokens, int *max_token_len)
{
    *tokens = 0;
    *max_token_len = 0;
    int token_len = 0;

    int input_len = wcslen(input);
    wchar_t **output = NULL;

    for (int i = 0; i < input_len; i++)
    {
        if (!iswspace(input[i]))
        {
            token_len++;
        }
        else
        {
            if (token_len > 0)
            {
                if (token_len > *max_token_len)
                    *max_token_len = token_len;
                (*tokens)++;
                token_len = 0;
            }
        }
    }

    if (token_len > 0)
    {
        if (token_len > *max_token_len)
            *max_token_len = token_len;
        (*tokens)++;
    }

    output = (wchar_t **)malloc(*tokens * sizeof(wchar_t *));
    if (output == NULL)
    {
        display_error(L"Insufficient memory.");
        return NULL;
    }

    for (int i = 0; i < *tokens; i++)
    {
        output[i] = (wchar_t *)malloc((*max_token_len + 1) * sizeof(wchar_t));
        if (output[i] == NULL)
        {
            display_error(L"Insufficient memory.");
            for (int j = 0; j < i; j++)
                free(output[j]);
            free(output);
            return NULL;
        }
    }

    int token_index = 0, char_index = 0;
    token_len = 0;

    for (int i = 0; i <= input_len; i++)
    {
        if (i < input_len && !iswspace(input[i]))
        {
            if (token_len == 0)
                char_index = 0;
            output[token_index][char_index++] = input[i];
            token_len++;
        }
        else
        {
            if (token_len > 0)
            {
                output[token_index][char_index] = L'\0';
                token_index++;
                token_len = 0;
            }
        }
    }

    return output;
}

char **tokenize_char(char *input, int *tokens, int *max_token_len)
{
    *tokens = 0;
    *max_token_len = 0;
    int token_len = 0;

    int input_len = strlen(input);
    char **output = NULL;

    // First pass: Count tokens and find the max token length
    for (int i = 0; i < input_len; i++)
    {
        if (!isspace((unsigned char)input[i]))
        {
            token_len++;
        }
        else
        {
            if (token_len > 0)
            {
                if (token_len > *max_token_len)
                    *max_token_len = token_len;
                (*tokens)++;
                token_len = 0;
            }
        }
    }
    // If the last token ends at the end of the string
    if (token_len > 0)
    {
        if (token_len > *max_token_len)
            *max_token_len = token_len;
        (*tokens)++;
    }

    // Allocate memory for tokens
    output = (char **)malloc(*tokens * sizeof(char *));
    if (output == NULL)
    {
        fprintf(stderr, "Insufficient memory.\n");
        return NULL;
    }

    for (int i = 0; i < *tokens; i++)
    {
        output[i] = (char *)malloc((*max_token_len + 1) * sizeof(char));
        if (output[i] == NULL)
        {
            fprintf(stderr, "Insufficient memory.\n");
            for (int j = 0; j < i; j++)
                free(output[j]);
            free(output);
            return NULL;
        }
    }

    // Second pass: Extract tokens
    int token_index = 0, char_index = 0;
    token_len = 0;

    for (int i = 0; i <= input_len; i++)
    {
        if (i < input_len && !isspace((unsigned char)input[i]))
        {
            if (token_len == 0)
                char_index = 0;
            output[token_index][char_index++] = input[i];
            token_len++;
        }
        else
        {
            if (token_len > 0)
            {
                output[token_index][char_index] = '\0';
                token_index++;
                token_len = 0;
            }
        }
    }

    return output;
}

int count_word_num(wchar_t *str)
{
    int words = 0;
    int str_len = wcslen(str);

    for (int i = 0; i < str_len; i++)
    {
        if ((i == 0 || isspace(str[i])) && !isspace(str[i - 1]))
            words++;
        if (i == str_len - 1 && isspace(str[str_len - 1]))
            words--;
    }
    return words;
}

int count_word_num_char(char *str)
{
    int words = 0;
    int str_len = strlen(str);

    for (int i = 0; i < str_len; i++)
    {
        if ((i == 0 || isspace(str[i])) && !isspace(str[i - 1]))
            words++;
        if (i == str_len - 1 && isspace(str[str_len - 1]))
            words--;
    }
    return words;
}

wchar_t *char_to_wchar(char *str)
{
    int len = mbstowcs(NULL, str, 0);
    if (len < 0)
        return (wchar_t *)NULL;
    wchar_t *wstr = (wchar_t *)malloc(sizeof(wchar_t) * (len + 1));
    if (wstr == NULL)
        return (wchar_t *)NULL;
    mbstowcs(wstr, str, len);
    wstr[len] = L'\0';
    return wstr;
}

char *wchar_to_char(wchar_t *wstr)
{
    int len = wcstombs(NULL, wstr, 0);
    if (len < 0)
        return NULL;
    char *str = (char *)malloc(sizeof(char) * (len + 1));
    if (str == NULL)
        return NULL;
    wcstombs(str, wstr, len);
    str[len] = '\0';
    return str;
}