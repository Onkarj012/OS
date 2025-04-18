#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
#include <stdexcept>

using namespace std;

#define DISK_SIZE 200 // Assuming disk has cylinders 0 to 199

// FCFS Disk Scheduling
int FCFS(int requests[], int n, int head)
{
    int seek_time = 0;
    int current = head;

    for (int i = 0; i < n; i++)
    {
        seek_time += abs(requests[i] - current);
        current = requests[i];
    }
    return seek_time;
}

// SCAN Disk Scheduling (Elevator Algorithm)
int Scan(int requests[], int n, int head)
{
    vector<int> left, right;
    int seek_time = 0;

    for (int i = 0; i < n; i++)
    {
        if (requests[i] < head)
            left.push_back(requests[i]);
        else
            right.push_back(requests[i]);
    }

    sort(left.begin(), left.end(), greater<int>());
    sort(right.begin(), right.end());

    for (int i = 0; i < right.size(); i++)
    {
        seek_time += abs(right[i] - head);
        head = right[i];
    }

    if (head != DISK_SIZE - 1)
    {
        seek_time += abs((DISK_SIZE - 1) - head);
        head = DISK_SIZE - 1;
    }

    for (int i = 0; i < left.size(); i++)
    {
        seek_time += abs(head - left[i]);
        head = left[i];
    }

    return seek_time;
}

// C-SCAN Disk Scheduling (Circular SCAN)
int CScan(int requests[], int n, int head)
{
    vector<int> left, right;
    int seek_time = 0;

    for (int i = 0; i < n; i++)
    {
        if (requests[i] < head)
            left.push_back(requests[i]);
        else
            right.push_back(requests[i]);
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    for (int i = 0; i < right.size(); i++)
    {
        seek_time += abs(right[i] - head);
        head = right[i];
    }

    if (head != DISK_SIZE - 1)
    {
        seek_time += abs((DISK_SIZE - 1) - head);
        head = DISK_SIZE - 1;
    }

    seek_time += DISK_SIZE - 1;
    head = 0;

    for (int i = 0; i < left.size(); i++)
    {
        seek_time += abs(left[i] - head);
        head = left[i];
    }

    return seek_time;
}

// SSTF Disk Scheduling (Shortest Seek Time First)
int SSTF(int requests[], int n, int head)
{
    try
    {
        vector<int> remaining(requests, requests + n);
        int seek_time = 0;
        int current = head;

        while (!remaining.empty())
        {
            int min_dist = INT_MAX, min_idx = -1;

            for (int i = 0; i < remaining.size(); i++)
            {
                int dist = abs(remaining[i] - current);
                if (dist < min_dist)
                {
                    min_dist = dist;
                    min_idx = i;
                }
            }

            if (min_idx == -1)
                throw runtime_error("Error finding next closest request.");

            seek_time += min_dist;
            current = remaining[min_idx];
            remaining.erase(remaining.begin() + min_idx);
        }

        return seek_time;
    }
    catch (const exception &e)
    {
        cerr << "Exception in SSTF: " << e.what() << endl;
        return -1;
    }
}

int main()
{
    try
    {
        int n, head;
        cout << "Enter the number of requests: ";
        cin >> n;

        if (n <= 0)
            throw invalid_argument("Number of requests must be positive.");

        int requests[n];
        cout << "Enter the requests: ";
        for (int i = 0; i < n; i++)
        {
            cin >> requests[i];
            if (requests[i] < 0 || requests[i] >= DISK_SIZE)
                throw out_of_range("Request out of disk range (0-199).");
        }

        cout << "Enter the initial head position: ";
        cin >> head;
        if (head < 0 || head >= DISK_SIZE)
            throw out_of_range("Head position out of disk range (0-199).");

        cout << "\n--- Disk Scheduling Results ---\n";
        cout << "FCFS Seek Time   : " << FCFS(requests, n, head) << endl;
        cout << "SSTF Seek Time   : " << SSTF(requests, n, head) << endl;
        cout << "SCAN Seek Time   : " << Scan(requests, n, head) << endl;
        cout << "C-SCAN Seek Time : " << CScan(requests, n, head) << endl;
    }
    catch (const exception &e)
    {
        cerr << "Input Error: " << e.what() << endl;
    }

    return 0;
}
