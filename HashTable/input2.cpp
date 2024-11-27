#include <iostream>
#include <fstream> // 用于文件操作
#include <sstream> // 用于生成动态文件名
using namespace std;

int main() {
    // 固定批量大小
    int BI_B = 10;   // 批量插入的数量
    int BS_B = 10;  // 批量查询的数量

    // 动态生成文件名
    stringstream fileName;
    fileName << "BI" << BI_B << "BS" << BS_B << ".txt";

    // 打开输出文件
    ofstream outFile(fileName.str());

    // 写入总行数（固定 2 行：BI 和 BS）
    if (outFile.is_open()) {
        outFile << 2 << endl; // 总行数为 2

        // 批量插入：输出 "BI BI_B keys values"
        outFile << "BI " << BI_B;
        for (int i = 0; i < BI_B; i++) {
            outFile << " " << i << " " << i; // 插入键值对，键和值相同
        }
        outFile << endl;

        // 批量查询：输出 "BS BS_B keys"
        outFile << "BS " << BS_B;
        for (int i = 0; i < BS_B; i++) {
            outFile << " " << (i % BI_B); // 查询插入的键，循环使用插入的键
        }
        outFile << endl;

        // 关闭文件
        outFile.close();
        cout << "Input file '" << fileName.str() << "' generated successfully!" << endl;
    } else {
        cerr << "Error: Could not open file!" << endl;
    }

    return 0;
}
