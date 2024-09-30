A Shell for Windows, Macos and Linux. for now windows is implemented yet (unix is under development for now).

Shadow shell v 1.4-ALPHA

Commands :

| Command | Args                   | Purpose                          | Status   |
|---------|------------------------|----------------------------------|----------|
| `dd`    | `path`                 | Display directory items          | Working  |
| `dcd`   | `no-args`              | Display current directory (CWD)  | Working  |
| `df`    | `path`                 | Display file contents            | Working  |
| `ccd`   | `path`                 | Change current directory (CWD)   | Working  |
| `mvf`   | `source destination`   | Move file                        | Working  |
| `mvd`   | `source destination`   | Move directory                   | Working  |
| `cpf`   | `source destination`   | Copy file                        | Working  |
| `cpd`   | `source destination`   | Copy directory                   | Working  |
| `crf`   | `path_to_file`         | Create file                      | Working  |
| `crd`   | `path_to_file`         | Create directory                 | Working  |
| `rmf`   | `path_to_file`         | Remove file                      | Working  |
| `rmd`   | `path_to_file`         | Remove directory                 | Working  |
| `clrscr`| `no-args`              | Clear screen                     | Working  |
| `quit`  | `no-args`              | Quit the shell                   | Working  |


Compilation Commands:<br>
Windows   -  gcc -o win_terminal main.c shell_funcs\common_funcs.c shell_funcs\win_os_funcs.c config\config.c config\os.c shell\win_shell.c <br>
Unix      -  (Work in progress)<br>

stay tuned for further updates :)

-Parth Joshi
