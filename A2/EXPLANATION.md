# A2: CPU Scheduling Algorithms

This assignment implements various CPU scheduling algorithms to demonstrate different process scheduling strategies.

## Files and Their Purposes

### A2.cpp

- **Purpose**: Implements multiple CPU scheduling algorithms
- **Functionality**:
  - Implements the following scheduling algorithms:
    - First-Come-First-Serve (FCFS)
    - Shortest Job First (SJF)
    - Priority Scheduling
    - Round Robin (RR)
  - Calculates and displays:
    - Completion Time
    - Turnaround Time
    - Waiting Time
    - Average Waiting Time
  - Takes input for:
    - Number of processes
    - Arrival Time
    - Burst Time
    - Priority (for Priority Scheduling)
    - Time Quantum (for Round Robin)

## Key Concepts Demonstrated

- Process scheduling algorithms
- CPU scheduling metrics
- Time calculations
- Priority-based scheduling
- Preemptive vs Non-preemptive scheduling
- Queue management

## How to Run

1. Compile using g++:
   ```bash
   g++ A2.cpp -o A2
   ```
2. Run the executable:
   ```bash
   ./A2
   ```
3. Follow the prompts to:
   - Enter number of processes
   - Input process details
   - Select scheduling algorithm
   - View results
