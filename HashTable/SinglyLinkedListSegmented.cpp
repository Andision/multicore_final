#include "SinglyLinkedListNode.cpp"
#include <iostream>
#include <omp.h>
#include <vector>
#define DEFAULT_SEGMENTS_SIZE 3
using namespace std;

template <typename K, typename V>
class SinglyLinkedListSegmented {
private:
    SinglyLinkedListNode<K, V> *head;
    SinglyLinkedListNode<K, V> *tail;
    int segmentSize;
    int size = 0;
    vector<SinglyLinkedListNode<K, V> *> segments;

public:
    SinglyLinkedListSegmented() : head(nullptr), tail(nullptr), segmentSize(DEFAULT_SEGMENTS_SIZE) {}
    SinglyLinkedListSegmented(int seg) : head(nullptr), tail(nullptr), segmentSize(DEFAULT_SEGMENTS_SIZE) {}

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

    void insertAtTail(K key, V value) {
        SinglyLinkedListNode<K, V> *newNode = new SinglyLinkedListNode<K, V>(key, value);

        if (!tail) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;

        if (segments.size() < segmentSize) {
            if (size < segmentSize || size % segments.size() == 1) {
                segments.push_back(newNode);
            }
        } else if (size % segmentSize == 1) {
            int offset = 1;
            for (auto it = segments.begin() + 1; it != segments.end(); ++it) {
                SinglyLinkedListNode<K, V> *pivot = *it;
                int t = offset;
                while (t && pivot) {
                    --t;
                    pivot = pivot->next;
                }
                *it = pivot;
                ++offset;
            }

            while (*(segments.end() - 1) == nullptr) {
                segments.pop_back();
            }
        }
    }

    bool remove(K key) {

        vector<SinglyLinkedListNode<K, V> *> searchResult = searchWithPrev(key);

        SinglyLinkedListNode<K, V> *previous = searchResult[0];
        SinglyLinkedListNode<K, V> *current = searchResult[1];

        if (current == tail) {
            tail = previous;
        }

        if (!current) {
            return false;
        } else {
            SinglyLinkedListNode<K, V> *next = current->next;
            if (previous) {
                previous->next = next;
            } else {
                head = current->next;
            }
            delete current;
            size--;
            segments.clear();
            current = head;
            int count = 0;
            while (current) {
                if (count == 0) {
                    segments.push_back(current);
                    count = (size - 1) / segmentSize;
                } else {
                    --count;
                }

                current = current->next;
            }
            return true;
        }
    }

    bool update(K key, V newValue) {
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

        bool stop = false;
        vector<SinglyLinkedListNode<K, V> *> res = {nullptr, nullptr};

#pragma omp parallel for shared(stop, res) num_threads(segments.size())
        for (int i = 0; i < segments.size(); ++i) {

            SinglyLinkedListNode<K, V> *current = segments[i];
            SinglyLinkedListNode<K, V> *previous = nullptr;
            SinglyLinkedListNode<K, V> *end = nullptr;

            if (i + 1 < segments.size()) {
                end = segments[i + 1];
            }

            while (current != end) {
                if (stop) {
                    break;
                }
                if (current->key == key) {
                    stop = true;
                    break;
                }
                previous = current;
                current = current->next;
            }

            if (current->key == key) {
                if (current != head && previous == nullptr) {
                    SinglyLinkedListNode<K, V> *pivot = segments[i - 1];
                    while (pivot->next != current) {
                        pivot = pivot->next;
                    }
                    previous = pivot;
                }

#pragma omp critical
                res = {previous, current};
            }
        }

        return res;
    }

    void printSegments() {
        cout << "printSegments: ";
        for (auto it = segments.begin(); it != segments.end(); ++it) {
            cout << (*it)->key << ' ';
        }
        cout << endl;
    }
};