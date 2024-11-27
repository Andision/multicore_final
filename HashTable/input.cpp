#include <iostream>
#include <fstream> // 用于文件操作
using namespace std;

int main() {
    int N = 100000;
    int S = 1000000;

    // 计算总和
    int sum = S + N;

    // 打开输出文件
    ofstream outFile("input.txt");

    // 写入总和
    if (outFile.is_open()) {
        outFile << sum << endl;

        // 第一个循环：输出 "I i i"
        for (int i = 0; i < N; i++) {
            outFile << "I " << i << " " << i << endl;
        }

        // 第二个循环：输出 "S N-1"
        for (int i = 0; i < S; i++) {
            outFile << "S " << (66669) << endl;
        }

        // 关闭文件
        outFile.close();
        cout << "Output written to file 'input.txt' successfully!" << endl;
    } else {
        cerr << "Error: Could not open file!" << endl;
    }

    return 0;
}
