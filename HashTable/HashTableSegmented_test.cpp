#include "HashTableSegmented.h"
#include <iostream>

int main() {
    HashTableSegmented<int, char> hashTable;

    int keys[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    char values[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    int numElements = sizeof(keys) / sizeof(keys[0]);
    hashTable.insertMultiple(keys, values, numElements);

    std::cout << "Hash Table Contents:" << std::endl;
    hashTable.print();

    int searchKeys[] = {1, 5, 9};
    char* searchResults[3] = {nullptr};
    int numSearchKeys = sizeof(searchKeys) / sizeof(searchKeys[0]);
    hashTable.searchMultiple(searchKeys, searchResults, numSearchKeys);

    std::cout << "\nSearch Results:" << std::endl;
    for (int i = 0; i < numSearchKeys; ++i) {
        if (searchResults[i]) {
            std::cout << "Key " << searchKeys[i] << ": " << *searchResults[i] << std::endl;
        } else {
            std::cout << "Key " << searchKeys[i] << ": Not found" << std::endl;
        }
    }

    hashTable.remove(3);
    hashTable.remove(6);

    std::cout << "\nAfter Deletion:" << std::endl;
    hashTable.print();

    std::cout << "\nHash Table Segments After Deletion:" << std::endl;
    hashTable.printSegments();

    return 0;
}
