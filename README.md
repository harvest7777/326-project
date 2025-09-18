 # Project 1 - Inter-Process Communication

**Authors:** Phu Quach (ID: 029475548) and Ryan Tran (ID: 031190716) 
**Course:** CECS 326 SEC 02 - Operating Systems  
**Assignment:** Group Project 1 - Warm up of Interprocess Communication  

## Description
This program demonstrates inter-process communication using UNIX pipes to copy files. It creates a parent-child process architecture where the parent reads from the source file and writes to a pipe, while the child reads from the pipe and writes to the destination file.

## How to Compile

To compile the program, use the following command in your terminal:

```bash
gcc -o filecopy filecopy.c
```

For additional compiler warnings (recommended):
```bash
gcc -Wall -o filecopy filecopy.c
```

## How to Run

### Basic Usage:
```bash
./filecopy <source_file> <destination_file>
```

### Example:
```bash
./filecopy file-to-copy.txt output.txt
```

This command will copy the contents of `file-to-copy.txt` to a new file called `output.txt`.

## How to Test Your Submission

### Test Case 1: Basic File Copy
1. Create or use an existing test file:
   ```bash
   echo "hello" > test-input.txt
   echo "this is a test file" >> test-input.txt
   ```

2. Run the program:
   ```bash
   ./filecopy test-input.txt test-output.txt
   ```

3. Verify the copy worked correctly:
   ```bash
   cat test-output.txt
   ```
   
4. Compare files to ensure they are identical:
   ```bash
   diff test-input.txt test-output.txt
   ```
   (No output means files are identical)

### Test Case 2: Using Provided Files
```bash
./filecopy file-to-copy.txt copied.txt
cat copied.txt
diff file-to-copy.txt copied.txt
```

### Expected Output
When running successfully, you should see output similar to:
```
Hello, my name is file-to-copy.txt and I am copied.txt years old.
Parent PID: 12345, Child PID: 12346
Child PID: 12346
Wrote 54 bytes to pipe
Read 54 bytes from pipe
```

### Test Case 3: Error Handling
Test with missing arguments:
```bash
./filecopy
```
Expected: Error message about missing arguments

Test with non-existent file:
```bash
./filecopy nonexistent.txt output.txt
```
Expected: "Error opening file: No such file or directory"


## Clean Up

To remove compiled program:
```bash
rm filecopy
```

To remove test files:
```bash
rm test-output.txt copied.txt
```

## System Requirements
- Unix-like operating system (Linux, macOS)
- GCC compiler
- Standard C library with POSIX support

## Program Features
- Inter-process communication using UNIX pipes
- Concurrent file processing with parent-child processes
- 1024-byte buffer for efficient data transfer
- Error handling for file operations
- Process ID reporting for debugging