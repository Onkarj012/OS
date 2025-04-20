# A3: Memory Management and Page Replacement Algorithms

This assignment implements memory management techniques and page replacement algorithms to demonstrate different memory allocation and page replacement strategies.

## Files and Their Purposes

### A3.cpp

- **Purpose**: Implements memory management and page replacement algorithms
- **Functionality**:
  - Implements the following page replacement algorithms:
    - First-In-First-Out (FIFO)
    - Least Recently Used (LRU)
    - Optimal Page Replacement
  - Memory management features:
    - Fixed partitioning
    - Dynamic partitioning
    - Best fit allocation
    - Worst fit allocation
    - First fit allocation
  - Calculates and displays:
    - Page faults
    - Page hits
    - Memory utilization
    - Fragmentation

## Key Concepts Demonstrated

- Page replacement algorithms
- Memory allocation strategies
- Virtual memory management
- Page fault handling
- Memory fragmentation
- Memory partitioning techniques

## How to Run

1. Compile using g++:
   ```bash
   g++ A3.cpp -o A3
   ```
2. Run the executable:
   ```bash
   ./A3
   ```
3. Follow the prompts to:
   - Select memory management technique
   - Choose page replacement algorithm
   - Input memory requirements
   - View results
