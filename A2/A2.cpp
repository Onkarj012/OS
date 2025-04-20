// This program simulates various CPU scheduling algorithms.
// It includes FCFS, SJF, Round Robin, and Priority Scheduling.

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
    void SJF(vector<Process> &p, int n);                    // Shortest Job First scheduling
    void RoundRobin(vector<Process> &p, int n, int tq);     // Round Robin scheduling
    void PriorityScheduling(vector<Process> &p, int n);     // Priority scheduling
    void output(const vector<Process> &p, int n);           // Output process details
    static bool comp(Process a, Process b);                 // Comparator for sorting by arrival time
};

// Comparator function to sort processes by arrival time
bool Process::comp(Process a, Process b)
{
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

// Function to perform SJF scheduling
void Process::SJF(vector<Process> &p, int n)
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
                    cout << currentTime << ":" << p[i].id << endl;
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

// Function to perform Priority Scheduling
void Process::PriorityScheduling(vector<Process> &p, int n)
{
    sort(p.begin(), p.end(), [](Process a, Process b)
         {
        if (a.at == b.at)
            return a.priority < b.priority;
        return a.at < b.at; });

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

        cout << "\nSelect Scheduling Algorithm:\n1. FCFS\n2. SJF\n3. Round Robin\n4. Priority Scheduling\nChoice: ";
        if (!(cin >> choice) || choice < 1 || choice > 4)
            throw invalid_argument("Invalid choice.");
        bool isPriority = (choice == 4);
        pManager.input(processes, n, isPriority);
        if (choice == 3)
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
            pManager.SJF(processes, n);
            break;
        case 3:
            pManager.RoundRobin(processes, n, tq);
            break;
        case 4:
            pManager.PriorityScheduling(processes, n);
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
