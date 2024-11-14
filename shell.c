#include "shell.h"

void win_shell(wchar_t* WIN_COMMANDS_PATH)
{
    int num_token = 0;
    int max_token_len = 0;

    wchar_t* input;
    wchar_t** input_tokens;

    wchar_t command_path[MAX_BUFF_LEN];

    WIN32_FIND_DATAW **command_dir;
    STARTUPINFOW si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    while(1)
    {
        printf("<<< ");
        input = user_input();
        if (input == NULL) {
            wprintf(L">-< Error reading input\n");
            continue;
        }

        input_tokens = tokenize(input, &num_token, &max_token_len);
        if (input_tokens == NULL) {
            wprintf(L">-< Error tokenizing input\n");
            free(input);
            continue;
        }

        if(num_token == 0)
            continue;

        //for changing the current directroy.
        if(!wcscmp(input_tokens[0], L"ccd"))
        {
            if (num_token < 2)
                wprintf(L"<-> Usage: program <path>\n");
            else if (set_cwd(input_tokens[1]))
                wprintf(L">>> Successfully changed current working directory to <%ls>.\n", input_tokens[1]);
            else
                wprintf(L">>> Failed to change current working directory to <%ls>.\n", input_tokens[1]);

            free(input);
            for (int i = 0; i < num_token; i++)
                free(input_tokens[i]);
            free(input_tokens);
            continue;
        }

        //for quitting the shell.
        else if(!wcscmp(input_tokens[0], L"quit"))
        {
            free(input);
            for (int i = 0; i < num_token; i++)
                free(input_tokens[i]);
            free(input_tokens);
            quit();
        }

        //processing the commands which are in different files.
        swprintf(command_path, MAX_BUFF_LEN, L"%ls\\commands\\windows\\%ls.exe", WIN_COMMANDS_PATH, input_tokens[0]);

        if(!is_path_valid(command_path))
        {
            wprintf(L">-< Invalid command <%s>\n", input_tokens[0]);
            free(input);
            for (int i = 0; i < num_token; i++)
                free(input_tokens[i]);
            free(input_tokens);
            continue;
        }
        
        wchar_t *command_args = (wchar_t*)calloc( wcslen(command_path) + max_token_len*(num_token-1) + num_token, sizeof(wchar_t));
        if(command_args == NULL)
        {
            printf(">-< Insufficient memory\n", input_tokens[0]);
            free(input);
            for (int i = 0; i < num_token; i++)
                free(input_tokens[i]);
            free(input_tokens);
            quit();
        }

        wcscat(command_args, command_path);
        wcscat(command_args, L" ");
        for(int i = 1; i < num_token; i++)
        {
            wcscat(command_args, input_tokens[i]);
            if(i== num_token-1)
                continue;
            wcscat(command_args, L" ");
        }

        //creating a process
        if (CreateProcessW(command_path, command_args, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
        {
            //Waiting till proces ends 
            WaitForSingleObject(pi.hProcess, INFINITE);

            // Closing process + thread handles
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
        }
        else
            wprintf(L">-< %lu Error executing command <%ls> \n", GetLastError(), input_tokens[0]);

        free(input);
        for (int i = 0; i < num_token; i++)
            free(input_tokens[i]);
        free(input_tokens);
        free(command_args);
    }
}


//to be implemented
void unix_shell()
{
    while(1)
    {
        quit();
    }
}