// This program implements the Banker's Algorithm to determine if a system is in a safe state.
// It checks if the system can allocate resources to each process in some order and still avoid a deadlock.

#include <iostream>
#include <stdexcept>
using namespace std;

// Function to input data for allocation, max, and available resources
void inputData(int processes, int resources, int allocation[][10], int max[][10], int available[])
{
    try
    {
        cout << "Enter allocation matrix:\n";
        for (int i = 0; i < processes; i++)
            for (int j = 0; j < resources; j++)
            {
                if (!(cin >> allocation[i][j]))
                    throw runtime_error("Invalid input in allocation matrix!");
            }

        cout << "Enter max matrix:\n";
        for (int i = 0; i < processes; i++)
            for (int j = 0; j < resources; j++)
            {
                if (!(cin >> max[i][j]))
                    throw runtime_error("Invalid input in max matrix!");
            }

        cout << "Enter available resources:\n";
        for (int i = 0; i < resources; i++)
        {
            if (!(cin >> available[i]))
                throw runtime_error("Invalid input in available resources!");
        }
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << endl;
        exit(1);
    }
}

// Function to calculate the need matrix
void calculateNeedMatrix(int processes, int resources, int max[][10], int allocation[][10], int need[][10])
{
    for (int i = 0; i < processes; i++)
        for (int j = 0; j < resources; j++)
            need[i][j] = max[i][j] - allocation[i][j];
}

// Function to check if the system is in a safe state
bool isSafeState(int processes, int resources, int allocation[][10], int need[][10], int available[])
{
    try
    {
        bool finish[processes]; // Track if process is finished
        for (int i = 0; i < processes; i++)
            finish[i] = false;
        int ava[10], safeSequence[processes], count = 0;
        for (int i = 0; i < resources; i++)
            ava[i] = available[i];

        while (count < processes)
        {
            bool found = false;
            for (int i = 0; i < processes; i++)
            {
                if (!finish[i])
                {
                    int j;
                    for (j = 0; j < resources; j++)
                        if (need[i][j] > ava[j])
                            break;
                    if (j == resources)
                    {
                        for (j = 0; j < resources; j++)
                            ava[j] += allocation[i][j];
                        safeSequence[count++] = i;
                        finish[i] = true;
                        found = true;
                    }
                }
            }
            if (!found)
            {
                throw runtime_error("System is not in a safe state.");
            }
        }

        cout << "System is in a safe state.\nSafe sequence: ";
        for (int i = 0; i < processes; i++)
            cout << safeSequence[i] << " ";
        cout << "\n";
        return true;
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << endl;
        return false;
    }
}

// Entry point of the program
int main()
{

    int processes, resources;
    cout << "Enter number of processes: ";
    if (!(cin >> processes) || processes <= 0)
        throw runtime_error("Invalid number of processes!");

    cout << "Enter number of resources: ";
    if (!(cin >> resources) || resources <= 0)
        throw runtime_error("Invalid number of resources!");

    int allocation[10][10], max[10][10], need[10][10], available[10];
    inputData(processes, resources, allocation, max, available);

    calculateNeedMatrix(processes, resources, max, allocation, need);
    isSafeState(processes, resources, allocation, need, available);

    return 0;
}
