/**
 * filecopy.c
 * 
 * This program copies files using a pipe.
 *
 */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#define READ_END 0
#define WRITE_END 1

/**
 * Main Function: The main function will parse command-line arguments, create a pipe, fork a child
 * process, and handle file copying.
 */
int main(int argc, char *argv[])
{
    // Minimal hello world
    printf("Hello, World!\n");
    return 0;
}

/**
 * File Copying Logic: This section will contain the logic for reading from the source file and writing
 * to the pipe in the parent process, as well as reading from the pipe and writing to the destination file
 * in the child process.
 */
void file_copy(const char *source, const char *destination) {
	return;
}