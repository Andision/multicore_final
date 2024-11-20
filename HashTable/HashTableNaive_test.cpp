#include "HashTableNaive.cpp"
#include <iostream>

using namespace std;

int main() {
    HashTableNaive<int, char> hashTable;

    hashTable.insert(1, '1');
    hashTable.insert(2, '2');
    hashTable.insert(3, '3');
    hashTable.insert(4, '4');

    cout<<hashTable.search(1)<<endl;
    cout<<hashTable.search(2)<<endl;
    cout<<hashTable.search(3)<<endl;
    cout<<hashTable.search(4)<<endl;

    return 0;
}