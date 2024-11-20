#include <iostream>

using namespace std;

template <typename K, typename V>
struct SinglyLinkedListNode {
    K key;
    V value;
    SinglyLinkedListNode *next;

    SinglyLinkedListNode(K k, V v) : key(k), value(v), next(nullptr) {}
};