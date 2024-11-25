#include "ArrayHashTable.cpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ifstream file("generated_input.txt"); 
    if (!file.is_open()) {
        cerr << "Error: Could not open input file." << endl;
        return 1;
    }

    int operationsCount;
    file >> operationsCount;

    ArrayHashTable hashTable;
    vector<string> commands;

    string line;
    getline(file, line); 
    while (getline(file, line)) {
        commands.push_back(line); // commands
    }

    file.close();

    // Batch
    hashTable.batchExecute(commands);

    return 0;
}
