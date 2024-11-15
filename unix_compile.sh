#!/bin/bash

# Set the source and target directories
source_dir="libraries/unix"
target_dir="commands/unix"

# Check if target directory exists; if not, create it
if [ ! -d "$target_dir" ]; then
    mkdir -p "$target_dir"
fi

echo "Building Shadow Shell"

# Compile all .c files in the source directory
for file in "$source_dir"/*.c; do
    echo "Compiling file: $file"
    gcc "$file" "config/config.c" "libraries/common_funcs.c" "libraries/unix_os_funcs.c" -o "$target_dir/$(basename "$file" .c)" -lm
done

echo "Compiling main.c"
gcc -o shadowShell main.c shell.c config/config.c libraries/common_funcs.c libraries/unix_os_funcs.c -lm

# Ensure the executables are marked as executable
chmod +x shadowShell
chmod +x "$target_dir"/*

echo "Compilation complete."
