#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

int main()
{
    int fd[2];
    pid_t pid;
    int choice;

    printf("Choose an option:\n");
    printf("1 - Sort only\n");
    printf("2 - Unique only\n");
    printf("3 - Both (Sort and Unique)\n");
    printf("Enter your choice (1/2/3): ");
    scanf("%d", &choice);

    int filedes = open("file.txt", O_RDONLY);
    if (filedes < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    if (pipe(fd) == -1)
    {
        perror("pipe");
        close(filedes);
        exit(EXIT_FAILURE);
    }

    switch (choice)
    {
    case 1:
        if ((pid = fork()) == 0)
        {
            dup2(filedes, STDIN_FILENO);
            close(filedes);
            execlp("sort", "sort", NULL);
            perror("execlp sort");
            exit(EXIT_FAILURE);
        }
        close(filedes);
        wait(NULL);
        break;

    case 2:
    case 3:
        if ((pid = fork()) == 0)
        {
            dup2(filedes, STDIN_FILENO);
            close(filedes);
            dup2(fd[1], STDOUT_FILENO);
            close(fd[0]);
            close(fd[1]);
            execlp("sort", "sort", NULL);
            perror("execlp sort");
            exit(EXIT_FAILURE);
        }

        close(filedes);
        close(fd[1]);

        if ((pid = fork()) == 0)
        {
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
            execlp("uniq", "uniq", NULL);
            perror("execlp uniq");
            exit(EXIT_FAILURE);
        }

        close(fd[0]);
        wait(NULL);
        wait(NULL);
        break;

    default:
        printf("Invalid choice!\n");
        close(filedes);
        exit(EXIT_FAILURE);
    }

    return 0;
}
