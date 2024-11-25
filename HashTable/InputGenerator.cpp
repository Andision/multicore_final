#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

int main(int argc, char* argv[]) {
    int N = 0;
    int M = 0;

    // If no command-line arguments are provided, read from stdin
    if (argc == 1) {
        std::cout << "Enter N: ";
        std::cin >> N;
        std::cout << "Enter M: ";
        std::cin >> M;
    } else {
        // Process command-line arguments
        for (int i = 1; i < argc; ++i) {
            std::string arg = argv[i];
            if (arg == "-n" && i + 1 < argc) {
                N = std::atoi(argv[++i]);
            } else if (arg == "-m" && i + 1 < argc) {
                M = std::atoi(argv[++i]);
            } else {
                std::cerr << "Invalid argument: " << arg << std::endl;
                return 1;
            }
        }
    }

    // Validate N and M
    if (N <= 0 || M <= 0) {
        std::cerr << "N and M must be positive integers." << std::endl;
        return 1;
    }

    // Generate the filename
    std::string filename = "N" + std::to_string(N) + "M" + std::to_string(M) + ".txt";

    // Open the output file
    std::ofstream outfile(filename);
    if (!outfile) {
        std::cerr << "Failed to open output file." << std::endl;
        return 1;
    }

    // Seed the random number generator
    std::srand(static_cast<unsigned int>(std::time(0)));

    // Write N as the first line
    outfile << N << std::endl;

    // Array of possible letters
    char letters[] = {'I', 'R', 'U', 'S'};

    // Generate N lines according to the specified rules
    for (int i = 0; i < N; ++i) {
        char letter = letters[std::rand() % 4];
        outfile << letter << ' ';

        int num = std::rand() % (M + 1);
        if (letter == 'I' || letter == 'U') {
            outfile << num << ' ' << num << std::endl;
        } else {
            outfile << num << std::endl;
        }
    }

    outfile.close();
    std::cout << "File " << filename << " generated successfully." << std::endl;

    return 0;
}
