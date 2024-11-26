#include "SinglyLinkedList.cpp"
#include <iostream>
#define DEFAULT_HASHTABLE_CAPACITY 1
using namespace std;

template <typename K, typename V>
class HashTableNaive {
private:
    SinglyLinkedList<K, V> *table;
    int capacity;
    int size;
    hash<K> hasher;

    int hashFunction(const K &key) const {
        return hasher(key) % capacity;
    }

public:
    HashTableNaive() : capacity(DEFAULT_HASHTABLE_CAPACITY), size(0) {
        table = new SinglyLinkedList<K, V>[capacity];
    }

    HashTableNaive(int cap) : capacity(cap), size(0) {
        table = new SinglyLinkedList<K, V>[capacity];
    }

    ~HashTableNaive() {
        delete[] table;
    }

    void insert(const K &key, const V &value) {
        int index = hashFunction(key);
        table[index].insertAtHead(key, value);
        size++;
    }

    bool remove(const K &key) {
        int index = hashFunction(key);
        if (table[index].remove(key)) {
            size--;
            return true;
        } else {
            return false;
        }
    }

    bool update(const K &key, const V &value) {
        int index = hashFunction(key);
        SinglyLinkedListNode<K, V> *targetNode = table[index].search(key);

        if (!targetNode) {
            return false;
        } else {
            targetNode->value = value;
            return true;
        }
    }

    V *search(const K &key) {
        int index = hashFunction(key);
        SinglyLinkedListNode<K, V> *targetNode = table[index].search(key);

        if (targetNode) {
            return &(targetNode->value);
        } else {
            return nullptr;
        }
    }

    void batchInsert(const K *keys, const V *values, int count) {
        for (int i = 0; i < count; ++i) {
            insert(keys[i], values[i]);
        }
    }

    void batchSearch(const K *keys, V **results, int count) {
        for (int i = 0; i < count; ++i) {
            results[i] = search(keys[i]);
        }
    }

    void print() {
        for (int i = 0; i < capacity; i++) {
            cout << "Bucket " << i << ": ";
            table[i].print();
            cout << endl;
        }
    }
};
