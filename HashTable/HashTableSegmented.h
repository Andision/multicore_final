#include "SinglyLinkedListSegmented.cpp"
#include "SimpleHash.h"
#include <iostream>
#include <omp.h>

#define DEFAULT_HASHTABLE_CAPACITY 1
#define DEFAULT_SEGMENT_SIZE 10

template <typename K, typename V>
class HashTableSegmented {
private:
    SinglyLinkedListSegmented<K, V> table[DEFAULT_HASHTABLE_CAPACITY];
    int capacity;
    int size;
    std::hash<K> hasher;

    int hashFunction(const K& key) const {
        return hasher(key) % capacity;
    }

public:
    HashTableSegmented(int segSize = DEFAULT_SEGMENT_SIZE)
        : capacity(DEFAULT_HASHTABLE_CAPACITY), size(0) {
        for (int i = 0; i < capacity; ++i) {
            table[i] = SinglyLinkedListSegmented<K, V>(segSize);
        }
    }

    ~HashTableSegmented() = default;

    void insert(const K& key, const V& value) {
        int index = hashFunction(key);
        #pragma omp critical
        {
            table[index].insertAtTail(key, value);
            size++;
        }
    }

    void insertMultiple(const K* keys, const V* values, int count) {
        #pragma omp parallel for
        for (int i = 0; i < count; ++i) {
            insert(keys[i], values[i]);
        }
    }

    bool remove(const K& key) {
        int index = hashFunction(key);
        bool result = false;
        #pragma omp critical
        {
            result = table[index].remove(key);
            if (result) {
                size--;
            }
        }
        return result;
    }

    bool update(const K& key, const V& newValue) {
        int index = hashFunction(key);
        bool updated = false;
        #pragma omp critical
        {
            updated = table[index].update(key, newValue);
        }
        return updated;
    }

    V* search(const K& key) {
        int index = hashFunction(key);
        auto node = table[index].search(key);
        return node ? &(node->value) : nullptr;
    }

    void searchMultiple(const K* keys, V** results, int count) {
        #pragma omp parallel for
        for (int i = 0; i < count; ++i) {
            results[i] = search(keys[i]);
        }
    }

    void print() {
        for (int i = 0; i < capacity; ++i) {
            std::cout << "Bucket " << i << ": ";
            table[i].print();
        }
    }

    void printSegments() {
        for (int i = 0; i < capacity; ++i) {
            std::cout << "Bucket " << i << " segments:" << std::endl;
            table[i].printSegments();
        }
    }
};
