#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

struct LetterInfo {
    char letter;
    int percent;
    double num_float;
    int num_int;
    double frac_part;
};

int main(int argc, char *argv[]) {
    int N = 0;
    int M = 0;
    int percent_i = -1, percent_r = -1, percent_u = -1, percent_s = -1;

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
            } else if (arg == "-i" && i + 1 < argc) {
                percent_i = std::atoi(argv[++i]);
            } else if (arg == "-r" && i + 1 < argc) {
                percent_r = std::atoi(argv[++i]);
            } else if (arg == "-u" && i + 1 < argc) {
                percent_u = std::atoi(argv[++i]);
            } else if (arg == "-s" && i + 1 < argc) {
                percent_s = std::atoi(argv[++i]);
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

    // Validate percentages
    int total_specified_percent = 0;
    int unspecified_letters = 0;
    if (percent_i >= 0) {
        total_specified_percent += percent_i;
    } else {
        ++unspecified_letters;
    }
    if (percent_r >= 0) {
        total_specified_percent += percent_r;
    } else {
        ++unspecified_letters;
    }
    if (percent_u >= 0) {
        total_specified_percent += percent_u;
    } else {
        ++unspecified_letters;
    }
    if (percent_s >= 0) {
        total_specified_percent += percent_s;
    } else {
        ++unspecified_letters;
    }

    if (total_specified_percent > 100) {
        std::cerr << "The sum of specified percentages cannot exceed 100." << std::endl;
        return 1;
    }

    // Generate the filename
    std::string filename = "N" + std::to_string(N) + "M" + std::to_string(M);

    if (percent_i >= 0) {
        filename += "I" + std::to_string(percent_i);
    }
    if (percent_r >= 0) {
        filename += "R" + std::to_string(percent_r);
    }
    if (percent_u >= 0) {
        filename += "U" + std::to_string(percent_u);
    }
    if (percent_s >= 0) {
        filename += "S" + std::to_string(percent_s);
    }

    filename += ".txt";

    // Distribute remaining percentage among unspecified letters
    int remaining_percent = 100 - total_specified_percent;
    if (unspecified_letters > 0) {
        int equal_percent = remaining_percent / unspecified_letters;
        // Distribute equally
        if (percent_i == -1)
            percent_i = equal_percent;
        if (percent_r == -1)
            percent_r = equal_percent;
        if (percent_u == -1)
            percent_u = equal_percent;
        if (percent_s == -1)
            percent_s = equal_percent;

        // Add any remaining percentage to the first unspecified letter
        int total_percent = percent_i + percent_r + percent_u + percent_s;
        int percent_difference = 100 - total_percent;
        if (percent_difference != 0) {
            if (percent_i == equal_percent) {
                percent_i += percent_difference;
            } else if (percent_r == equal_percent) {
                percent_r += percent_difference;
            } else if (percent_u == equal_percent) {
                percent_u += percent_difference;
            } else if (percent_s == equal_percent) {
                percent_s += percent_difference;
            }
        }
    } else if (total_specified_percent < 100) {
        // All letters specified but total less than 100
        std::cerr << "The sum of specified percentages is less than 100." << std::endl;
        return 1;
    }

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

    // Prepare the letters and their counts
    std::vector<LetterInfo> letters = {
        {'I', percent_i, 0.0, 0, 0.0},
        {'R', percent_r, 0.0, 0, 0.0},
        {'U', percent_u, 0.0, 0, 0.0},
        {'S', percent_s, 0.0, 0, 0.0}};

    // Calculate num_float, num_int, and frac_part for each letter
    int total_lines_int = 0;
    for (auto &letter : letters) {
        letter.num_float = N * letter.percent / 100.0;
        letter.num_int = static_cast<int>(letter.num_float);
        letter.frac_part = letter.num_float - letter.num_int;
        total_lines_int += letter.num_int;
    }

    // Adjust the counts to ensure total lines equal N
    int difference = N - total_lines_int;
    if (difference > 0) {
        // Sort letters by frac_part descending
        std::sort(letters.begin(), letters.end(), [](const LetterInfo &a, const LetterInfo &b) {
            return a.frac_part > b.frac_part;
        });
        for (auto &letter : letters) {
            if (difference == 0)
                break;
            letter.num_int += 1;
            difference -= 1;
        }
    } else if (difference < 0) {
        // Sort letters by frac_part ascending
        std::sort(letters.begin(), letters.end(), [](const LetterInfo &a, const LetterInfo &b) {
            return a.frac_part < b.frac_part;
        });
        for (auto &letter : letters) {
            if (difference == 0)
                break;
            if (letter.num_int > 0) {
                letter.num_int -= 1;
                difference += 1;
            }
        }
    }

    // Collect letters based on counts
    std::vector<char> letter_list;
    for (const auto &letter : letters) {
        letter_list.insert(letter_list.end(), letter.num_int, letter.letter);
    }

    // Shuffle the letters
    std::random_shuffle(letter_list.begin(), letter_list.end());

    // Generate the N lines
    for (const auto &ch : letter_list) {
        outfile << ch << ' ';
        int num1 = std::rand() % (M + 1);
        if (ch == 'I' || ch == 'U') {
            outfile << num1 << ' ' << num1 << std::endl;
        } else { // 'R' or 'S'
            outfile << num1 << std::endl;
        }
    }

    outfile.close();
    std::cout << "File " << filename << " generated successfully." << std::endl;

    return 0;
}
