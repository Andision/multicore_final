#include <iostream>
#include <vector>
#include <omp.h>

// 哈希表的槽状态
enum SlotStatus { EMPTY, OCCUPIED, DELETED };

// 冲突解决策略
enum ProbingMethod { QUADRATIC, DOUBLE_HASHING };

// 哈希表的槽结构
struct HashSlot {
    int key;
    int value;
    SlotStatus status;

    HashSlot() : key(0), value(0), status(EMPTY) {}
};

// 哈希表类
class HashTable {
private:
    std::vector<HashSlot> table;
    int size;
    ProbingMethod probingMethod; // 当前使用的冲突解决方法

    // 主哈希函数
    int hash1(int key) {
        return key % size;
    }

    // 双哈希法的第二个哈希函数
    int hash2(int key) {
        return 1 + (key % (size - 1));
    }

    // 冲突解决函数：二次探测
    int quadraticProbing(int idx, int i) {
        return (idx + i * i) % size;
    }

    // 冲突解决函数：双哈希
    int doubleHashing(int idx, int i, int key) {
        return (idx + i * hash2(key)) % size;
    }

public:
    HashTable(int s, ProbingMethod method) : size(s), table(s), probingMethod(method) {}

    // 插入键值对 (线程安全)
    bool insert(int key, int value) {
        int idx = hash1(key);
        for (int i = 0; i < size; ++i) {
            int probe_idx;
            if (probingMethod == QUADRATIC) {
                probe_idx = quadraticProbing(idx, i);
            } else { // DOUBLE_HASHING
                probe_idx = doubleHashing(idx, i, key);
            }

            // 使用原子性保护槽访问
            #pragma omp critical
            {
                if (table[probe_idx].status == EMPTY || table[probe_idx].status == DELETED) {
                    table[probe_idx].key = key;
                    table[probe_idx].value = value;
                    table[probe_idx].status = OCCUPIED;
                    return true;
                }
            }
        }
        return false; // 插入失败
    }

    // 批量插入键值对 (支持多线程)
    void batchInsert(const std::vector<std::pair<int, int>>& data) {
        #pragma omp parallel for
        for (size_t i = 0; i < data.size(); ++i) {
            int key = data[i].first;
            int value = data[i].second;
            insert(key, value); // 调用线程安全的插入函数
        }
    }

    // 删除键 (线程安全)
    bool remove(int key) {
        int idx = hash1(key);
        for (int i = 0; i < size; ++i) {
            int probe_idx;
            if (probingMethod == QUADRATIC) {
                probe_idx = quadraticProbing(idx, i);
            } else { // DOUBLE_HASHING
                probe_idx = doubleHashing(idx, i, key);
            }

            #pragma omp critical
            {
                if (table[probe_idx].status == OCCUPIED && table[probe_idx].key == key) {
                    table[probe_idx].status = DELETED;
                    return true;
                }
                if (table[probe_idx].status == EMPTY) {
                    break; // 提前终止：键不存在
                }
            }
        }
        return false;
    }

    // 更新键值 (线程安全)
    bool update(int key, int newValue) {
        int idx = hash1(key);
        for (int i = 0; i < size; ++i) {
            int probe_idx;
            if (probingMethod == QUADRATIC) {
                probe_idx = quadraticProbing(idx, i);
            } else { // DOUBLE_HASHING
                probe_idx = doubleHashing(idx, i, key);
            }

            #pragma omp critical
            {
                if (table[probe_idx].status == OCCUPIED && table[probe_idx].key == key) {
                    table[probe_idx].value = newValue;
                    return true;
                }
                if (table[probe_idx].status == EMPTY) {
                    break; // 提前终止：键不存在
                }
            }
        }
        return false;
    }

    // 查找键值 (线程安全)
    int search(int key) {
        int idx = hash1(key);
        for (int i = 0; i < size; ++i) {
            int probe_idx;
            if (probingMethod == QUADRATIC) {
                probe_idx = quadraticProbing(idx, i);
            } else { // DOUBLE_HASHING
                probe_idx = doubleHashing(idx, i, key);
            }

            // 查找操作无需修改共享数据，无需 critical
            if (table[probe_idx].status == OCCUPIED && table[probe_idx].key == key) {
                return table[probe_idx].value;
            }
            if (table[probe_idx].status == EMPTY) {
                break; // 提前终止：键不存在
            }
        }
        return -1; // 未找到
    }

    // 打印哈希表内容
    void printTable() {
        for (int i = 0; i < size; ++i) {
            if (table[i].status == OCCUPIED) {
                std::cout << i << ": (" << table[i].key << ", " << table[i].value << ")" << std::endl;
            } else if (table[i].status == DELETED) {
                std::cout << i << ": Deleted" << std::endl;
            } else {
                std::cout << i << ": Empty" << std::endl;
            }
        }
    }
};

int main() {
    int methodChoice;
    std::cout << "Select probing method (1 = Quadratic Probing, 2 = Double Hashing): ";
    std::cin >> methodChoice;

    ProbingMethod method = (methodChoice == 1) ? QUADRATIC : DOUBLE_HASHING;
    const int TABLE_SIZE = 17;
    HashTable ht(TABLE_SIZE, method);

    // 测试多线程批量插入
    std::vector<std::pair<int, int>> data = {{1, 10}, {2, 20}, {3, 30}, {4, 40}, {5, 50}, {6, 60}};
    ht.batchInsert(data);

    // 打印哈希表
    std::cout << "Hash table after parallel batch insertion:" << std::endl;
    ht.printTable();

    // 测试更新和删除
    ht.update(3, 300);
    std::cout << "After updating key 3:" << std::endl;
    ht.printTable();

    ht.remove(3);
    std::cout << "After deleting key 3:" << std::endl;
    ht.printTable();

    return 0;
}





