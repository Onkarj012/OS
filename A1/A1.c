#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

// Function to display the menu and execute commands
void runApp()
{
    int op = 1; // Variable to store user choice
    while (1)
    {
        // Display menu options
        printf("\n====================================\n");
        printf(" Menu:\n");
        printf("------------------------------------\n");
        printf(" 1. Simulate cp\n");
        printf(" 2. Simulate grep\n");
        printf(" 3. Simulate ls\n");
        printf(" 4. Use Linux command cp\n");
        printf(" 5. Use Linux command grep\n");
        printf(" 6. Use Linux command ls\n");
        printf(" 7. Exit\n");
        printf("------------------------------------\n");
        printf(" Enter your choice: ");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
        {
            char source[256], destination[256];
            printf("\nEnter source file: ");
            scanf("%s", source);
            printf("Enter destination file: ");
            scanf("%s", destination);
            execlp("./copyCommand", "./copyCommand", source, destination, NULL);
            perror("Error executing cp");
            break;
        }
        case 2:
        {
            char pattern[256], filename[256];
            printf("\nEnter pattern to search: ");
            scanf("%s", pattern);
            printf("Enter filename: ");
            scanf("%s", filename);
            execlp("./grepCommand", "./grepCommand", pattern, filename, NULL);
            perror("Error executing grep");
            break;
        }
        case 3:
        {
            char dir_path[256];
            printf("\nEnter directory path (or press Enter for current directory): ");
            scanf("%s", dir_path);
            execlp("./lsCommand", "./lsCommand", dir_path, NULL);
            perror("Error executing ls");
            break;
        }
        case 4:
        {
            char source[256], destination[256];
            printf("\nEnter source file: ");
            scanf("%s", source);
            printf("Enter destination file: ");
            scanf("%s", destination);
            execlp("cp", "cp", source, destination, NULL);
            perror("Error executing Linux cp");
            break;
        }
        case 5:
        {
            char pattern[256], filename[256];
            printf("\nEnter pattern to search: ");
            scanf("%s", pattern);
            printf("Enter filename: ");
            scanf("%s", filename);
            printf("\n");
            execlp("grep", "grep", pattern, filename, NULL);
            perror("Error executing Linux grep");
            break;
        }
        case 6:
        {
            char dir_path[256];
            printf("\nEnter directory path (or press Enter for current directory): ");
            scanf("%s", dir_path);
            execlp("ls", "ls", dir_path, NULL);
            perror("Error executing Linux ls");
            break;
        }
        case 7:
            exit(0);
        default:
            printf("\nInvalid choice. Please try again.\n");
            break;
        }
    }
}

// Entry point of the program
int main()
{
    pid_t pid = fork(); // Create a child process

    if (pid < 0)
    {
        printf("Fork unsuccessful\n");
        exit(1);
    }
    else if (pid == 0)
    {
        // Child process
        printf("\nChild Process Started\n");
        printf("PID: %d, Parent PID: %d\n", getpid(), getppid());
        runApp();
    }
    else
    {
        // Parent process
        wait(NULL); // Wait for child process to complete
        printf("\nParent Process Resuming\n");
        printf("PID: %d\n", getpid());
    }

    return 0;
}