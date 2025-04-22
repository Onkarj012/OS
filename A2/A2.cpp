#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

class Process
{
public:
    int id, at, bt, ct, tat, wt, rt, rmt, priority;         // Process attributes
    void input(vector<Process> &p, int n, bool isPriority); // Input process details
    void FCFS(vector<Process> &p, int n);                   // First-Come, First-Served scheduling
    void SJF_NonPreemptive(vector<Process> &p, int n);      // Non-Preemptive Shortest Job First scheduling
    void SJF_Preemptive(vector<Process> &p, int n);         // Preemptive Shortest Job First (SRTF) scheduling
    void RoundRobin(vector<Process> &p, int n, int tq);     // Round Robin scheduling
    void Priority_NonPreemptive(vector<Process> &p, int n); // Non-Preemptive Priority scheduling
    void Priority_Preemptive(vector<Process> &p, int n);    // Preemptive Priority scheduling
    void output(const vector<Process> &p, int n);           // Output process details
    static bool comp(Process a, Process b);                 // Comparator for sorting by arrival time
    static bool compPriority(Process a, Process b);         // Comparator for sorting by priority
};

// Comparator function to sort processes by arrival time
bool Process::comp(Process a, Process b)
{
    return a.at < b.at;
}

bool Process::compPriority(Process a, Process b)
{
    if (a.at == b.at)
        return a.priority < b.priority;
    return a.at < b.at;
}

// Function to input process details
void Process::input(vector<Process> &p, int n, bool isPriority)
{
    cout << "Enter arrival time and burst time for each process:\n";
    for (int i = 0; i < n; i++)
    {
        try
        {
            cout << "Process " << i + 1 << ": ";
            if (!(cin >> p[i].at >> p[i].bt) || p[i].at < 0 || p[i].bt <= 0)
                throw invalid_argument("Invalid input. Arrival time must be non-negative, burst time must be positive.");
            p[i].id = i + 1;
            p[i].rmt = p[i].bt;
            if (isPriority)
            {
                cout << "Enter priority: ";
                if (!(cin >> p[i].priority) || p[i].priority < 0)
                    throw invalid_argument("Invalid input. Priority must be non-negative.");
            }
        }
        catch (const exception &e)
        {
            cerr << "Error: " << e.what() << "\n";
            exit(1);
        }
    }
    sort(p.begin(), p.end(), comp); // Sort processes by arrival time
}

// Function to perform FCFS scheduling
void Process::FCFS(vector<Process> &p, int n)
{
    int sum = p[0].at;
    for (int i = 0; i < n; i++)
    {
        if (p[i].at > sum)
            sum = p[i].at;
        p[i].ct = sum + p[i].bt;
        sum = p[i].ct;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }
}

// Function to perform Non-Preemptive SJF scheduling
void Process::SJF_NonPreemptive(vector<Process> &p, int n)
{
    int completed = 0, currentTime = 0;
    vector<bool> isCompleted(n, false);
    while (completed < n)
    {
        int currentProcess = -1;
        for (int i = 0; i < n; i++)
        {
            if (!isCompleted[i] && p[i].at <= currentTime)
            {
                if (currentProcess == -1 || p[i].bt < p[currentProcess].bt)
                    currentProcess = i;
            }
        }
        if (currentProcess != -1)
        {
            currentTime += p[currentProcess].bt;
            p[currentProcess].ct = currentTime;
            p[currentProcess].tat = p[currentProcess].ct - p[currentProcess].at;
            p[currentProcess].wt = p[currentProcess].tat - p[currentProcess].bt;
            isCompleted[currentProcess] = true;
            completed++;
        }
        else
        {
            currentTime++;
        }
    }
}

// Function to perform Preemptive SJF (SRTF) scheduling
void Process::SJF_Preemptive(vector<Process> &p, int n)
{
    vector<int> remainingTime(n);
    vector<bool> isCompleted(n, false);
    int completed = 0, currentTime = p[0].at;
    for (int i = 0; i < n; i++)
        remainingTime[i] = p[i].bt;

    while (completed < n)
    {
        int minRemaining = INT_MAX, currentProcess = -1;
        for (int i = 0; i < n; i++)
        {
            if (!isCompleted[i] && p[i].at <= currentTime && remainingTime[i] < minRemaining && remainingTime[i] > 0)
            {
                minRemaining = remainingTime[i];
                currentProcess = i;
            }
        }
        if (currentProcess == -1)
        {
            currentTime++;
            continue;
        }
        remainingTime[currentProcess]--;
        currentTime++;
        if (remainingTime[currentProcess] == 0)
        {
            isCompleted[currentProcess] = true;
            p[currentProcess].ct = currentTime;
            p[currentProcess].tat = p[currentProcess].ct - p[currentProcess].at;
            p[currentProcess].wt = p[currentProcess].tat - p[currentProcess].bt;
            completed++;
        }
    }
}

// Function to perform Round Robin scheduling
void Process::RoundRobin(vector<Process> &p, int n, int tq)
{
    vector<int> remainingTime(n);
    int currentTime = 0, completed = 0;
    for (int i = 0; i < n; i++)
        remainingTime[i] = p[i].bt;
    while (completed < n)
    {
        bool found = false;
        for (int i = 0; i < n; i++)
        {
            if (remainingTime[i] > 0 && p[i].at <= currentTime)
            {
                found = true;
                int execTime = min(remainingTime[i], tq);
                remainingTime[i] -= execTime;
                currentTime += execTime;
                if (remainingTime[i] == 0)
                {
                    p[i].ct = currentTime;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;
                    completed++;
                }
            }
        }
        if (!found)
            currentTime++;
    }
}

// Function to perform Non-Preemptive Priority Scheduling
void Process::Priority_NonPreemptive(vector<Process> &p, int n)
{
    sort(p.begin(), p.end(), compPriority());

    int sum = p[0].at;
    for (int i = 0; i < n; i++)
    {
        if (p[i].at > sum)
            sum = p[i].at;
        p[i].ct = sum + p[i].bt;
        sum = p[i].ct;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }
}

// Function to perform Preemptive Priority Scheduling
void Process::Priority_Preemptive(vector<Process> &p, int n)
{
    vector<int> remainingTime(n);
    vector<bool> isCompleted(n, false);
    int completed = 0, currentTime = p[0].at;
    for (int i = 0; i < n; i++)
        remainingTime[i] = p[i].bt;

    while (completed < n)
    {
        int highestPriority = INT_MAX, currentProcess = -1;
        for (int i = 0; i < n; i++)
        {
            if (!isCompleted[i] && p[i].at <= currentTime && p[i].priority < highestPriority && remainingTime[i] > 0)
            {
                highestPriority = p[i].priority;
                currentProcess = i;
            }
        }
        if (currentProcess == -1)
        {
            currentTime++;
            continue;
        }
        remainingTime[currentProcess]--;
        currentTime++;
        if (remainingTime[currentProcess] == 0)
        {
            isCompleted[currentProcess] = true;
            p[currentProcess].ct = currentTime;
            p[currentProcess].tat = p[currentProcess].ct - p[currentProcess].at;
            p[currentProcess].wt = p[currentProcess].tat - p[currentProcess].bt;
            completed++;
        }
    }
}

// Function to output process details
void Process::output(const vector<Process> &p, int n)
{
    cout << "\nProcessID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
    float avgTat = 0, avgWt = 0;
    for (int i = 0; i < n; i++)
    {
        cout << p[i].id << "\t\t" << p[i].at << "\t" << p[i].bt << "\t"
             << p[i].ct << "\t\t" << p[i].tat << "\t\t" << p[i].wt
             << "\n";
        avgTat += p[i].tat;
        avgWt += p[i].wt;
    }
    cout << "Average Turnaround Time: " << avgTat / n << "\n";
    cout << "Average Waiting Time: " << avgWt / n << "\n";
}

// Entry point of the program
int main()
{
    try
    {
        int n, choice, tq;
        cout << "Enter number of processes: ";
        if (!(cin >> n) || n <= 0)
            throw invalid_argument("Invalid input. Number of processes must be positive.");

        vector<Process> processes(n);
        Process pManager;

        cout << "\nSelect Scheduling Algorithm:\n"
             << "1. FCFS\n"
             << "2. SJF (Non-Preemptive)\n"
             << "3. SJF (Preemptive)\n"
             << "4. Round Robin\n"
             << "5. Priority Scheduling (Non-Preemptive)\n"
             << "6. Priority Scheduling (Preemptive)\n"
             << "Choice: ";
        if (!(cin >> choice) || choice < 1 || choice > 6)
            throw invalid_argument("Invalid choice.");

        bool isPriority = (choice == 5 || choice == 6);
        pManager.input(processes, n, isPriority);

        if (choice == 4)
        {
            cout << "Enter Time Quantum: ";
            if (!(cin >> tq) || tq <= 0)
                throw invalid_argument("Invalid input. Time quantum must be positive.");
        }

        switch (choice)
        {
        case 1:
            pManager.FCFS(processes, n);
            break;
        case 2:
            pManager.SJF_NonPreemptive(processes, n);
            break;
        case 3:
            pManager.SJF_Preemptive(processes, n);
            break;
        case 4:
            pManager.RoundRobin(processes, n, tq);
            break;
        case 5:
            pManager.Priority_NonPreemptive(processes, n);
            break;
        case 6:
            pManager.Priority_Preemptive(processes, n);
            break;
        }
        pManager.output(processes, n);
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}