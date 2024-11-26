#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <omp.h>
#include "doublehashing_parallel4.cpp" 

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <capacity> <input_file>" << std::endl;
        return 1;
    }

    // Read command-line arguments
    int capacity = std::atoi(argv[1]);
    std::string input_file = argv[2];

    if (capacity <= 0) {
        std::cerr << "Error: Capacity must be a positive integer." << std::endl;
        return 1;
    }

    // Open input file
    std::ifstream infile(input_file);
    if (!infile) {
        std::cerr << "Error: Could not open file " << input_file << std::endl;
        return 1;
    }

    // Initialize the hash table
    HashTable hashTable(capacity);

    std::string line;
    int line_number = 0;

    // Read file and perform operations
    while (std::getline(infile, line)) {
        line_number++;
        std::istringstream iss(line);
        std::string operation;
        iss >> operation;

        if (operation == "I") {
            // Insert operation
            int key, value;
            iss >> key >> value;
            #pragma omp critical
            {
                hashTable.insert(key, value);
            }
        } else if (operation == "S") {
            // Search operation
            int key;
            iss >> key;
            #pragma omp critical
            {
                int result = hashTable.search(key);
                std::cout << "Search " << key << ": " << (result == -1 ? "Not Found" : std::to_string(result)) << std::endl;
            }
        } else if (operation == "R") {
            // Remove operation
            int key;
            iss >> key;
            #pragma omp critical
            {
                hashTable.remove(key);
            }
        } else if (operation == "U") {
            // Update operation
            int key, new_value;
            iss >> key >> new_value;
            #pragma omp critical
            {
                if (hashTable.search(key) != -1) {
                    hashTable.update(key, new_value);
                } else {
                    std::cout << "Update " << key << ": Key not found, inserting new value" << std::endl;
                    hashTable.insert(key, new_value);
                }
            }
        } else if (operation == "BI") {
            // Batch insert operation
            int batch_size;
            iss >> batch_size;
            std::vector<std::pair<int, int>> batch(batch_size);

            for (int i = 0; i < batch_size; ++i) {
                iss >> batch[i].first >> batch[i].second;
            }

            // Perform batch insert
            #pragma omp parallel for
            for (int i = 0; i < batch_size; ++i) {
                hashTable.insert(batch[i].first, batch[i].second);
            }
        } else if (operation == "BS") {
            // Batch search operation
            int batch_size;
            iss >> batch_size;
            std::vector<int> keys(batch_size);

            for (int i = 0; i < batch_size; ++i) {
                iss >> keys[i];
            }

            // Perform batch search
            #pragma omp parallel for
            for (int i = 0; i < batch_size; ++i) {
                int result = hashTable.search(keys[i]);
                std::cout << "Batch Search " << keys[i] << ": "
                          << (result == -1 ? "Not Found" : std::to_string(result))
                          << std::endl;
            }
        } else {
            std::cerr << "Error: Invalid operation '" << operation << "' on line " << line_number << std::endl;
        }
    }

    infile.close();
    return 0;
}
