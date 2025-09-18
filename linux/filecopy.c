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

// Stack overflow says 4096 is optimal for most systems but this class assignment
// shouldn't require writing anything crazy big.
// https://stackoverflow.com/questions/13433286/optimal-buffer-size-for-reading-file-in-c
#define BUFFER_SIZE 1024

// Function prototypes of course
const char* get_source_file_name(int argc, char *argv[]);
const char* get_destination_file_name(int argc, char *argv[]);
void file_copy(const char *source, const char *destination);
void write_to_pipe(int write_fd, FILE *src);
void read_from_pipe(int read_fd, FILE *dst); 


// Main Function: The main function will parse command-line arguments, create a pipe, fork a child
// process, and handle file copying.
int main(int argc, char *argv[])
{
    // Minimal hello world
	const char* source_file = get_source_file_name(argc, argv);
	const char* destination_file = get_destination_file_name(argc, argv);

    printf("Hello, my name is %s and I am %s years old.\n", source_file, destination_file);
	FILE *src = fopen(source_file, "r");
	FILE *dst = fopen(destination_file, "w");

	// There has to be some file to read from and write to, this is our assumption
	if (src == NULL || dst == NULL) {
		perror("Error opening file");
		return 1;
	}

	// Making the pipe basically it's just a special buffer in memory
	// fd[0] is the end you read from fd[1] is the end you write to
	// THIS IS COPIED OVER TO THE NEW PROCESS ON FORK
	int fd[2];
	pipe(fd);

	pid_t process_id = fork();

	// These wil run concurrently it is not possible to predict which will run first
	// We DO know that the child will get a 0 return value from fork, this is just regular
	// fork behavior https://www.geeksforgeeks.org/c/fork-system-call/

    if (process_id == 0) {
        // Child process
		// WE NEED THIS BECAUSE THE CHILD ONLY WRITES WHEN IT SEES EOF
		close(fd[WRITE_END]); 
        printf("Child PID: %d\n", getpid());
		read_from_pipe(fd[READ_END], dst);
		fclose(dst);           // Save and close 
		close(fd[READ_END]);

    } else {
        // Parent process is responsible for writing into the pipe
		close(fd[READ_END]);
        printf("Parent PID: %d, Child PID: %d\n", getpid(), process_id);
		write_to_pipe(fd[WRITE_END], src);
		fclose(src);           
		close(fd[WRITE_END]);  
    }

    return 0;
}

void write_to_pipe(int write_fd, FILE *src) {
	/**
	 * Read data from a file and write it to the pipe.
	 */
	char buffer[BUFFER_SIZE];
	size_t bytes_read;

	while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, src)) > 0) {
		write(write_fd, buffer, bytes_read);
		printf("Wrote %zu bytes to pipe\n", bytes_read);
	}
}

void read_from_pipe(int read_fd, FILE *dst) {
	/**
	 * Read data from the pipe and write it to a file.
	 */
	char buffer[BUFFER_SIZE];
	ssize_t bytes_read;

	while ((bytes_read = read(read_fd, buffer, BUFFER_SIZE)) > 0) {
		fwrite(buffer, 1, bytes_read, dst);
		printf("Read %zd bytes from pipe\n", bytes_read);
	}
}

const char* get_source_file_name(int argc, char *argv[]) { 
	/**
	 * Helper method for getting source file name and error checking.
	 */
	if (argc < 2) {
		fprintf(stderr, "Source file name not provided.\n");
		return NULL;
	}
	return argv[1];
}

const char* get_destination_file_name(int argc, char *argv[]) {
	/**
	 * Helper method for getting destination file name and error checking.
	 */
	if (argc < 3) {
		fprintf(stderr, "Destination file name not provided.\n");
		return NULL;
	}
	return argv[2];
}