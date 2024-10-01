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
            while(getwchar() == L'\n');
            display_error(L"Invalid Command.");
        }
        cmd_exec(cmd);
    }
}

void cmd_exec(const wchar_t* cmd)
{
    // display current working directory
    if(!wcscmp(cmd, CMD_DISPLAY_CWD)) 
        display_cwd();

    // change current working directory
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

    // create new file
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

    // create new directory
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

    // remove a file
    else if(!wcscmp(cmd, CMD_REMOVE_FILE))
    {
        wchar_t dir[MAX_PATH];
        if (wscanf(L"%ls", dir) != 1){
            display_error(L"Invalid Path, Can't Remove File.");
            return;
        }
        if(remove_file(dir) != TRUE)
        {
            display_error(L"Invalid Path, Can't Remove File.");
            return;
        }
        wprintf(L">>> Successfully Removed File <%ls>.\n", dir);
    }

    // remove a directory
    else if(!wcscmp(cmd, CMD_REMOVE_DIR))
    {
        wchar_t dir[MAX_PATH];
        if (wscanf(L"%ls", dir) != 1){
            display_error(L"Invalid Path, Can't Remove directory.");
            return;
        }
        if(remove_dir(dir) != TRUE)
        {
            display_error(L"Invalid Path, Can't Remove directory.");
            return;
        }
        wprintf(L">>> Successfully Removed Directory <%ls>.\n", dir);
    }

    // copy a file from source to destination
    else if(!wcscmp(cmd, CMD_COPY_FILE))
    {
        wchar_t dir_s[MAX_PATH];
        wchar_t dir_d[MAX_PATH];
        if (wscanf(L"%ls", dir_s) != 1){
            display_error(L"Invalid Path, Can't Copy File.");
            return;
        }
        if (wscanf(L"%ls", dir_d) != 1){
            display_error(L"Invalid Path, Can't Copy File.");
            return;
        }
        if(copy_file(dir_s, dir_d) != TRUE)
        {
            display_error(L"Invalid Path, Can't Copy File.");
            return;
        }
        wprintf(L">>> Successfully Copied File from <%ls> to <%ls>.\n", dir_s, dir_d);
    }

    // move a file from source to destination
    else if(!wcscmp(cmd, CMD_MOVE_FILE))
    {
        wchar_t dir_s[MAX_PATH];
        wchar_t dir_d[MAX_PATH];
        if (wscanf(L"%ls", dir_s) != 1){
            display_error(L"Invalid Path, Can't Move File.");
            return;
        }
        if (wscanf(L"%ls", dir_d) != 1){
            display_error(L"Invalid Path, Can't Move File.");
            return;
        }
        if(move_file(dir_s, dir_d) != TRUE)
        {
            display_error(L"Invalid Path, Can't Move File.");
            return;
        }
        wprintf(L">>> Successfully Moved File from <%ls> to <%ls>.\n", dir_s, dir_d);
    }

// copy a directory from source to destination
    else if(!wcscmp(cmd, CMD_COPY_DIR))
    {
        wchar_t dir_s[MAX_PATH];
        wchar_t dir_d[MAX_PATH];
        if (wscanf(L"%ls", dir_s) != 1){
            display_error(L"Invalid Path, Can't Copy Directory.");
            return;
        }
        if (wscanf(L"%ls", dir_d) != 1){
            display_error(L"Invalid Path, Can't Copy Directory.");
            return;
        }
        if(copy_dir(dir_s, dir_d) != TRUE)
        {
            display_error(L"Invalid Path, Can't Copy Directory.");
            return;
        }
        wprintf(L">>> Successfully Copied Directory from <%ls> to <%ls>.\n", dir_s, dir_d);
    }

// move a directory from source to destination
    else if(!wcscmp(cmd, CMD_MOVE_DIR))
    {
        wchar_t dir_s[MAX_PATH];
        wchar_t dir_d[MAX_PATH];
        if (wscanf(L"%ls", dir_s) != 1){
            display_error(L"Invalid Path, Can't Move Directory.");
            return;
        }
        if (wscanf(L"%ls", dir_d) != 1){
            display_error(L"Invalid Path, Can't Move Directory.");
            return;
        }
        if(move_dir(dir_s, dir_d) != TRUE)
        {
            display_error(L"Invalid Path, Can't Move Directory.");
            return;
        }
        wprintf(L">>> Successfully Moved Directory from <%ls> to <%ls>.\n", dir_s, dir_d);
    }

    // display current working directory
    else if(!wcscmp(cmd, CMD_DISPLAY_DIR))
    {
        wchar_t dir[MAX_PATH];
        if (wscanf(L"%ls", dir) != 1 || is_path_valid(dir) == FALSE){
            display_error(L"Invalid Path, Can't Display Directory.");
            return;
        }
        display_list_dir(dir);
    }

    // display contents of a file
    else if(!wcscmp(cmd, CMD_DISPLAY_FILE))
    {
        wchar_t dir[MAX_PATH];
        if (wscanf(L"%ls", dir) != 1 || is_path_valid(dir) == FALSE){
            display_error(L"Invalid Path, Can't Display File.");
            return;
        }
        display_file(dir);
    }

    // display number of words/tokens in a file
    else if(!wcscmp(cmd, CMD_DISPLAY_FILE_WORD_NUM))
    {
        wchar_t dir[MAX_PATH];
        if (wscanf(L"%ls", dir) != 1 || is_path_valid(dir) == FALSE){
            display_error(L"Invalid Path, Can't Display number of words/tokens in the file.");
            return;
        }
        display_file_word_num(dir);
    }

    // quit the shell
    else if(!wcscmp(cmd, CMD_QUIT))
    {
        quit();
    }

    // clear shell screen
    else if(!wcscmp(cmd, CMD_CLEAR_SCREEN))
    {
        if (clear_screen())
            display_error(L"Can't Clear Terminal Screen.");
        else
            display_author();
    }

    // invalid command
    else{
        while(getwchar() == L'\n');
        display_error(L"Invalid Command.");
    }
}

