#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <pthread.h>
#include <cstring>
using namespace std;

// Node
struct DynamicArrayNode {
    int key;
    int value;
    bool isOccupied;

    DynamicArrayNode() : key(0), value(0), isOccupied(false) {}
};

// Parallel array hash table
class ParallelArrayHashTable {
private:
    DynamicArrayNode *data;  
    int capacity;           
    int size;                
    pthread_mutex_t tableLock; // Mutex for thread safety

    // Resize the array
    void resize() {
        pthread_mutex_lock(&tableLock); // Lock the table
        int newCapacity = capacity * 2;
        DynamicArrayNode *newData = new DynamicArrayNode[newCapacity];
        for (int i = 0; i < capacity; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
        pthread_mutex_unlock(&tableLock); // Unlock the table
    }

public:
    // Constructor
    ParallelArrayHashTable(int initialCapacity = 10) : capacity(initialCapacity), size(0) {
        data = new DynamicArrayNode[capacity];
        pthread_mutex_init(&tableLock, nullptr); // Initialize the mutex
    }

    ~ParallelArrayHashTable() {
        delete[] data;
        pthread_mutex_destroy(&tableLock); // Destroy the mutex
    }

    // Insert a key-value pair
    void insert(int key, int value) {
        pthread_mutex_lock(&tableLock); // Lock the table
        if (size == capacity) {
            resize(); // Resize if necessary
        }
        for (int i = 0; i < capacity; ++i) {
            if (!data[i].isOccupied) { // Find the first empty slot
                data[i].key = key;
                data[i].value = value;
                data[i].isOccupied = true;
                size++;
                pthread_mutex_unlock(&tableLock); // Unlock the table
                return;
            }
        }
        pthread_mutex_unlock(&tableLock); // Unlock the table
    }

    // Remove 
    void remove(int key) {
        pthread_mutex_lock(&tableLock); // Lock the table
        try {
            int index = search(key);
            data[index].isOccupied = false;
            size--;
        } catch (runtime_error &e) {
            // Key not found
        }
        pthread_mutex_unlock(&tableLock); // Unlock the table
    }

    // Update 
    void update(int key, int newValue) {
        pthread_mutex_lock(&tableLock); // Lock the table
        try {
            int index = search(key);
            data[index].value = newValue;
        } catch (runtime_error &e) {
            // Key not found
        }
        pthread_mutex_unlock(&tableLock); // Unlock the table
    }

    // Search for index
    int search(int key) const {
        for (int i = 0; i < capacity; ++i) {
            if (data[i].isOccupied && data[i].key == key) {
                return i; // Return the index
            }
        }
        throw runtime_error("Key not found");
    }

    // Search for value
    int searchValue(int key) const {
        int index = search(key);
        return data[index].value;
    }

    // Batch in parallel
    void batchExecute(const vector<string> &commands, int threads) {
        auto threadFunc = [&](int start, int end) {
            for (int i = start; i < end; ++i) {
                istringstream iss(commands[i]);
                string op;
                iss >> op;

                if (op == "Insert") { // Insert
                    int key, value;
                    iss >> key >> value;
                    insert(key, value);
                    cout << "Inserted (" << key << ", " << value << ")" << endl;
                } else if (op == "Remove") { // Remove
                    int key;
                    iss >> key;
                    remove(key);
                    cout << "Removed key " << key << endl;
                } else if (op == "Update") { // Update
                    int key, value;
                    iss >> key >> value;
                    update(key, value);
                    cout << "Updated key " << key << " to value " << value << endl;
                } else if (op == "Search") { // Search
                    int key;
                    iss >> key;
                    try {
                        int result = searchValue(key);
                        cout << result << endl; // Output only the value
                    } catch (const runtime_error &e) {
                        cout << "Key " << key << " not found" << endl;
                    }
                }
            }
        };

        int commandsPerThread = commands.size() / threads;
        vector<thread> threadPool;

        for (int i = 0; i < threads; ++i) {
            int start = i * commandsPerThread;
            int end = (i == threads - 1) ? commands.size() : start + commandsPerThread;
            threadPool.emplace_back(threadFunc, start, end);
        }

        for (auto &t : threadPool) {
            t.join();
        }
    }
};
