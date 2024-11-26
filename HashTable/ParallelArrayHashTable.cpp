#include <iostream>
#include <vector>
#include <functional>
#include <mutex>
#include <stdexcept>
#include <sstream>
#include <string>
#include <thread>
using namespace std;

// Node structure for the hash table
struct DynamicArrayNode {
    int key;
    int value;
    bool isOccupied;

    DynamicArrayNode() : key(0), value(0), isOccupied(false) {}
    DynamicArrayNode(int k, int v, bool occupied) : key(k), value(v), isOccupied(occupied) {}
};

// Parallel Array Hash Table
class ParallelArrayHashTable {
private:
    vector<DynamicArrayNode> data;
    int capacity;
    int size;
    mutex tableLock;

    void resize() {
        lock_guard<mutex> guard(tableLock); // lock
        cout << "Resizing hash table from capacity " << capacity << " to " << capacity * 2 << endl;

        int newCapacity = capacity * 2;
        vector<DynamicArrayNode> newData(newCapacity);

        for (int i = 0; i < capacity; ++i) {
            if (data[i].isOccupied) {
                size_t hashIndex = std::hash<int>{}(data[i].key) % newCapacity;

                // add limit
                int probeCount = 0;
                while (newData[hashIndex].isOccupied) {
                    hashIndex = (hashIndex + 1) % newCapacity;
                    if (++probeCount > newCapacity) {
                        throw runtime_error("Resize failed: excessive collisions");
                    }
                }

                newData[hashIndex] = data[i];
            }
        }

        data = std::move(newData);
        capacity = newCapacity;

        cout << "Resize complete. New capacity: " << capacity << endl;
    }

public:
    ParallelArrayHashTable(int initialCapacity = 16) : capacity(initialCapacity), size(0) {
        data.resize(capacity);
    }

    void insert(int key, int value) {
        lock_guard<mutex> guard(tableLock);
        if (size == capacity) {
            resize();
        }
        size_t hashIndex = std::hash<int>{}(key) % capacity;
        while (data[hashIndex].isOccupied) {
            hashIndex = (hashIndex + 1) % capacity;
        }
        data[hashIndex] = DynamicArrayNode(key, value, true);
        ++size;
    }

    bool remove(int key) {
        lock_guard<mutex> guard(tableLock);
        size_t hashIndex = std::hash<int>{}(key) % capacity;
        for (int i = 0; i < capacity; ++i) {
            if (data[hashIndex].isOccupied && data[hashIndex].key == key) {
                data[hashIndex].isOccupied = false;
                --size;
                return true;
            }
            hashIndex = (hashIndex + 1) % capacity;
        }
        return false;
    }

    bool update(int key, int newValue) {
        lock_guard<mutex> guard(tableLock);
        size_t hashIndex = std::hash<int>{}(key) % capacity;
        for (int i = 0; i < capacity; ++i) {
            if (data[hashIndex].isOccupied && data[hashIndex].key == key) {
                data[hashIndex].value = newValue;
                return true;
            }
            hashIndex = (hashIndex + 1) % capacity;
        }
        return false;
    }

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

    void batchInsert(const vector<int>& keys, const vector<int>& values) {
        for (size_t i = 0; i < keys.size(); ++i) {
            insert(keys[i], values[i]);
        }
    }

    void batchSearch(const vector<int>& keys, vector<int>& results) const {
        for (const auto& key : keys) {
            try {
                results.push_back(searchValue(key));
            } catch (const runtime_error&) {
                results.push_back(-1); // Not found
            }
        }
    }

    void batchExecute(const vector<string>& commands, int threads) {
        auto threadFunc = [&](int start, int end) {
            for (int i = start; i < end; ++i) {
                istringstream iss(commands[i]);
                string op;
                iss >> op;

                if (op == "Insert") {
                    int key, value;
                    iss >> key >> value;
                    insert(key, value);
                    cout << "Inserted: " << key << " -> " << value << endl;
                } else if (op == "Remove") {
                    int key;
                    iss >> key;
                    bool result = remove(key);
                    cout << "Removed: " << key << " -> " << (result ? "true" : "false") << endl;
                } else if (op == "Update") {
                    int key, value;
                    iss >> key >> value;
                    bool result = update(key, value);
                    cout << "Updated: " << key << " -> " << value << " -> " << (result ? "true" : "false") << endl;
                } else if (op == "Search") {
                    int key;
                    iss >> key;
                    try {
                        cout << "Search: " << searchValue(key) << endl;
                    } catch (const runtime_error&) {
                        cout << "Search: Not found" << endl;
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

        for (auto& t : threadPool) {
            t.join();
        }
    }
};


