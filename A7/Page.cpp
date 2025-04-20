// This program simulates different page replacement algorithms.
// It includes FIFO, LRU, and Optimal page replacement strategies.

#include <iostream>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <climits>
using namespace std;

// Function to simulate FIFO page replacement
int FIFO(int pages[], int n, int capacity)
{
    unordered_set<int> s; // Set to store current pages in memory
    queue<int> indexes;   // Queue to track the order of pages
    int page_faults = 0;  // Count of page faults

    cout << "\n--- FIFO Page Replacement ---\n";
    for (int i = 0; i < n; i++)
    {
        cout << "Page " << pages[i] << ": ";
        if (s.find(pages[i]) == s.end())
        {
            if (s.size() < capacity)
            {
                s.insert(pages[i]);
                indexes.push(pages[i]);
            }
            else
            {
                int val = indexes.front();
                indexes.pop();
                s.erase(val);

                s.insert(pages[i]);
                indexes.push(pages[i]);
            }
            page_faults++;
            cout << "Miss";
        }
        else
        {
            cout << "Hit";
        }

        cout << " | Frames: ";
        queue<int> temp = indexes;
        while (!temp.empty())
        {
            cout << temp.front() << " ";
            temp.pop();
        }
        cout << endl;
    }
    return page_faults;
}

// Function to simulate LRU page replacement
int LRU(int pages[], int n, int capacity)
{
    unordered_set<int> s;            // Set to store current pages in memory
    unordered_map<int, int> indexes; // Map to store the last used index of pages
    int page_faults = 0;             // Count of page faults

    cout << "\n--- LRU Page Replacement ---\n";
    for (int i = 0; i < n; i++)
    {
        cout << "Page " << pages[i] << ": ";
        if (s.size() < capacity)
        {
            if (s.find(pages[i]) == s.end())
            {
                s.insert(pages[i]);
                page_faults++;
                cout << "Miss";
            }
            else
            {
                cout << "Hit";
            }
            indexes[pages[i]] = i;
        }
        else
        {
            if (s.find(pages[i]) == s.end())
            {
                int lru = INT_MAX, val;
                for (unordered_set<int>::iterator it = s.begin(); it != s.end(); it++)
                {
                    if (indexes[*it] < lru)
                    {
                        lru = indexes[*it];
                        val = *it;
                    }
                }

                s.erase(val);
                s.insert(pages[i]);
                page_faults++;
                cout << "Miss";
            }
            else
            {
                cout << "Hit";
            }
            indexes[pages[i]] = i;
        }

        cout << " | Frames: ";
        for (auto page : s)
            cout << page << " ";
        cout << endl;
    }
    return page_faults;
}

// Function to simulate Optimal page replacement
int optimal(int pages[], int n, int capacity)
{
    unordered_set<int> s; // Set to store current pages in memory
    int page_faults = 0;  // Count of page faults

    cout << "\n--- Optimal Page Replacement ---\n";
    for (int i = 0; i < n; i++)
    {
        cout << "Page " << pages[i] << ": ";
        if (s.size() < capacity)
        {
            if (s.find(pages[i]) == s.end())
            {
                s.insert(pages[i]);
                page_faults++;
                cout << "Miss";
            }
            else
            {
                cout << "Hit";
            }
        }
        else
        {
            if (s.find(pages[i]) == s.end())
            {
                int farthest = -1, val;
                for (unordered_set<int>::iterator it = s.begin(); it != s.end(); it++)
                {
                    int j;
                    for (j = i + 1; j < n; j++)
                    {
                        if (pages[j] == *it)
                        {
                            if (j > farthest)
                            {
                                farthest = j;
                                val = *it;
                            }
                            break;
                        }
                    }

                    if (j == n)
                    {
                        val = *it;
                        break;
                    }
                }
                s.erase(val);
                s.insert(pages[i]);
                page_faults++;
                cout << "Miss";
            }
            else
            {
                cout << "Hit";
            }
        }

        cout << " | Frames: ";
        for (auto page : s)
            cout << page << " ";
        cout << endl;
    }
    return page_faults;
}

// Entry point of the program
int main()
{
    try
    {
        int n;
        cout << "Enter the number of pages: ";
        cin >> n;

        if (n <= 0)
            throw runtime_error("Page count must be positive.");

        int pages[n];
        cout << "Enter the page reference sequence:\n";
        for (int i = 0; i < n; i++)
        {
            cin >> pages[i];
        }

        int capacity;
        cout << "Enter the number of frames (capacity): ";
        cin >> capacity;
        if (capacity <= 0)
            throw runtime_error("Capacity must be positive.");

        int choice;
        do
        {
            cout << "\nChoose a Page Replacement Algorithm:\n";
            cout << "1. FIFO\n";
            cout << "2. LRU\n";
            cout << "3. Optimal\n";
            cout << "4. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            int faults = 0;
            switch (choice)
            {
            case 1:
                faults = FIFO(pages, n, capacity);
                cout << "Total Page Faults (FIFO): " << faults << "\n";
                break;
            case 2:
                faults = LRU(pages, n, capacity);
                cout << "Total Page Faults (LRU): " << faults << "\n";
                break;
            case 3:
                faults = optimal(pages, n, capacity);
                cout << "Total Page Faults (Optimal): " << faults << "\n";
                break;
            case 4:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 4);
    }
    catch (exception &e)
    {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
