# A5: Process Synchronization and Deadlock

This assignment implements process synchronization techniques and deadlock handling mechanisms.

## Files and Their Purposes

### A5.cpp

- **Purpose**: Implements process synchronization and deadlock handling
- **Functionality**:
  - Synchronization mechanisms:
    - Semaphores
    - Mutex locks
    - Monitors
    - Condition variables
  - Deadlock handling:
    - Deadlock prevention
    - Deadlock avoidance
    - Deadlock detection
    - Deadlock recovery

## Key Concepts Demonstrated

- Process synchronization
- Critical section handling
- Deadlock conditions
- Resource allocation
- Process coordination
- Mutual exclusion

## Syntax and Usage

### Synchronization Primitives

```cpp
// Semaphore operations
class Semaphore {
    int value;
    queue<Process> waiting;
public:
    void wait();    // P operation
    void signal();  // V operation
};

// Mutex operations
class Mutex {
    bool locked;
public:
    void lock();
    void unlock();
};

// Monitor operations
class Monitor {
    ConditionVariable cv;
    void enter();
    void leave();
    void wait();
    void signal();
};
```

### Deadlock Handling

```cpp
// Resource allocation graph
class ResourceAllocationGraph {
    vector<Process> processes;
    vector<Resource> resources;
    bool detectDeadlock();
    void recoverFromDeadlock();
};

// Banker's algorithm
class Banker {
    vector<int> available;
    vector<vector<int>> max;
    vector<vector<int>> allocation;
    bool isSafe();
    bool requestResources(int process, vector<int> request);
};
```

## How to Run

1. Compile using g++:
   ```bash
   g++ A5.cpp -o A5
   ```
2. Run the executable:
   ```bash
   ./A5
   ```
3. Follow the prompts to:
   - Test synchronization mechanisms
   - Simulate deadlock scenarios
   - Apply deadlock handling techniques
   - View process execution results
