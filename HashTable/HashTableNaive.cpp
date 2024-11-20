#include "SinglyLinkedList.cpp"
#include <iostream>
#define DEFAULT_HASHTABLE_CAPACITY 10
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

    V search(const K &key) {
        int index = hashFunction(key);
        SinglyLinkedListNode<K, V> *targetNode = table[index].search(key);
        return targetNode->value;
    }

    void print() {
        for (int i = 0; i < capacity; i++) {
            cout << "Bucket " << i << ": ";
            table[i].print();
            cout << endl;
        }
    }
};