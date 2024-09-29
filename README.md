A Shell for Windows, Macos and Linux. for now windows is implemented yet.

Shadow shell v 1.4-ALPHA

Commands :

| Command  | Purpose                          | Status               |
|----------|----------------------------------|----------------------|
| dd       | Display directory items          | Working              |
| dcd      | Display current directory (CWD)  | Working              |
| ccd      | Change current directory (CWD)   | Working              |
| mvf      | Move file                        | Working              |
| mvd      | Move directory                   | Working              |
| cpf      | Copy file                        | Working              |
| cpd      | Copy directory                   | Working              |
| crf      | Create file                      | Working              |
| crd      | Create directory                 | Working              |
| rmf      | Remove file                      | Working              |
| rmd      | Remove directory                 | Working              |
| clrscr   | Clear screen                     | Working              |
| quit     | Quit the shell                   | Working              |


Compilation Commands:
Windows -  gcc -o win_terminal main.c shell_funcs\common_funcs.c shell_funcs\win_os_funcs.c config\config.c config\os.c shell\win_shell.c
Unix    -  (not implemented yet)

stay tuned for further updates :)
-Parth Joshi
