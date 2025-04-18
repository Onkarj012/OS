#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_READERS 5

pthread_mutex_t mutex;
sem_t *writeLock;          // Named semaphore
int accountBalance = 1000; // Initial bank balance
int totalReaders = 0;

// Reader function: Customers checking balance
void *reader(void *arg)
{
    int id = *((int *)arg);
    pthread_mutex_lock(&mutex);
    totalReaders++;
    if (totalReaders == 1)
    {
        sem_wait(writeLock); // First reader locks the writers
    }
    pthread_mutex_unlock(&mutex);

    printf("Customer %d checked balance: $%d\n", id, accountBalance);
    sleep(1);

    pthread_mutex_lock(&mutex);
    totalReaders--;
    if (totalReaders == 0)
    {
        sem_post(writeLock); // Last reader unlocks writers
    }
    pthread_mutex_unlock(&mutex);

    return NULL;
}

// Writer function: Customers making deposits or withdrawals
void *writer(void *arg)
{
    int id = *((int *)arg);
    sem_wait(writeLock);
    accountBalance += 100; // Simulating a deposit
    printf("Customer %d deposited $100. New balance: $%d\n", id, accountBalance);
    sleep(1);
    sem_post(writeLock);
    return NULL;
}

int main()
{
    pthread_t readers[MAX_READERS], writers[2];
    int readerIds[MAX_READERS], writerIds[2];

    pthread_mutex_init(&mutex, NULL);

    // Create a named semaphore
    writeLock = sem_open("/writeLockSem", O_CREAT, 0644, 1);
    if (writeLock == SEM_FAILED)
    {
        perror("sem_open failed");
        return 1;
    }

    // Banking Application:
    // - Multiple customers can check their balance simultaneously.
    // - Deposits (writes) must be exclusive to prevent race conditions.

    for (int i = 0; i < MAX_READERS; i++)
    {
        readerIds[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &readerIds[i]);
    }

    for (int i = 0; i < 2; i++)
    {
        writerIds[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writerIds[i]);
    }

    for (int i = 0; i < MAX_READERS; i++)
    {
        pthread_join(readers[i], NULL);
    }

    for (int i = 0; i < 2; i++)
    {
        pthread_join(writers[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    // Close and unlink the semaphore
    sem_close(writeLock);
    sem_unlink("/writeLockSem");

    return 0;
}