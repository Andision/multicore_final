#include <iostream>
#include <fstream> // 用于文件操作
#include <sstream> // 用于生成动态文件名
using namespace std;

int main() {
    int N = 50000;
    int S = 500000;

    // 计算总和
    int sum = S + N;

    // 动态生成文件名
    stringstream fileName;
    fileName << "I" << N << "S" << S << ".txt";

    // 打开输出文件
    ofstream outFile(fileName.str());

    // 写入总和
    if (outFile.is_open()) {
        outFile << sum << endl;

        // 第一个循环：输出 "I i i"
        for (int i = 0; i < N; i++) {
            outFile << "I " << i << " " << i << endl;
        }

        // 第二个循环：输出 "S 6666"
        for (int i = 0; i < S; i++) {
            outFile << "S " << (6666) << endl;
        }

        // 关闭文件
        outFile.close();
        cout << "Output written to file '" << fileName.str() << "' successfully!" << endl;
    } else {
        cerr << "Error: Could not open file!" << endl;
    }

    return 0;
}
