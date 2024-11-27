#include "SinglyLinkedListNode.cpp"
#include <iostream>
#include <omp.h>
#define DEFAULT_SEGMENTS_SIZE 10

template <typename K, typename V>
struct SearchResult {
    SinglyLinkedListNode<K, V>* previous;
    SinglyLinkedListNode<K, V>* current;
};

template <typename K, typename V>
class SinglyLinkedListSegmented {
private:
    SinglyLinkedListNode<K, V> *head;
    SinglyLinkedListNode<K, V> *tail;
    int segmentSize;
    int size = 0;
    SinglyLinkedListNode<K, V>* segments[DEFAULT_SEGMENTS_SIZE];
    int segmentCount = 0;

public:
    SinglyLinkedListSegmented() : head(nullptr), tail(nullptr), segmentSize(DEFAULT_SEGMENTS_SIZE) {
        for (int i = 0; i < DEFAULT_SEGMENTS_SIZE; ++i) {
            segments[i] = nullptr;
        }
    }
    SinglyLinkedListSegmented(int seg) : head(nullptr), tail(nullptr), segmentSize(seg) {
        for (int i = 0; i < DEFAULT_SEGMENTS_SIZE; ++i) {
            segments[i] = nullptr;
        }
    }

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
        SinglyLinkedListNode<K, V>* newNode = new SinglyLinkedListNode<K, V>(key, value);

        if (!tail) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;

        if (segmentCount < DEFAULT_SEGMENTS_SIZE) {
            if (size < segmentSize || size % segmentCount == 1) {
                segments[segmentCount++] = newNode;
            }
        } else if (size % segmentSize == 1) {
            int offset = 1;
            for (int i = 1; i < segmentCount; ++i) {
                SinglyLinkedListNode<K, V>* pivot = segments[i];
                int t = offset;
                while (t && pivot) {
                    pivot = pivot->next;
                    --t;
                }
                segments[i] = pivot;
                ++offset;
            }

            while (segments[segmentCount - 1] == nullptr) {
                --segmentCount;
            }
        }
    }

    bool remove(K key) {
        SearchResult<K, V> result = searchWithPrev(key);

        SinglyLinkedListNode<K, V>* previous = result.previous;
        SinglyLinkedListNode<K, V>* current = result.current;

        if (!current) {
            return false;
        }

         if (current == tail) {
            tail = previous;
        }


        SinglyLinkedListNode<K, V>* next = current->next;
        if (previous) {
            previous->next = next;
        } else {
            head = next;
        }

        delete current;
        size--;

        segmentCount = 0;
        SinglyLinkedListNode<K, V>* temp = head;

        while (temp && segmentCount < DEFAULT_SEGMENTS_SIZE) {
            segments[segmentCount++] = temp;
            for (int i = 0; i < segmentSize - 1 && temp; ++i) {
                temp = temp->next;
            }
        }

        return true;
    }

    bool update(K key, V newValue) {
        SinglyLinkedListNode<K, V>* nodeToUpdate = search(key);
        if (nodeToUpdate) {
            nodeToUpdate->value = newValue;
            return true;
        }
        return false;
    }

    SinglyLinkedListNode<K, V>* search(K key) {
        return searchWithPrev(key).current;
    }

    SearchResult<K, V> searchWithPrev(K key) {
        bool stop = false;
        SearchResult<K, V> res = {nullptr, nullptr};

        #pragma omp parallel for shared(stop, res) num_threads(segmentCount)
        for (int i = 0; i < segmentCount; ++i) {
            SinglyLinkedListNode<K, V>* current = segments[i];
            SinglyLinkedListNode<K, V>* previous = nullptr;
            SinglyLinkedListNode<K, V>* end = (i + 1 < segmentCount) ? segments[i + 1] : nullptr;

            while (current != end) {
                if (stop || current == nullptr) {
                    break;
                }
                if (current->key == key) {
                    stop = true;
                    break;
                }
                previous = current;
                current = current->next;
            }

            if (current != nullptr && current->key == key) {
                if (i > 0 && previous == nullptr) {
                    SinglyLinkedListNode<K, V>* pivot = segments[i - 1];
                    while (pivot->next != current) {
                        pivot = pivot->next;
                    }
                    previous = pivot;
                }

                #pragma omp critical(search_critical)
                {
                    res = {previous, current};
                }
            }
        }

        return res;
    }

    void printSegments() {
        for (int i = 0; i < segmentCount; ++i) {
            if (segments[i]) {
                cout << segments[i]->key << endl;
            }
        }
    }
};
