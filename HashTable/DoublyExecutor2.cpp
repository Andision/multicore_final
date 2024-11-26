#include "DoublyHashTable.cpp"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>


using namespace std;

void processInput(const string &input, DoublyHashTable<int, int> &hashTable) {
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
    } else {
        cerr << "Invalid command: " << command << "\n";
    }
}

int main(int argc, char *argv[]) {
    int capacity = -1;

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--capacity") == 0 && i + 1 < argc) {
            capacity = atoi(argv[i + 1]);
            break;
        }
    }

    if (capacity <= 0) {
        cerr << "Error: You must provide a positive integer for --capacity.\n";
        return 1;
    }

    DoublyHashTable<int, int> hashTable(capacity);

    int N;
    scanf("%d\n", &N);

    for (int i = 0; i < N; ++i) {
        string line;
        getline(cin, line);
        processInput(line, hashTable);
    }

    return 0;
}
