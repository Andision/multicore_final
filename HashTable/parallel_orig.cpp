#include <cstdio>
#include <cstdlib>
#include <functional>
#include <omp.h>

// Hash slot states
enum SlotStatus { EMPTY, OCCUPIED, DELETED };

// Hash slot structure
struct HashSlot {
    int key;             // Key in the hash slot
    int value;           // Value in the hash slot
    SlotStatus status;   // Status of the hash slot
};

// Hash table structure
struct HashTable {
    HashSlot* table;    // Pointer to the array of hash slots
    int capacity;       // Capacity of the hash table
};

// Primary hash function using std::hash
int hash1(int key, int capacity) {
    std::hash<int> hasher;
    return hasher(key) % capacity;  // Use std::hash and take modulo of capacity
}

// Secondary hash function for double hashing
int hash2(int key, int capacity) {
    return 1 + (key % (capacity - 1));  // Ensure hash2(key) is non-zero
}

// Conflict resolution function using double hashing
int probe(int idx, int i, int key, int capacity) {
    return (idx + i * hash2(key, capacity)) % capacity;  // Compute the probing index
}

// Find a key in the hash table
int findSlot(HashTable* ht, int key) {
    int idx = hash1(key, ht->capacity);  // Get the primary hash index
    for (int i = 0; i < ht->capacity; ++i) {
        int probe_idx = probe(idx, i, key, ht->capacity);  // Calculate the probing index
        if (ht->table[probe_idx].status == EMPTY) {
            return -1;  // Not found
        }
        if (ht->table[probe_idx].status == OCCUPIED && ht->table[probe_idx].key == key) {
            return probe_idx;  // Key found
        }
    }
    return -1;  // Not found
}

// Initialize the hash table
void initHashTable(HashTable* ht, int capacity) {
    ht->capacity = capacity;
    ht->table = (HashSlot*)malloc(sizeof(HashSlot) * capacity);  // Allocate memory for the table
    for (int i = 0; i < capacity; ++i) {
        ht->table[i].status = EMPTY;  // Initialize all slots as empty
    }
}

// Destroy the hash table
void destroyHashTable(HashTable* ht) {
    free(ht->table);  // Free the allocated memory
}

// Insert a key-value pair into the hash table
int insert(HashTable* ht, int key, int value) {
    if (findSlot(ht, key) != -1) {
        return 0;  // Key already exists
    }

    int idx = hash1(key, ht->capacity);  // Get the primary hash index
    for (int i = 0; i < ht->capacity; ++i) {
        int probe_idx = probe(idx, i, key, ht->capacity);  // Calculate the probing index
        if (ht->table[probe_idx].status == EMPTY || ht->table[probe_idx].status == DELETED) {
            #pragma omp critical
            {
                ht->table[probe_idx].key = key;      // Insert the key
                ht->table[probe_idx].value = value;  // Insert the value
                ht->table[probe_idx].status = OCCUPIED;  // Mark the slot as occupied
            }
            return 1;
        }
    }
    return 0;  // Table is full
}

// Remove a key from the hash table
int remove(HashTable* ht, int key) {
    int slot = findSlot(ht, key);  // Find the slot for the key
    if (slot != -1) {
        #pragma omp critical
        {
            ht->table[slot].status = DELETED;  // Mark the slot as deleted
        }
        return 1;
    }
    return 0;  // Key not found
}

// Update the value associated with a key
int update(HashTable* ht, int key, int newValue) {
    int slot = findSlot(ht, key);  // Find the slot for the key
    if (slot != -1) {
        #pragma omp critical
        {
            ht->table[slot].value = newValue;  // Update the value
        }
        return 1;
    }
    return 0;  // Key not found
}

// Search for a key in the hash table
int search(HashTable* ht, int key) {
    int slot = findSlot(ht, key);  // Find the slot for the key
    if (slot != -1) {
        return ht->table[slot].value;  // Return the associated value
    }
    return -1;  // Key not found
}

// Execute batch operations from a file (sequential implementation)
void executeBatch(HashTable* ht, const char* filename) {
    FILE* file = fopen(filename, "r");  // Open the file
    if (!file) {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        return;
    }

    int numOperations;
    fscanf(file, "%d", &numOperations);  // Read the number of operations

    for (int i = 0; i < numOperations; ++i) {
        char op[3];
        fscanf(file, "%s", op);  // Read the operation

        if (op[0] == 'B') {
            int batchSize;
            fscanf(file, "%d", &batchSize);  // Read batch size
            for (int j = 0; j < batchSize; ++j) {
                int key, value;
                if (op[1] == 'I') {  // Batch Insert
                    fscanf(file, "%d %d", &key, &value);
                    if (insert(ht, key, value)) {
                        printf("Inserted (%d, %d)\n", key, value);
                    } else {
                        printf("Insert failed: %d\n", key);
                    }
                } else if (op[1] == 'S') {  // Batch Search
                    fscanf(file, "%d", &key);
                    int result = search(ht, key);
                    printf("Search %d: %d\n", key, result);
                }
            }
        } else {
            int key, value;
            if (op[0] == 'I') {  // Insert operation
                fscanf(file, "%d %d", &key, &value);
                if (insert(ht, key, value)) {
                    printf("Inserted (%d, %d)\n", key, value);
                } else {
                    printf("Insert failed: %d\n", key);
                }
            } else if (op[0] == 'R') {  // Remove operation
                fscanf(file, "%d", &key);
                if (remove(ht, key)) {
                    printf("Removed %d\n", key);
                } else {
                    printf("Remove failed: %d\n", key);
                }
            } else if (op[0] == 'U') {  // Update operation
                fscanf(file, "%d %d", &key, &value);
                if (update(ht, key, value)) {
                    printf("Updated (%d, %d)\n", key, value);
                } else {
                    printf("Update failed: %d\n", key);
                }
            } else if (op[0] == 'S') {  // Search operation
                fscanf(file, "%d", &key);
                int result = search(ht, key);
                printf("%d\n", result);
            }
        }
    }

    fclose(file);  // Close the file
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <table_size> <input_file>\n", argv[0]);  // Check arguments
        return 1;
    }

    int tableSize = atoi(argv[1]);  // Parse the table size
    const char* inputFile = argv[2];  // Get the input file name

    HashTable ht;
    initHashTable(&ht, tableSize);  // Initialize the hash table
    executeBatch(&ht, inputFile);  // Execute batch operations
    destroyHashTable(&ht);  // Destroy the hash table

    return 0;
}