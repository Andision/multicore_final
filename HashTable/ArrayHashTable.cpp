#include <iostream>
#include <optional>
#define DEFAULT_HASHTABLE_CAPACITY 10

using namespace std;

template <typename K, typename V>
class ArrayHashTable {
private:
    optional<pair<K, V>> *table; // Use std::optional to store key-value pairs
    int capacity;
    int size;
    hash<K> hasher;

    // Hash function to map key to index
    int hashFunction(const K &key) const {
        return hasher(key) % capacity;
    }

public:
    // Default constructor
    ArrayHashTable() : capacity(DEFAULT_HASHTABLE_CAPACITY), size(0) {
        table = new optional<pair<K, V>>[capacity](); // Initialize array
    }

    // Constructor with custom capacity
    ArrayHashTable(int cap) : capacity(cap), size(0) {
        table = new optional<pair<K, V>>[capacity]();
    }

    // Destructor
    ~ArrayHashTable() {
        delete[] table;
    }

    // Insert a key-value pair
    void insert(const K &key, const V &value) {
        int index = hashFunction(key);
        if (!table[index].has_value() || table[index]->first == key) {
            table[index] = make_pair(key, value); // Insert or overwrite
            size++;
        } else {
            cout << "Collision at index " << index << ". Overwriting value!" << endl;
            table[index] = make_pair(key, value); // Directly overwrite on collision
        }
    }

    // Remove a key-value pair
    bool remove(const K &key) {
        int index = hashFunction(key);
        if (table[index].has_value() && table[index]->first == key) {
            table[index].reset(); // Clear the slot
            size--;
            return true;
        }
        return false;
    }

    // Search for a key
    V search(const K &key) {
        int index = hashFunction(key);
        if (table[index].has_value() && table[index]->first == key) {
            return table[index]->second; // Return the value
        } else {
            throw runtime_error("Key not found!"); // Throw exception if not found
        }
    }

    // Update the value of an existing key
    bool update(const K &key, const V &newValue) {
        int index = hashFunction(key);
        if (table[index].has_value() && table[index]->first == key) {
            table[index]->second = newValue; // Update value
            return true;
        }
        return false; // Key not found
    }

    // Print the hash table
    void print() {
        for (int i = 0; i < capacity; i++) {
            cout << "Bucket " << i << ": ";
            if (table[i].has_value()) {
                cout << table[i]->first << ":" << table[i]->second;
            } else {
                cout << "nullptr";
            }
            cout << endl;
        }
    }
};
