# OS

# OS Assignments

This repository contains various assignments related to Operating Systems, each focusing on different concepts and algorithms. Below is a brief description of each assignment:

## A1: Basic Linux Command Simulation

- **copy.c**: Simulates the `cp` command to copy contents from one file to another.
- **A1.c**: Provides a menu-driven interface to simulate basic Linux commands like `cp` and `grep` using custom implementations and system calls.
- **grep.c**: Simulates the `grep` command to search for patterns in a file, with an optional `-c` flag to count occurrences.
- **fork.c**: Demonstrates the use of `fork` to create a child process, printing messages from both parent and child processes.

## A2: CPU Scheduling Algorithms

- **A2.cpp**: Simulates various CPU scheduling algorithms including First-Come, First-Served (FCFS), Shortest Job First (SJF), Round Robin, and Priority Scheduling.

## A3: Pipe and Fork Demonstration

- **pipe.c**: Demonstrates the use of pipes and `fork` to execute `sort` and `uniq` commands, allowing the user to choose between sorting, finding unique entries, or both.

## A4: Reader-Writer Problem

- **A4.cpp**: Simulates a banking application using the reader-writer problem, allowing multiple customers to check their balance simultaneously while ensuring exclusive access for deposits.
- **nosync.cpp**: Simulates a banking application without synchronization, demonstrating potential race conditions when multiple threads access shared data.

## A5: Banker's Algorithm

- **Banker.cpp**: Implements the Banker's Algorithm to determine if a system is in a safe state, checking if resources can be allocated to each process in some order to avoid deadlock.

## A6: Memory Allocation Strategies

- **memory.cpp**: Simulates different memory allocation strategies including First Fit, Best Fit, Worst Fit, and Next Fit algorithms.

## A7: Page Replacement Algorithms

- **Page.cpp**: Simulates different page replacement algorithms including FIFO, LRU, and Optimal page replacement strategies.

## A8: Disk Scheduling Algorithms

- **disk.cpp**: Simulates different disk scheduling algorithms including FCFS, SSTF, SCAN, and C-SCAN strategies.

Each assignment is designed to provide hands-on experience with key operating system concepts and algorithms. Explore each directory for source code and further details.
