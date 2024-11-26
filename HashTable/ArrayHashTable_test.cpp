#include "ParallelArrayHashTable.cpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_file> --threads <thread_count>" << endl;
        return 1;
    }

    string inputFile = argv[1];
    int numThreads = 4; // Default thread count
    if (argc > 3 && string(argv[2]) == "--threads") {
        numThreads = stoi(argv[3]);
    }

    ifstream file(inputFile);
    if (!file.is_open()) {
        cerr << "Error: Could not open input file." << endl;
        return 1;
    }

    int operationCount;
    file >> operationCount;

    vector<string> commands;
    string line;
    getline(file, line); // Skip the first line
    while (getline(file, line)) {
        commands.push_back(line);
    }

    file.close();

    ParallelArrayHashTable hashTable;
    hashTable.batchExecute(commands, numThreads);

    return 0;
}
