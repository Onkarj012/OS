#include <iostream>
#include <iomanip>
#include <stdexcept>
using namespace std;

#define MAX 100

void displayAllocation(int processSize[], int allocation[], int blockSize[], int n, int m)
{
    cout << "\n---------------------------------------------------------------\n";
    cout << left << setw(12) << "Process No."
         << setw(15) << "Process Size"
         << setw(12) << "Block No."
         << setw(25) << "Fragmented Memory" << endl;
    cout << "---------------------------------------------------------------\n";

    for (int i = 0; i < n; i++)
    {
        if (allocation[i] == -1)
        {
            cout << setw(12) << (i + 1)
                 << setw(15) << processSize[i]
                 << setw(12) << "Not Allocated"
                 << setw(25) << "-" << endl;
        }
        else
        {
            cout << setw(12) << (i + 1)
                 << setw(15) << processSize[i]
                 << setw(12) << allocation[i]
                 << setw(25) << blockSize[allocation[i] - 1] << endl;
        }
    }
    cout << "---------------------------------------------------------------\n";
}

void firstFit(int blockSize[], int m, int processSize[], int n)
{
    int allocation[n];
    fill_n(allocation, n, -1);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                allocation[i] = j + 1;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }
    displayAllocation(processSize, allocation, blockSize, n, m);
}

void bestFit(int blockSize[], int m, int processSize[], int n)
{
    int allocation[n];
    fill_n(allocation, n, -1);
    for (int i = 0; i < n; i++)
    {
        int bestIdx = -1;
        for (int j = 0; j < m; j++)
        {
            if (blockSize[j] >= processSize[i] &&
                (bestIdx == -1 || blockSize[j] < blockSize[bestIdx]))
            {
                bestIdx = j;
            }
        }
        if (bestIdx != -1)
        {
            allocation[i] = bestIdx + 1;
            blockSize[bestIdx] -= processSize[i];
        }
    }
    displayAllocation(processSize, allocation, blockSize, n, m);
}

void worstFit(int blockSize[], int m, int processSize[], int n)
{
    int allocation[n];
    fill_n(allocation, n, -1);
    for (int i = 0; i < n; i++)
    {
        int worstIdx = -1;
        for (int j = 0; j < m; j++)
        {
            if (blockSize[j] >= processSize[i] &&
                (worstIdx == -1 || blockSize[j] > blockSize[worstIdx]))
            {
                worstIdx = j;
            }
        }
        if (worstIdx != -1)
        {
            allocation[i] = worstIdx + 1;
            blockSize[worstIdx] -= processSize[i];
        }
    }
    displayAllocation(processSize, allocation, blockSize, n, m);
}

void nextFit(int blockSize[], int m, int processSize[], int n)
{
    int allocation[n];
    fill_n(allocation, n, -1);
    int lastAllocated = 0;

    for (int i = 0; i < n; i++)
    {
        int j = lastAllocated;
        bool allocated = false;

        do
        {
            if (blockSize[j] >= processSize[i])
            {
                allocation[i] = j + 1;
                blockSize[j] -= processSize[i];
                lastAllocated = j;
                allocated = true;
                break;
            }
            j = (j + 1) % m;
        } while (j != lastAllocated);

        if (!allocated)
            lastAllocated = (lastAllocated + 1) % m;
    }

    displayAllocation(processSize, allocation, blockSize, n, m);
}

int main()
{
    int m, n, choice;
    int blockSize[MAX], processSize[MAX], blockCopy[MAX];

    try
    {
        cout << "Enter the number of memory blocks: ";
        cin >> m;
        if (cin.fail() || m <= 0 || m > MAX)
            throw invalid_argument("Invalid number of memory blocks!");

        cout << "Enter sizes of " << m << " memory blocks:\n";
        for (int i = 0; i < m; i++)
        {
            cin >> blockSize[i];
            if (cin.fail() || blockSize[i] <= 0)
                throw invalid_argument("Invalid block size!");
        }

        cout << "Enter the number of processes: ";
        cin >> n;
        if (cin.fail() || n <= 0 || n > MAX)
            throw invalid_argument("Invalid number of processes!");

        cout << "Enter sizes of " << n << " processes:\n";
        for (int i = 0; i < n; i++)
        {
            cin >> processSize[i];
            if (cin.fail() || processSize[i] <= 0)
                throw invalid_argument("Invalid process size!");
        }

        do
        {
            for (int i = 0; i < m; i++)
                blockCopy[i] = blockSize[i];

            cout << "\nChoose Memory Allocation Strategy:\n";
            cout << "1. First Fit\n";
            cout << "2. Best Fit\n";
            cout << "3. Worst Fit\n";
            cout << "4. Next Fit\n";
            cout << "5. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            if (cin.fail())
                throw runtime_error("Invalid input for choice!");

            switch (choice)
            {
            case 1:
                firstFit(blockCopy, m, processSize, n);
                break;
            case 2:
                bestFit(blockCopy, m, processSize, n);
                break;
            case 3:
                worstFit(blockCopy, m, processSize, n);
                break;
            case 4:
                nextFit(blockCopy, m, processSize, n);
                break;
            case 5:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice! Please enter again.\n";
            }
        } while (choice != 5);
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
