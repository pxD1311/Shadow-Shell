#include "win_shell.h"

void mainloop()
{
    wchar_t *cmd = (wchar_t*)malloc(sizeof(wchar_t)*MAX_CMD_LEN);
    display_author();
    while (1)
    {
        printf("<<< ");
        if (wscanf(L"%ls", cmd) != 1)
        {
            display_error(L"Invalid Command.");
        }
        cmd_exec(cmd);
    }
}

void cmd_exec(const wchar_t* cmd)
{
    if(!wcscmp(cmd, CMD_DISPLAY_CWD))
        display_cwd();
    else if(!wcscmp(cmd, CMD_CHANGE_CWD))
    {
        wchar_t dir[MAX_PATH];
        if (wscanf(L"%ls", dir) != 1 || is_path_valid(dir) == FALSE){
            display_error(L"Invalid Path, Can't change Current Working Directory.");
            return;
        }
        if (set_cwd(dir) != TRUE)
        {
            display_error(L"Invalid Path, Can't Change Current Working Directory.");
            return;
        }
        wprintf(L">>> Successfully Changed Current Working Directory To <%ls>.\n", get_cwd());  
    }
    else if(!wcscmp(cmd, CMD_CREATE_FILE))
    {
        wchar_t dir[MAX_PATH];
        if (wscanf(L"%ls", dir) != 1){
            display_error(L"Invalid Path, Can't Create File.");
            return;
        }
        if(create_file(dir) != TRUE)
        {
            display_error(L"Invalid Path, Can't Create File.");
            return;
        }
        wprintf(L">>> Successfully Created File <%ls>.\n", dir);
    }
    else if(!wcscmp(cmd, CMD_CREATE_DIR))
    {
        wchar_t dir[MAX_PATH];
        if (wscanf(L"%ls", dir) != 1)
        {
            display_error(L"Invalid Path, Can't Create Directory.");
            return;
        }
        if(create_directory(dir) != TRUE)
        {
            display_error(L"Invalid Path, Can't Create Directory.");
            return;
        }
        wprintf(L">>> Successfully Created Directory <%ls>.\n", dir);
    }
    else if(!wcscmp(cmd, CMD_DISPLAY_DIR))
    {
        wchar_t dir[MAX_PATH];
        if (wscanf(L"%ls", dir) != 1 || is_path_valid(dir) == FALSE){
            display_error(L"Invalid Path, Can't Display Directory.");
            return;
        }
        display_list_dir(dir);
    }
    else if(!wcscmp(cmd, CMD_QUIT))
    {
        quit();
    }
    else if(!wcscmp(cmd, CMD_CLEAR_SCREEN))
    {
        if (clear_screen())
            display_error(L"Can't Clear Terminal Screen.");
        else
            display_author();
    }
    else{
        display_error(L"Invalid Command.");
    }
}

