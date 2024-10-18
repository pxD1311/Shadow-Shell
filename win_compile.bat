@echo off
set source_dir=libraries/windows
set target_dir=commands/windows

REM Check if target directory exists; if not, create it
if not exist %target_dir% mkdir %target_dir%

echo Building Shadow Shell

REM Compile all .c files in the source directory
for %%f in (%source_dir%\*.c) do (
    echo Compiling file : %%f
    gcc %%f "config\config.c" "libraries\common_funcs.c" "libraries\win_os_funcs.c" -o %target_dir%\%%~nf.exe -municode -lm
)

echo Compiling file : main.c
gcc -o shadowShell.exe main.c shell.c config/config.c .\libraries\common_funcs.c .\libraries\win_os_funcs.c

echo Compilation complete.
pause
