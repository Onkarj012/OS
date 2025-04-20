// This program demonstrates the use of pipes and fork to execute sort and uniq commands.
// It allows the user to choose between sorting, finding unique entries, or both.

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

// Entry point of the program
int main()
{
    int fd[2];  // File descriptors for the pipe
    pid_t pid;  // Process ID
    int choice; // User's choice for operation

    // Display menu options
    printf("Choose an option:\n");
    printf("1 - Sort only\n");
    printf("2 - Unique only\n");
    printf("3 - Both (Sort and Unique)\n");
    printf("Enter your choice (1/2/3): ");
    scanf("%d", &choice);

    int filedes = open("file.txt", O_RDONLY); // Open file for reading
    if (filedes < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Create a pipe
    if (pipe(fd) == -1)
    {
        perror("pipe");
        close(filedes);
        exit(EXIT_FAILURE);
    }

    switch (choice)
    {
    case 1:
        // Fork a child process to execute sort
        if ((pid = fork()) == 0)
        {
            dup2(filedes, STDIN_FILENO); // Redirect file to standard input
            close(filedes);
            execlp("sort", "sort", NULL); // Execute sort command
            perror("execlp sort");
            exit(EXIT_FAILURE);
        }
        close(filedes);
        wait(NULL); // Wait for child process to complete
        break;

    case 2:
    case 3:
        // Fork a child process to execute sort
        if ((pid = fork()) == 0)
        {
            dup2(filedes, STDIN_FILENO); // Redirect file to standard input
            close(filedes);
            dup2(fd[1], STDOUT_FILENO); // Redirect standard output to pipe
            close(fd[0]);
            close(fd[1]);
            execlp("sort", "sort", NULL); // Execute sort command
            perror("execlp sort");
            exit(EXIT_FAILURE);
        }

        close(filedes);
        close(fd[1]);

        // Fork another child process to execute uniq
        if ((pid = fork()) == 0)
        {
            dup2(fd[0], STDIN_FILENO); // Redirect pipe to standard input
            close(fd[0]);
            execlp("uniq", "uniq", NULL); // Execute uniq command
            perror("execlp uniq");
            exit(EXIT_FAILURE);
        }

        close(fd[0]);
        wait(NULL); // Wait for child processes to complete
        wait(NULL);
        break;

    default:
        printf("Invalid choice!\n");
        close(filedes);
        exit(EXIT_FAILURE);
    }

    return 0;
}
