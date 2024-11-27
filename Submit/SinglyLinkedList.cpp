#include "SinglyLinkedListNode.cpp"
#include <iostream>
using namespace std;

template <typename K, typename V>
class SinglyLinkedList {
private:
    SinglyLinkedListNode<K, V> *head;

public:
    SinglyLinkedList() : head(nullptr) {}

    ~SinglyLinkedList() {
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
        if (!head)
            return false;

        if (head->key == key) {
            SinglyLinkedListNode<K, V> *temp = head;
            head = head->next;
            delete temp;
            return true;
        }

        SinglyLinkedListNode<K, V> *current = head;
        while (current->next && current->next->key != key) {
            current = current->next;
        }

        // ads::maybe wrong
        if (!current->next)
            return false;
        SinglyLinkedListNode<K, V> *temp = current->next;
        current->next = current->next->next;
        delete temp;
        return true;
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
        SinglyLinkedListNode<K, V> *current = head;
        while (current) {
            if (current->key == key) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }
};