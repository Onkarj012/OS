#include <iostream>
using namespace std;

void inputData(int processes, int resources, int allocation[][10], int max[][10], int available[]) {
    cout << "Enter allocation matrix:\n";
    for (int i = 0; i < processes; i++)
        for (int j = 0; j < resources; j++)
            cin >> allocation[i][j];

    cout << "Enter max matrix:\n";
    for (int i = 0; i < processes; i++)
        for (int j = 0; j < resources; j++)
            cin >> max[i][j];

    cout << "Enter available resources:\n";
    for (int i = 0; i < resources; i++)
        cin >> available[i];
}

void calculateNeedMatrix(int processes, int resources, int max[][10], int allocation[][10], int need[][10]) {
    for (int i = 0; i < processes; i++)
        for (int j = 0; j < resources; j++)
            need[i][j] = max[i][j] - allocation[i][j];
}

bool isSafeState(int processes, int resources, int allocation[][10], int need[][10], int available[]) {
    bool finish[processes];
    for (int i = 0; i < processes; i++)
        finish[i] = false;
    int ava[10], safeSequence[processes], count = 0;
    for (int i = 0; i < resources; i++)
        ava[i] = available[i];

    while (count < processes) {
        bool found = false;
        for (int i = 0; i < processes; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < resources; j++)
                    if (need[i][j] > ava[j])
                        break;
                if (j == resources) {
                    for (j = 0; j < resources; j++)
                        ava[j] += allocation[i][j];
                    safeSequence[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            cout << "System is not in safe state.\n";
            return false;
        }
    }
    cout << "System is in safe state.\nSafe sequence: ";
    for (int i = 0; i < processes; i++)
        cout << safeSequence[i] << " ";
    cout << "\n";
    return true;
}

int main() {
    int processes, resources;
    cout << "Enter number of processes: ";
    cin >> processes;
    cout << "Enter number of resources: ";
    cin >> resources;
    
    int allocation[10][10], max[10][10], need[10][10], available[10];
    inputData(processes, resources, allocation, max, available);
    
    calculateNeedMatrix(processes, resources, max, allocation, need);
    isSafeState(processes, resources, allocation, need, available);
    
    return 0;
}