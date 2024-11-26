#include "ParallelArrayHashTable.cpp"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
using namespace std;

void processInput(const string &input, ParallelArrayHashTable &hashTable) {
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
                try {
                    int result = hashTable.searchValue(x);
                    cout << result << endl;
                } catch (const runtime_error &) {
                    cout << "null" << endl;
                }
            }
        } else {
            cerr << "Invalid input format for command " << command << "\n";
        }
    } else if (command == "BI") {
        int B;
        if (iss >> B && B > 0) {
            vector<int> keys(B), values(B);
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
            hashTable.batchInsert(keys, values);
            cout << "command finished" << endl;
        } else {
            cerr << "Invalid B value for command " << command << "\n";
        }
    } else if (command == "BS") {
        int B;
        if (iss >> B && B > 0) {
            vector<int> keys(B);
            for (int i = 0; i < B; ++i) {
                if (!(iss >> keys[i])) {
                    cerr << "Invalid input format for command " << command << "\n";
                    return;
                }
            }
            vector<int> results;
            hashTable.batchSearch(keys, results);
            for (const auto &result : results) {
                cout << (result != -1 ? to_string(result) : "null") << ' ';
            }
            cout << endl;
        } else {
            cerr << "Invalid B value for command " << command << "\n";
        }
    } else {
        cerr << "Invalid command: " << command << "\n";
    }
}

int main(int argc, char *argv[]) {
    int capacity = -1;
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--capacity") == 0 && i + 1 < argc) {
            capacity = atoi(argv[++i]);
        }
    }

    if (capacity <= 0) {
        cerr << "Error: You must provide a positive integer for --capacity.\n";
        return 1;
    }

    ParallelArrayHashTable hashTable(capacity);

    int N;
    cin >> N; 
    cin.ignore(); 

    for (int i = 0; i < N; ++i) {
        string line;
        getline(cin, line);
        processInput(line, hashTable);
    }

    return 0;
}
