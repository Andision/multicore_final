#include <cstdio>
#include <cstdlib>
#include <functional>
#include <omp.h>

// Slot Status enumeration
enum SlotStatus { EMPTY, OCCUPIED, DELETED };

// Hash slot structure
struct HashSlot {
    int key;
    int value;
    SlotStatus status;
};

// Hash table structure with member functions
struct HashTable {
    HashSlot* table;
    int capacity;

    // Constructor to initialize hash table with a specific capacity
    HashTable(int cap) : capacity(cap) {
        table = (HashSlot*)malloc(sizeof(HashSlot) * capacity);
        for (int i = 0; i < capacity; ++i) {
            table[i].status = EMPTY;  // Initialize all slots as empty
        }
    }

    // Destructor to free memory
    ~HashTable() {
        free(table);
    }

    // Member functions for hash table operations
    int insert(int key, int value);
    int remove(int key);
    int update(int key, int newValue);
    int search(int key);
    int findSlot(int key);  // Internal function to find a slot for the key
};

// Primary hash function using std::hash
int hash1(int key, int capacity) {
    std::hash<int> hasher;
    return hasher(key) % capacity;
}

// Secondary hash function for double hashing
int hash2(int key, int capacity) {
    return 1 + (key % (capacity - 1));  // Ensure hash2(key) is non-zero
}

// Conflict resolution function using double hashing
int probe(int idx, int i, int key, int capacity) {
    return (idx + i * hash2(key, capacity)) % capacity;
}

// Find slot for a given key
int HashTable::findSlot(int key) {
    int idx = hash1(key, this->capacity);
    for (int i = 0; i < this->capacity; ++i) {
        int probe_idx = probe(idx, i, key, this->capacity);
        if (this->table[probe_idx].status == EMPTY) {
            return -1;  // Key not found
        }
        if (this->table[probe_idx].status == OCCUPIED && this->table[probe_idx].key == key) {
            return probe_idx;  // Key found
        }
    }
    return -1;  // Key not found
}

// Insert a key-value pair into the hash table
int HashTable::insert(int key, int value) {
    if (findSlot(key) != -1) {
        return 0;  // Key already exists
    }

    int idx = hash1(key, this->capacity);
    for (int i = 0; i < this->capacity; ++i) {
        int probe_idx = probe(idx, i, key, this->capacity);
        if (this->table[probe_idx].status == EMPTY || this->table[probe_idx].status == DELETED) {
            #pragma omp critical
            {
                this->table[probe_idx].key = key;
                this->table[probe_idx].value = value;
                this->table[probe_idx].status = OCCUPIED;
            }
            return 1;
        }
    }
    return 0;  // Table is full
}

// Remove a key from the hash table
int HashTable::remove(int key) {
    int slot = findSlot(key);
    if (slot != -1) {
        #pragma omp critical
        {
            this->table[slot].status = DELETED;
        }
        return 1;
    }
    return 0;  // Key not found
}

// Update the value associated with a key
int HashTable::update(int key, int newValue) {
    int slot = findSlot(key);
    if (slot != -1) {
        #pragma omp critical
        {
            this->table[slot].value = newValue;
        }
        return 1;
    }
    return 0;  // Key not found
}

// Search for a key in the hash table
int HashTable::search(int key) {
    int slot = findSlot(key);
    if (slot != -1) {
        return this->table[slot].value;
    }
    return -1;  // Key not found
}

// Execute batch operations from a file
void executeBatch(HashTable* ht, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        return;
    }

    int numOperations;
    fscanf(file, "%d", &numOperations);

    for (int i = 0; i < numOperations; ++i) {
        char op[3];
        fscanf(file, "%s", op);

        if (op[0] == 'B') {
            int batchSize;
            fscanf(file, "%d", &batchSize);
            for (int j = 0; j < batchSize; ++j) {
                int key, value;
                if (op[1] == 'I') {
                    fscanf(file, "%d %d", &key, &value);
                    if (ht->insert(key, value)) {
                        printf("Inserted (%d, %d)\n", key, value);
                    } else {
                        printf("Insert failed: %d\n", key);
                    }
                } else if (op[1] == 'S') {
                    fscanf(file, "%d", &key);
                    int result = ht->search(key);
                    printf("Search %d: %d\n", key, result);
                }
            }
        } else {
            int key, value;
            if (op[0] == 'I') {
                fscanf(file, "%d %d", &key, &value);
                if (ht->insert(key, value)) {
                    printf("Inserted (%d, %d)\n", key, value);
                } else {
                    printf("Insert failed: %d\n", key);
                }
            } else if (op[0] == 'R') {
                fscanf(file, "%d", &key);
                if (ht->remove(key)) {
                    printf("Removed %d\n", key);
                } else {
                    printf("Remove failed: %d\n", key);
                }
            } else if (op[0] == 'U') {
                fscanf(file, "%d %d", &key, &value);
                if (ht->update(key, value)) {
                    printf("Updated (%d, %d)\n", key, value);
                } else {
                    printf("Update failed: %d\n", key);
                }
            } else if (op[0] == 'S') {
                fscanf(file, "%d", &key);
                int result = ht->search(key);
                printf("%d\n", result);
            }
        }
    }

    fclose(file);
}
