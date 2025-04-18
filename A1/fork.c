#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    printf("Before fork!!");
    pid_t p;
    p = fork();

    if(p < 0) {
        printf("\n===============================================");
        printf("\nError in creating child process");
        exit(0);
    }
    else if (p == 0) {
        wait(NULL);
        printf("\n===============================================");
        printf("\nHello from child process, PID: %d", getpid());
        printf("\nParent ID: %d", getppid());
    }
    else {
        wait(NULL);
        printf("\nAfter wait");
        printf("\n===============================================");
        printf("\nHello from parent process, PID: %d", getpid());
    }
    printf("\n\n");
    return 0;
}