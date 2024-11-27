#include "SinglyLinkedList.cpp"
#include <iostream>
#include <vector>
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

    bool insert(const K &key, const V &value) {
        int index = hashFunction(key);

        if (search(key) != nullptr) {
            std::cerr << "Key " << key << " already exists. Insert skipped.\n";
            return false;
        }

        table[index].insertAtHead(key, value);
        size++;

        return true;
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

    void batchInsert(const vector<K> keys, const vector<V> values) {
        for (int i = 0; i < static_cast<int>(keys.size()); ++i) {
            K key = keys[i];
            V value = values[i];

            insert(key, value);
        }
    }

    vector<V *> batchSearch(const vector<K> keys) {
        vector<V *> results;
        for (int i = 0; i < static_cast<int>(keys.size()); ++i) {
            K key = keys[i];

            results.push_back(search(key));
        }
        return results;
    }

    void print() {
        for (int i = 0; i < capacity; i++) {
            cout << "Bucket " << i << ": ";
            table[i].print();
            cout << endl;
        }
    }
};