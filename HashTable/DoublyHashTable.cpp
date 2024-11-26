#include "DoublyHashTableNode.cpp"
#include <iostream>
#include <vector>
#define DEFAULT_HASHTABLE_CAPACITY 10

using namespace std;

template <typename K, typename V>
class DoublyHashTable {
private:
    DoublyHashTableNode<K, V> *table;
    int capacity;
    int size;
    hash<K> hasher;

    int primaryHash(const K &key) const {
        return hasher(key) % capacity;
    }

    int secondaryHash(const K &key) const {
        return 1 + (hasher(key) % (capacity - 1));
    }

    int findIndex(const K &key) const {
        int index = primaryHash(key);
        int step = secondaryHash(key);

        for (int i = 0; i < capacity; i++) {
            int currentIndex = (index + i * step) % capacity;
            if (!table[currentIndex].isActive || table[currentIndex].key == key) {
                return currentIndex;
            }
        }
        return -1; // Hash table is full or key not found
    }

    void deepCopy(const DoublyHashTable &other) {
        table = new DoublyHashTableNode<K, V>[other.capacity];
        for (int i = 0; i < other.capacity; ++i) {
            table[i] = other.table[i];
        }
        capacity = other.capacity;
        size = other.size;
        hasher = other.hasher;
    }

public:
    // Constructors and Destructor
    DoublyHashTable() : capacity(DEFAULT_HASHTABLE_CAPACITY), size(0) {
        table = new DoublyHashTableNode<K, V>[capacity];
    }

    DoublyHashTable(int cap) : capacity(cap), size(0) {
        table = new DoublyHashTableNode<K, V>[capacity];
    }

    ~DoublyHashTable() {
        delete[] table;
    }

    // Copy Constructor
    DoublyHashTable(const DoublyHashTable &other) {
        deepCopy(other);
    }

    // Copy Assignment Operator
    DoublyHashTable &operator=(const DoublyHashTable &other) {
        if (this != &other) {
            delete[] table;
            deepCopy(other);
        }
        return *this;
    }

    // Disable Move Constructor and Move Assignment Operator
    DoublyHashTable(DoublyHashTable &&) = delete;
    DoublyHashTable &operator=(DoublyHashTable &&) = delete;

    // Methods
    void insert(const K &key, const V &value) {
        if (size == capacity) {
            cerr << "HashTable is full!\n";
            return;
        }

        int index = findIndex(key);

        if (!table[index].isActive) {
            size++;
        }

        table[index] = DoublyHashTableNode<K, V>(key, value);
    }

    bool remove(const K &key) {
        int index = findIndex(key);

        if (index >= 0 && table[index].isActive && table[index].key == key) {
            table[index].isActive = false;
            size--;
            return true;
        }
        return false;
    }

    bool update(const K &key, const V &value) {
        int index = findIndex(key);

        if (index >= 0 && table[index].isActive && table[index].key == key) {
            table[index].value = value;
            return true;
        }
        return false;
    }

    V *search(const K &key) {
        int index = findIndex(key);

        if (index >= 0 && table[index].isActive && table[index].key == key) {
            return &(table[index].value);
        }
        return nullptr;
    }

    void batchInsert(const vector<K> keys, const vector<V> values) {
        for (int i = 0; i < keys.size(); ++i) {
            insert(keys[i], values[i]);
        }
    }

    vector<V *> batchSearch(const vector<K> keys) {
        vector<V *> results;

        for (int i = 0; i < keys.size(); ++i) {
            results.push_back(search(keys[i]));
        }

        return results;
    }

    void print() {
        for (int i = 0; i < capacity; i++) {
            if (table[i].isActive) {
                cout << "Index " << i << ": " << table[i].key << " -> " << table[i].value << endl;
            } else {
                cout << "Index " << i << ": Empty\n";
            }
        }
    }
};
