# A6: Interprocess Communication

This assignment implements various interprocess communication (IPC) mechanisms.

## Files and Their Purposes

### A6.cpp

- **Purpose**: Implements different IPC mechanisms
- **Functionality**:
  - IPC mechanisms:
    - Pipes
    - Shared memory
    - Message queues
    - Sockets
  - Communication patterns:
    - Producer-consumer
    - Client-server
    - Publish-subscribe

## Key Concepts Demonstrated

- Interprocess communication
- Process coordination
- Data sharing
- Message passing
- Synchronization
- Network communication

## Syntax and Usage

### Pipe Operations

```cpp
// Create a pipe
int pipefd[2];
pipe(pipefd);

// Write to pipe
write(pipefd[1], buffer, size);

// Read from pipe
read(pipefd[0], buffer, size);
```

### Shared Memory

```cpp
// Create shared memory segment
int shmid = shmget(key, size, IPC_CREAT | 0666);

// Attach shared memory
void* shm = shmat(shmid, NULL, 0);

// Detach shared memory
shmdt(shm);
```

### Message Queue

```cpp
// Create message queue
int msgid = msgget(key, IPC_CREAT | 0666);

// Send message
msgsnd(msgid, &message, sizeof(message), 0);

// Receive message
msgrcv(msgid, &message, sizeof(message), type, 0);
```

### Socket Communication

```cpp
// Server side
int server_fd = socket(AF_INET, SOCK_STREAM, 0);
bind(server_fd, (struct sockaddr*)&address, sizeof(address));
listen(server_fd, 3);
int new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen);

// Client side
int sock = socket(AF_INET, SOCK_STREAM, 0);
connect(sock, (struct sockaddr*)&address, sizeof(address));
```

## How to Run

1. Compile using g++:
   ```bash
   g++ A6.cpp -o A6
   ```
2. Run the executable:
   ```bash
   ./A6
   ```
3. Follow the prompts to:
   - Test different IPC mechanisms
   - Choose communication pattern
   - Send/receive messages
   - View communication results
