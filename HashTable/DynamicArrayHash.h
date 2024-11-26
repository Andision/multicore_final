#ifndef DYNAMIC_ARRAY_HASH_H
#define DYNAMIC_ARRAY_HASH_H

#include <stdexcept>

template <typename T>
class DynamicArrayHash {
private:
    T* data;
    int capacity;
    int count;

    void resize(int newCapacity) {
        T* newData = new T[newCapacity];
        for (int i = 0; i < count; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    DynamicArrayHash(int initialCapacity = 16) : capacity(initialCapacity), count(0) {
        data = new T[capacity];
    }

    ~DynamicArrayHash() {
        delete[] data;
    }

    void resizeTo(int newSize) {
        if (newSize > capacity) {
            resize(newSize);
        }
        count = newSize;
    }

    T& operator[](int index) {
        if (index < 0 || index >= capacity) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[index];
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= capacity) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[index];
    }
};

#endif
