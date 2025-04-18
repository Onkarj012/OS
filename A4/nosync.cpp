#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_READERS 5

int accountBalance = 1000; // Initial bank balance

// Reader function: Customers checking balance
void *reader(void *arg)
{
    int id = *((int *)arg);
    printf("Customer %d checked balance: $%d\n", id, accountBalance);
    sleep(1);
    return NULL;
}

// Writer function: Customers making deposits or withdrawals
void *writer(void *arg)
{
    int id = *((int *)arg);
    int temp = accountBalance;
    temp += 100; // Simulate deposit
    sleep(1);    // Intentional delay to increase chance of race condition
    accountBalance = temp;
    printf("Customer %d deposited $100. New balance: $%d\n", id, accountBalance);
    return NULL;
}

int main()
{
    pthread_t readers[MAX_READERS], writers[2];
    int readerIds[MAX_READERS], writerIds[2];

    // Create reader threads
    for (int i = 0; i < MAX_READERS; i++)
    {
        readerIds[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &readerIds[i]);
    }

    // Create writer threads
    for (int i = 0; i < 2; i++)
    {
        writerIds[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writerIds[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < MAX_READERS; i++)
    {
        pthread_join(readers[i], NULL);
    }

    for (int i = 0; i < 2; i++)
    {
        pthread_join(writers[i], NULL);
    }

    printf("Final Account Balance (may be incorrect due to race conditions): $%d\n", accountBalance);

    return 0;
}
