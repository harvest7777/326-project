#!/bin/bash

# Check if correct number of arguments is provided
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <source_file> <destination_file>"
    exit 1
fi

SOURCE_FILE=$1
DEST_FILE=$2

# Compile the C program
echo "Compiling filecopy.c..."
gcc -Wall -o filecopy filecopy.c

if [ $? -ne 0 ]; then
    echo "Compilation failed!"
    exit 1
fi

echo "Compilation successful."

# Run the program
echo "Running filecopy..."
./filecopy "$SOURCE_FILE" "$DEST_FILE"

if [ $? -eq 0 ]; then
    echo "File copied successfully: $SOURCE_FILE -> $DEST_FILE"
else
    echo "File copy failed."
fi

