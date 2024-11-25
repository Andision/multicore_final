#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

// Define a node 
struct DynamicArrayNode {
    int key;         
    int value;       
    bool isOccupied; // Flag to indicate if the slot is occupied

    DynamicArrayNode() : key(0), value(0), isOccupied(false) {}
};

// implementation
class ArrayHashTable {
private:
    DynamicArrayNode *data; // Array to store nodes
    int capacity;           // Current capacity 
    int size;               // Current number of occupied slots

    // Resize the array to twice capacity
    void resize() {
        int newCapacity = capacity * 2;
        DynamicArrayNode *newData = new DynamicArrayNode[newCapacity];
        for (int i = 0; i < capacity; ++i) {
            newData[i] = data[i]; // Copy existing nodes
        }
        delete[] data; // Free the old array
        data = newData;
        capacity = newCapacity;
    }

public:
    // ]initialize with a fixed capacity
    ArrayHashTable(int initialCapacity = 16) : capacity(initialCapacity), size(0) {
        data = new DynamicArrayNode[capacity];
    }

    ~ArrayHashTable() {
        delete[] data; 
    }

    // Insert 
    void insert(int key, int value) {
        if (size == capacity) {
            resize(); // Resize the array if full
        }
        for (int i = 0; i < capacity; ++i) {
            if (!data[i].isOccupied) { // Find the first empty slot
                data[i].key = key;
                data[i].value = value;
                data[i].isOccupied = true;
                size++;
                return;
            }
        }
    }

    // Remove 
    void remove(int key) {
        try {
            int index = search(key);
            data[index].isOccupied = false;
            size--;
        } catch (runtime_error &e) {
            cerr << "Error in remove: " << e.what() << endl;
        }
    }

    // update
    void update(int key, int newValue) {
        try {
            int index = search(key);
            data[index].value = newValue;
        } catch (runtime_error &e) {
            cerr << "Error in update: " << e.what() << endl;
        }
    }

    // Search and return its index
    int search(int key) const {
        for (int i = 0; i < capacity; ++i) {
            if (data[i].isOccupied && data[i].key == key) {
                return i; 
            }
        }
        throw runtime_error("Key not found"); 
    }

    // Search and return its value
    int searchValue(int key) const {
        return data[search(key)].value;
    }

    // Batch
    void batchExecute(const vector<string>& commands) {
        for (const auto& command : commands) {
            istringstream iss(command);
            string op;
            iss >> op;

            if (op == "Insert") {
                int key, value;
                iss >> key >> value;
                insert(key, value);
                cout << "Inserted (" << key << ", " << value << ")" << endl;
            } else if (op == "Remove") {
                int key;
                iss >> key;
                remove(key);
                cout << "Removed key " << key << endl;
            } else if (op == "Update") {
                int key, value;
                iss >> key >> value;
                update(key, value);
                cout << "Updated key " << key << " to value " << value << endl;
            } else if (op == "Search") {
                int key;
                iss >> key;
                try {
                    int result = searchValue(key);
                    cout << "Value of key " << key << ": " << result << endl;
                } catch (const runtime_error &e) {
                    cout << "Key " << key << " not found" << endl;
                }
            }
        }
    }
};