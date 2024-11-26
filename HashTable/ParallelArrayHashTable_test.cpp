#include "ParallelArrayHashTable.cpp" 
#include <iostream>
using namespace std;

int main() {

    ParallelArrayHashTable hashTable(10);

    // insert
    hashTable.insert(1, 100);
    hashTable.insert(2, 200);
    hashTable.insert(3, 300);
    cout << "Inserted values: 1->100, 2->200, 3->300" << endl;

    // search
    cout << "Search 1: " << hashTable.searchValue(1) << endl; //  100
    cout << "Search 2: " << hashTable.searchValue(2) << endl; //  200
    cout << "Search 3: " << hashTable.searchValue(3) << endl; //  300

    // update
    hashTable.update(2, 250);
    cout << "Updated 2 to 250. Search 2: " << hashTable.searchValue(2) << endl; //  250

    // delete
    hashTable.remove(3);
    cout << "Removed key 3. Search 3: ";
    try {
        cout << hashTable.searchValue(3) << endl;
    } catch (const runtime_error &) {
        cout << "null (not found)" << endl; //  null
    }

    // batch
    vector<int> keys = {4, 5, 6};
    vector<int> values = {400, 500, 600};
    hashTable.batchInsert(keys, values);
    cout << "Batch inserted keys 4, 5, 6 with values 400, 500, 600" << endl;


    cout << "Search 4: " << hashTable.searchValue(4) << endl; //  400
    cout << "Search 5: " << hashTable.searchValue(5) << endl; //  500
    cout << "Search 6: " << hashTable.searchValue(6) << endl; //  600


    vector<int> searchKeys = {1, 2, 6, 7};
    vector<int> results;
    hashTable.batchSearch(searchKeys, results);
    cout << "Batch search results: ";
    for (const auto &res : results) {
        cout << (res != -1 ? to_string(res) : "null") << " ";
    }
    cout << endl;

    // threads
    vector<string> commands = {
        "Insert 7 700",
        "Update 4 450",
        "Search 5",
        "Remove 2"
    };
    hashTable.batchExecute(commands, 2); 
    cout << "Executed batch commands." << endl;


    cout << "Search 7: " << hashTable.searchValue(7) << endl; //  700
    cout << "Search 4: " << hashTable.searchValue(4) << endl; //  450
    cout << "Search 5: " << hashTable.searchValue(5) << endl; //  500
    cout << "Search 2: ";
    try {
        cout << hashTable.searchValue(2) << endl;
    } catch (const runtime_error &) {
        cout << "null (not found)" << endl; //  null
    }

    return 0;
}
