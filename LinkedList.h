#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <utility>
#include <cstddef>

template <typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    size_t list_size;

public:
    class Iterator {
    public:
        Node* node;
        Iterator(Node* n) : node(n) {}
        T& operator*() { return node->data; }
        Iterator& operator++() { node = node->next; return *this; }
        Iterator& operator--() { node = node->prev; return *this; }
        bool operator!=(const Iterator& other) const { return node != other.node; }
    };

    LinkedList() : head(nullptr), tail(nullptr), list_size(0) {}
    ~LinkedList() { clear(); }

    void push_back(const T& value);
    void erase(Node* node);
    void clear();

    T& front() { return head->data; }
    T& back() { return tail->data; }
    bool empty() const { return list_size == 0; }
    size_t size() const { return list_size; }

    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }
};

#include "LinkedList.cpp"  // 包含实现
#endif  // LINKED_LIST_H
