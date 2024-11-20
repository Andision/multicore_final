#include "SinglyLinkedListNode.cpp"
#include <iostream>
#include <vector>
using namespace std;

template <typename K, typename V>
class SinglyLinkedListSegmented {
private:
    SinglyLinkedListNode<K, V> *head;

public:
    SinglyLinkedListSegmented() : head(nullptr) {}

    ~SinglyLinkedListSegmented() {
        SinglyLinkedListNode<K, V> *current = head;
        while (current) {
            SinglyLinkedListNode<K, V> *temp = current;
            current = current->next;
            delete temp;
        }
    }

    void print() {
        SinglyLinkedListNode<K, V> *current = head;
        while (current) {
            cout << current->key << ":" << current->value << " -> ";
            current = current->next;
        }
        cout << "nullptr" << endl;
    }

    void insertAtHead(K key, V value) {
        SinglyLinkedListNode<K, V> *newNode = new SinglyLinkedListNode<K, V>(key, value);
        newNode->next = head;
        head = newNode;
    }

    bool remove(K key) {

        vector<SinglyLinkedListNode<K, V> *> searchResult = searchWithPrev(key);

        SinglyLinkedListNode<K, V> *previous = searchResult[0];
        SinglyLinkedListNode<K, V> *current = searchResult[1];

        if (!current) {
            return false;
        } else {
            SinglyLinkedListNode<K, V> *next = current->next;
            previous->next = next;
            delete current;
            return true;
        }
    }

    bool update(K key, V oldValue, V newValue) {
        SinglyLinkedListNode<K, V> *nodeToUpdate = search(key);
        if (nodeToUpdate) {
            nodeToUpdate->value = newValue;
            return true;
        }
        return false;
    }

    SinglyLinkedListNode<K, V> *search(K key) {
        vector<SinglyLinkedListNode<K, V> *> searchResult = searchWithPrev(key);
        return searchResult[1];
    }

    vector<SinglyLinkedListNode<K, V> *> searchWithPrev(K key) {
        SinglyLinkedListNode<K, V> *current = head;
        SinglyLinkedListNode<K, V> *previous = nullptr;

        while (current) {
            if (current->key == key) {
                return {previous, current};
            }

            previous = current;
            current = current->next;
        }

        return {nullptr, nullptr};
    }
};