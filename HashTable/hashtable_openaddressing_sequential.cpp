#include <iostream>
#include <vector>

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

    // 插入键值对
    bool insert(int key, int value) {
        int idx = hash1(key);
        for (int i = 0; i < size; ++i) {
            int probe_idx;
            if (probingMethod == QUADRATIC) {
                probe_idx = quadraticProbing(idx, i);
            } else { // DOUBLE_HASHING
                probe_idx = doubleHashing(idx, i, key);
            }

            if (table[probe_idx].status == EMPTY || table[probe_idx].status == DELETED) {
                table[probe_idx].key = key;
                table[probe_idx].value = value;
                table[probe_idx].status = OCCUPIED;
                return true;
            }
        }
        std::cerr << "Insert failed: Hash table is full." << std::endl;
        return false;
    }

    // 删除键
    bool remove(int key) {
        int idx = hash1(key);
        for (int i = 0; i < size; ++i) {
            int probe_idx;
            if (probingMethod == QUADRATIC) {
                probe_idx = quadraticProbing(idx, i);
            } else { // DOUBLE_HASHING
                probe_idx = doubleHashing(idx, i, key);
            }

            if (table[probe_idx].status == OCCUPIED && table[probe_idx].key == key) {
                table[probe_idx].status = DELETED;
                return true;
            }
            if (table[probe_idx].status == EMPTY) {
                break; // 提前终止：键不存在
            }
        }
        std::cerr << "Remove failed: Key not found." << std::endl;
        return false;
    }

    // 更新键值
    bool update(int key, int newValue) {
        int idx = hash1(key);
        for (int i = 0; i < size; ++i) {
            int probe_idx;
            if (probingMethod == QUADRATIC) {
                probe_idx = quadraticProbing(idx, i);
            } else { // DOUBLE_HASHING
                probe_idx = doubleHashing(idx, i, key);
            }

            if (table[probe_idx].status == OCCUPIED && table[probe_idx].key == key) {
                table[probe_idx].value = newValue;
                return true;
            }
            if (table[probe_idx].status == EMPTY) {
                break; // 提前终止：键不存在
            }
        }
        std::cerr << "Update failed: Key not found." << std::endl;
        return false;
    }

    // 查找键值
    int search(int key) {
        int idx = hash1(key);
        for (int i = 0; i < size; ++i) {
            int probe_idx;
            if (probingMethod == QUADRATIC) {
                probe_idx = quadraticProbing(idx, i);
            } else { // DOUBLE_HASHING
                probe_idx = doubleHashing(idx, i, key);
            }

            if (table[probe_idx].status == OCCUPIED && table[probe_idx].key == key) {
                return table[probe_idx].value;
            }
            if (table[probe_idx].status == EMPTY) {
                break; // 提前终止：键不存在
            }
        }
        std::cerr << "Search failed: Key not found." << std::endl;
        return -1; // 返回 -1 表示未找到
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

    // 测试插入
    for (int i = 0; i < 10; ++i) {
        ht.insert(i, i * 10);
    }

    // 打印哈希表
    std::cout << "Hash table after insertion:" << std::endl;
    ht.printTable();

    // 测试查找
    std::cout << "Search key 5: " << ht.search(5) << std::endl;

    // 测试更新
    ht.update(5, 500);
    std::cout << "After updating key 5:" << std::endl;
    ht.printTable();

    // 测试删除
    ht.remove(5);
    std::cout << "After deleting key 5:" << std::endl;
    ht.printTable();

    return 0;
}