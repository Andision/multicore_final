#include "ArrayHashTable.cpp"
#include <iostream>

using namespace std;

int main() {
    ArrayHashTable<int, char> hashTable;

    // Insert test cases
    hashTable.insert(1, 'A');
    hashTable.insert(2, 'B');
    hashTable.insert(3, 'C');
    hashTable.insert(4, 'D');

    // Print the hash table
    cout << "Initial hash table:" << endl;
    hashTable.print();

    // Search test cases
    try {
        cout << "Search key 2: " << hashTable.search(2) << endl;
        cout << "Search key 5 (not present): ";
        cout << hashTable.search(5) << endl; // This will throw an exception
    } catch (const runtime_error &e) {
        cout << e.what() << endl;
    }

    // Update test case
    if (hashTable.update(2, 'Z')) {
        cout << "Key 2 updated successfully." << endl;
    } else {
        cout << "Key 2 update failed!" << endl;
    }

    // Print the hash table after update
    cout << "Hash table after update:" << endl;
    hashTable.print();

    // Remove test case
    if (hashTable.remove(2)) {
        cout << "Key 2 removed successfully." << endl;
    } else {
        cout << "Key 2 removal failed!" << endl;
    }

    // Print the hash table again
    cout << "Hash table after deletion:" << endl;
    hashTable.print();

    return 0;
}
