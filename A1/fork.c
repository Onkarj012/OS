// This program demonstrates the use of fork to create a child process.
// It prints messages from both the parent and child processes.

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Entry point of the program
int main()
{
    printf("Before fork!!");
    pid_t p;
    p = fork(); // Create a child process

    // Check if fork was successful
    if (p < 0)
    {
        printf("\n===============================================");
        printf("\nError in creating child process");
        exit(0);
    }
    else if (p == 0)
    {
        // Child process
        wait(NULL); // Wait for any child processes to complete
        printf("\n===============================================");
        printf("\nHello from child process, PID: %d", getpid());
        printf("\nParent ID: %d", getppid());
    }
    else
    {
        // Parent process
        wait(NULL); // Wait for child process to complete
        printf("\nAfter wait");
        printf("\n===============================================");
        printf("\nHello from parent process, PID: %d", getpid());
    }
    printf("\n\n");
    return 0;
}