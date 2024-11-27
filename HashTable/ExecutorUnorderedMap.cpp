#include <unordered_map>
#include <cctype>
#include <cstdlib> // for atoi
#include <cstring> // for strcmp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void processInput(const string &input, unordered_map<int, int> &hashTable) {
    istringstream iss(input);
    string command;
    iss >> command;

    if (command == "I" || command == "U") {
        int x, y;
        if (iss >> x >> y) {
            if (command == "I") {
                hashTable.insert(make_pair(x, y));
                cout << x << ' ' << y << endl;
            } else {
                auto it = hashTable.find(x);
                if(it == hashTable.end()){
                    cout<<"false"<<endl;
                }
                else{
                    it -> second = y;
                    cout<<"true"<<endl;
                }
            }
        } else {
            cerr << "Invalid input format for command " << command << "\n";
        }
    } else if (command == "R" || command == "S") {
        int x;
        if (iss >> x) {
            if (command == "R") {
                hashTable.erase(x);
                cout << endl;
                // cout << (result ? "true" : "false") << endl;
            } else {
                auto it = hashTable.find(x);
                if (it != hashTable.end()) {
                    cout << it -> second << endl;
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
                for(int i=0;i<keys.size();++i){
                    int key = keys[i];
                    int value = values[i];
                    
                    hashTable[key] = value;
                }
                cout<<endl;
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
                for(auto it = numbers.begin();it != numbers.end(); ++it){
                    int key = *it;
                    auto result = hashTable.find(key);
                    if(result == hashTable.end()){
                        cout<<"null ";
                    }
                    else{
                        cout<<result->second<<' ';
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
    // Check if the required argument is passed
    int capacity = -1;
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--capacity") == 0 && i + 1 < argc) {
            capacity = atoi(argv[i + 1]); // Convert the next argument to an integer
            break;
        }
    }

    if (capacity <= 0) {
        cerr << "Error: You must provide a positive integer for --capacity.\n";
        cerr << "Usage: ExecutorLinkedListNavie --capacity <positive_integer>\n";
        return 1;
    }

    unordered_map<int, int> hashTable;

    int N;
    scanf("%d\n", &N);

    for (int i = 0; i < N; ++i) {
        string line;
        getline(cin, line);
        processInput(line, hashTable);
    }

    return 0;
}
