#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int main() {
    int N = 50000;
    int S = 500000;

    int sum = S + N;

    stringstream fileName;
    fileName << "I" << N << "S" << S << ".txt";

    ofstream outFile(fileName.str());

    if (outFile.is_open()) {
        outFile << sum << endl;

        for (int i = 0; i < N; i++) {
            outFile << "I " << i << " " << i << endl;
        }

        for (int i = 0; i < S; i++) {
            outFile << "S " << (6666) << endl;
        }

        outFile.close();
        cout << "Output written to file '" << fileName.str() << "' successfully!" << endl;
    } else {
        cerr << "Error: Could not open file!" << endl;
    }

    return 0;
}
