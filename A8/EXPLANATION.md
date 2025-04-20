# A8: File System Implementation with Advanced Features

This assignment implements an advanced file system with features like journaling, caching, and RAID simulation.

## Files and Their Purposes

### A8.cpp

- **Purpose**: Implements an advanced file system
- **Functionality**:
  - File system features:
    - Journaling
    - File caching
    - RAID simulation
    - File compression
    - Encryption
  - Advanced operations:
    - Atomic operations
    - Transaction support
    - Backup and recovery
    - File system check

## Key Concepts Demonstrated

- File system journaling
- Caching mechanisms
- RAID levels
- Data compression
- File encryption
- System recovery

## Syntax and Usage

### Journaling Operations

```cpp
// Journal entry structure
struct JournalEntry {
    int transactionId;
    string operation;
    string data;
    bool committed;
};

// Journal operations
class Journal {
    vector<JournalEntry> entries;
public:
    void logOperation(string operation, string data);
    void commitTransaction(int transactionId);
    void rollbackTransaction(int transactionId);
};
```

### Cache Management

```cpp
// Cache entry
struct CacheEntry {
    string key;
    string value;
    time_t lastAccess;
    int frequency;
};

// Cache operations
class FileCache {
    map<string, CacheEntry> cache;
    int maxSize;
public:
    void put(string key, string value);
    string get(string key);
    void evict();
};
```

### RAID Operations

```cpp
// RAID configuration
enum RAIDLevel {
    RAID0,
    RAID1,
    RAID5
};

// RAID operations
class RAID {
    RAIDLevel level;
    vector<Disk> disks;
public:
    void writeData(string data);
    string readData();
    void rebuildDisk(int failedDisk);
};
```

### File Operations

```cpp
// File operations with compression
class CompressedFile {
    string compress(string data);
    string decompress(string compressedData);
    void writeCompressed(string filename, string data);
    string readCompressed(string filename);
};

// File operations with encryption
class EncryptedFile {
    string encrypt(string data, string key);
    string decrypt(string encryptedData, string key);
    void writeEncrypted(string filename, string data, string key);
    string readEncrypted(string filename, string key);
};
```

## How to Run

1. Compile using g++:
   ```bash
   g++ A8.cpp -o A8
   ```
2. Run the executable:
   ```bash
   ./A8
   ```
3. Follow the prompts to:
   - Test file system features
   - Perform advanced operations
   - Simulate system failures
   - Test recovery mechanisms
