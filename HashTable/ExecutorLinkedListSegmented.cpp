#include "HashTableSegmented.h"
#include <cctype>
#include <cstdlib> // for atoi
#include <cstring> // for strcmp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void processInput(const string &input, HashTableSegmented<int, int> &hashTable) {
    istringstream iss(input);
    string command;
    iss >> command;

    if (command == "I" || command == "U") {
        int x, y;
        if (iss >> x >> y) {
            if (command == "I") {
                hashTable.insert(x, y);
                cout << x << ' ' << y << endl;
            } else {
                bool result = hashTable.update(x, y);
                cout << (result ? "true" : "false") << endl;
            }
        } else {
            cerr << "Invalid input format for command " << command << "\n";
        }
    } else if (command == "R" || command == "S") {
        int x;
        if (iss >> x) {
            if (command == "R") {
                bool result = hashTable.remove(x);
                cout << (result ? "true" : "false") << endl;
            } else {
                int *result = hashTable.search(x);
                if (result) {
                    cout << *result << endl;
                } else {
                    cout << "null" << endl;
                }
            }
        } else {
            cerr << "Invalid input format for command " << command << "\n";
        }
    } else if (command == "BI" || command == "BU") {
        int B;
        if (iss >> B && B > 0) {
            vector<int> keys(B);
            vector<int> values(B);
            for (int i = 0; i < B; ++i) {
                if (!(iss >> keys[i])) {
                    cerr << "Invalid input format for command " << command << "\n";
                    return;
                }

                if (!(iss >> values[i])) {
                    cerr << "Invalid input format for command " << command << "\n";
                    return;
                }
            }
            if (command == "BI") {
                int *keysArray = keys.data();
                int *valuesArray = values.data();
                int count = keys.size();
                hashTable.insertMultiple(keysArray, valuesArray, count);
                cout << "command finished" << endl;
            } else {
                cout << "Not Implemented" << endl;
            }
        } else {
            cerr << "Invalid B value for command " << command << "\n";
        }
    } else if (command == "BR" || command == "BS") {
        int B;
        if (iss >> B && B > 0) {
            vector<int> numbers(B);
            for (int i = 0; i < B; ++i) {
                if (!(iss >> numbers[i])) {
                    cerr << "Invalid input format for command " << command << "\n";
                    return;
                }
            }
            if (command == "BS") {
                int *numbersArray = numbers.data();
                int count = numbers.size();
                int **results = new int *[count];

                hashTable.searchMultiple(numbersArray, results, count);
                for (int i = 0; i < count; ++i) {
                    int *pointer = results[i];
                    if (pointer) {
                        cout << *pointer << ' ';
                    } else {
                        cout << "null" << ' ';
                    }
                }
                cout << endl;
            } else {
                cout << "Not Implemented" << endl;
            }
        } else {
            cerr << "Invalid B value for command " << command << "\n";
        }
    } else {
        cerr << "Invalid command: " << command << "\n";
    }
}

int main(int argc, char *argv[]) {
    // // Check if the required argument is passed
    // int capacity = -1;
    // for (int i = 1; i < argc; ++i) {
    //     if (strcmp(argv[i], "--capacity") == 0 && i + 1 < argc) {
    //         capacity = atoi(argv[i + 1]); // Convert the next argument to an integer
    //         break;
    //     }
    // }

    // if (capacity <= 0) {
    //     cerr << "Error: You must provide a positive integer for --capacity.\n";
    //     cerr << "Usage: ExecutorLinkedListNavie --capacity <positive_integer>\n";
    //     return 1;
    // }

    // HashTableSegmented<int, int> hashTable(capacity);
    HashTableSegmented<int, int> hashTable;

    int N;
    scanf("%d\n", &N);

    for (int i = 0; i < N; ++i) {
        string line;
        getline(cin, line);
        // cout << "line:" << line << endl;
        processInput(line, hashTable);
        // hashTable.printSegments();
    }

    return 0;
}
