#include <iostream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <functional> // For std::hash
using namespace std;

// Node structure for the hash table
struct DynamicArrayNode {
    int key;
    int value;
    bool isOccupied;

    DynamicArrayNode() : key(0), value(0), isOccupied(false) {}
};

// Implementation of the hash table
class ArrayHashTable {
private:
    vector<DynamicArrayNode> data;
    int capacity;
    int size;

    // Resize the hash table to double its capacity
    void resize() {
        int newCapacity = capacity * 2;
        vector<DynamicArrayNode> newData(newCapacity);
        for (int i = 0; i < capacity; ++i) {
            if (data[i].isOccupied) {
                size_t hashIndex = std::hash<int>{}(data[i].key) % newCapacity;
                while (newData[hashIndex].isOccupied) {
                    hashIndex = (hashIndex + 1) % newCapacity;
                }
                newData[hashIndex] = data[i];
            }
        }
        data = move(newData);
        capacity = newCapacity;
    }

public:
    // Constructor
    ArrayHashTable(int initialCapacity = 16) : capacity(initialCapacity), size(0) {
        data.resize(capacity);
    }

    // Insert a key-value pair
    void insert(int key, int value) {
        if (size == capacity) {
            resize();
        }
        size_t hashIndex = std::hash<int>{}(key) % capacity;
        while (data[hashIndex].isOccupied) {
            hashIndex = (hashIndex + 1) % capacity;
        }
        data[hashIndex] = {key, value, true};
        ++size;
    }

    // Remove a key
    void remove(int key) {
        size_t hashIndex = std::hash<int>{}(key) % capacity;
        for (int i = 0; i < capacity; ++i) {
            if (data[hashIndex].isOccupied && data[hashIndex].key == key) {
                data[hashIndex].isOccupied = false;
                --size;
                return;
            }
            hashIndex = (hashIndex + 1) % capacity;
        }
    }

    // Update a key's value
    void update(int key, int newValue) {
        size_t hashIndex = std::hash<int>{}(key) % capacity;
        for (int i = 0; i < capacity; ++i) {
            if (data[hashIndex].isOccupied && data[hashIndex].key == key) {
                data[hashIndex].value = newValue;
                return;
            }
            hashIndex = (hashIndex + 1) % capacity;
        }
    }

    // Search for a key's value
    int searchValue(int key) const {
        size_t hashIndex = std::hash<int>{}(key) % capacity;
        for (int i = 0; i < capacity; ++i) {
            if (data[hashIndex].isOccupied && data[hashIndex].key == key) {
                return data[hashIndex].value;
            }
            hashIndex = (hashIndex + 1) % capacity;
        }
        throw runtime_error("Key not found");
    }

    // Batch insert keys and values
    void batchInsert(const vector<int>& keys, const vector<int>& values) {
        for (size_t i = 0; i < keys.size(); ++i) {
            insert(keys[i], values[i]);
        }
    }

    // Batch search keys and return their values
    void batchSearch(const vector<int>& keys, vector<int>& results) const {
        for (const auto& key : keys) {
            try {
                results.push_back(searchValue(key));
            } catch (const runtime_error&) {
                results.push_back(-1); // Not found
            }
        }
    }
};

void executeCommands(const vector<string>& commands, ArrayHashTable& hashTable) {
    for (const auto& command : commands) {
        istringstream iss(command);
        string op;
        iss >> op;

        if (op == "Insert") {
            int key, value;
            iss >> key >> value;
            hashTable.insert(key, value);
            cout << "Inserted: " << key << " -> " << value << endl;
        } else if (op == "Remove") {
            int key;
            iss >> key;
            hashTable.remove(key);
            cout << "Removed: " << key << endl;
        } else if (op == "Update") {
            int key, value;
            iss >> key >> value;
            hashTable.update(key, value);
            cout << "Updated: " << key << " -> " << value << endl;
        } else if (op == "Search") {
            int key;
            iss >> key;
            try {
                cout << "Search: " << hashTable.searchValue(key) << endl;
            } catch (const runtime_error&) {
                cout << "Search: Not found" << endl;
            }
        } else if (op == "BI") { // Batch insert
            int count;
            iss >> count;
            vector<int> keys(count), values(count);
            for (int i = 0; i < count; ++i) iss >> keys[i];
            for (int i = 0; i < count; ++i) iss >> values[i];
            hashTable.batchInsert(keys, values);
            cout << "Batch Inserted: " << count << " items" << endl;
        } else if (op == "BS") { // Batch search
            int count;
            iss >> count;
            vector<int> keys(count), results;
            for (int i = 0; i < count; ++i) iss >> keys[i];
            hashTable.batchSearch(keys, results);
            cout << "Batch Search Results: ";
            for (const auto& result : results) {
                cout << result << " ";
            }
            cout << endl;
        }
    }
}

int main() {
    ArrayHashTable hashTable;
    vector<string> commands = {
        "Insert 1 10",
        "Insert 2 20",
        "BI 3 3 4 5 30 40 50",
        "BS 2 1 5",
        "Search 3",
        "Update 3 35",
        "Search 3",
        "Remove 3",
        "Search 3"
    };
    executeCommands(commands, hashTable);
    return 0;
}
