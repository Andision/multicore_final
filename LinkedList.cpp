#include "LinkedList.h"

template <typename T>
void LinkedList<T>::push_back(const T& value) {
    Node* new_node = new Node(value);
    if (tail) {
        tail->next = new_node;
        new_node->prev = tail;
    } else {
        head = new_node;
    }
    tail = new_node;
    ++list_size;
}

template <typename T>
void LinkedList<T>::erase(Node* node) {
    if (!node) return;

    if (node->prev) node->prev->next = node->next;
    if (node->next) node->next->prev = node->prev;

    if (node == head) head = node->next;
    if (node == tail) tail = node->prev;

    delete node;
    --list_size;
}

template <typename T>
void LinkedList<T>::clear() {
    while (head) {
        Node* next = head->next;
        delete head;
        head = next;
    }
    tail = nullptr;
    list_size = 0;
}
