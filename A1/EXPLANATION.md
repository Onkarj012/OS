# A1: Basic Linux Command Simulation

This assignment focuses on simulating basic Linux commands and process management using system calls.

## Files and Their Purposes

### 1. copy.c

- **Purpose**: Simulates the Linux `cp` command
- **Functionality**:
  - Takes source and destination file names as command-line arguments
  - Opens source file in read mode and destination file in write mode
  - Copies content from source to destination file
  - Handles basic error checking for file operations

### 2. A1.c

- **Purpose**: Menu-driven interface for command simulation
- **Functionality**:
  - Uses fork() to create a child process
  - Provides a menu with options to:
    - Simulate cp command
    - Simulate grep command
    - Use actual Linux cp command
    - Use actual Linux grep command
  - Demonstrates process creation and management

### 3. grep.c

- **Purpose**: Simulates the Linux `grep` command
- **Functionality**:
  - Takes pattern and filename as arguments
  - Supports optional '-c' flag to count occurrences
  - Searches for pattern in the specified file
  - Prints whether pattern was found and count if requested

### 4. fork.c

- **Purpose**: Demonstrates process creation using fork()
- **Functionality**:
  - Creates a child process using fork()
  - Shows process IDs (PID) of both parent and child
  - Demonstrates process hierarchy and communication

## Key Concepts Demonstrated

- File I/O operations
- Process creation and management
- Command-line argument handling
- Basic string manipulation
- System calls (fork, exec)
- Process synchronization

## How to Run

1. Compile each file using gcc:
   ```bash
   gcc copy.c -o copy
   gcc A1.c -o A1
   gcc grep.c -o grep
   gcc fork.c -o fork
   ```
2. Run the executables with appropriate arguments
3. For A1.c, follow the menu prompts to execute different commands
