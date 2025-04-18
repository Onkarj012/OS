#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

void runApp()
{
    int op = 1;
    while (1)
    {
        printf("\n====================================\n");
        printf(" Menu:\n");
        printf("------------------------------------\n");
        printf(" 1. Simulate cp\n");
        printf(" 2. Simulate grep\n");
        printf(" 3. Use Linux command cp\n");
        printf(" 4. Use Linux command grep\n");
        printf(" 5. Exit\n");
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
            break;
        }
        case 3:
        {
            char source[256], destination[256];
            printf("\nEnter source file: ");
            scanf("%s", source);
            printf("Enter destination file: ");
            scanf("%s", destination);
            execlp("cp", "cp", source, destination, NULL);
            break;
        }
        case 4:
        {
            char pattern[256], filename[256];
            printf("\nEnter pattern to search: ");
            scanf("%s", pattern);
            printf("Enter filename: ");
            scanf("%s", filename);
            printf("\n");
            execlp("grep", "grep", pattern, filename, NULL);
            break;
        }
        case 5:
            exit(0);
        default:
            printf("\nInvalid choice. Please try again.\n");
            break;
        }
    }
}

int main()
{
    pid_t pid = fork();

    if (pid < 0)
    {
        printf("Fork unsuccessful\n");
        exit(1);
    }
    else if (pid == 0)
    {
        printf("\nChild Process Started\n");
        printf("PID: %d, Parent PID: %d\n", getpid(), getppid());
        runApp();
    }
    else
    {
        wait(NULL);
        printf("\nParent Process Resuming\n");
        printf("PID: %d\n", getpid());
    }

    return 0;
}