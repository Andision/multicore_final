#include <iostream>

using namespace std;

template <typename K, typename V>
struct DoublyHashTableNode {
    K key;
    V value;
    bool isActive;

    DoublyHashTableNode() : key(K()), value(V()), isActive(false) {}
    DoublyHashTableNode(K k, V v) : key(k), value(v), isActive(true) {}
};
