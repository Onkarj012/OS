#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

sem_t *wrt;
pthread_mutex_t mutex;
int balance = 500;
int numreader = 0;

void *credit_writer(void *wno)
{
    int amount = 500;
    sem_wait(wrt);
    balance += amount;
    printf("Writer %d credited %d. Balance: %d\n", *((int *)wno), amount, balance);
    sem_post(wrt);
    return NULL;
}

void *debit_writer(void *wno)
{
    int amount = 100;
    sem_wait(wrt);
    balance -= amount;
    printf("Writer %d debited %d. Balance: %d\n", *((int *)wno), amount, balance);
    sem_post(wrt);
    return NULL;
}

int main()
{
    pthread_t writers[5];
    pthread_mutex_init(&mutex, NULL);

    // Initialize named semaphore
    wrt = sem_open("/wrt_semaphore", O_CREAT, 0644, 1);
    if (wrt == SEM_FAILED)
    {
        perror("sem_open failed");
        exit(EXIT_FAILURE);
    }

    int a[5] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++)
    {
        pthread_create(&writers[i], NULL, credit_writer, (void *)&a[i]);
    }

    for (int i = 0; i < 5; i++)
    {
        pthread_join(writers[i], NULL);
    }

    // Clean up named semaphore
    sem_close(wrt);
    sem_unlink("/wrt_semaphore");
    pthread_mutex_destroy(&mutex);

    return 0;
}
