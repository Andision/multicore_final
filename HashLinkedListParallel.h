#ifndef HASH_LINKED_LIST_PARALLEL_H
#define HASH_LINKED_LIST_PARALLEL_H

#include <list>
#include <unordered_map>
#include <utility>
#include <vector> // 用于批量操作

template <typename KeyType, typename ValueType>
class HashLinkedListParallel {
public:
    using KeyValuePair = std::pair<KeyType, ValueType>;
    using ListIterator = typename std::list<KeyValuePair>::iterator;

    // 构造函数与析构函数
    HashLinkedListParallel();
    ~HashLinkedListParallel();

    // 插入元素
    void insert(const KeyType& key, const ValueType& value);
    void insert(const std::vector<KeyValuePair>& key_value_pairs);  // 批量插入

    // 查找元素
    bool contains(const KeyType& key) const;
    std::vector<bool> contains(const std::vector<KeyType>& keys) const;  // 批量查找

    // 获取元素的值
    ValueType& at(const KeyType& key);
    const ValueType& at(const KeyType& key) const;
    std::vector<ValueType> at(const std::vector<KeyType>& keys) const;  // 批量获取（只读）
    std::vector<ValueType> at(const std::vector<KeyType>& keys);  // 批量获取（读写）

    // 删除指定键的元素
    void erase(const KeyType& key);
    void erase(const std::vector<KeyType>& keys);  // 批量删除

    // 清空所有元素
    void clear();

    // 检查是否为空
    bool empty() const;

    // 获取元素数量
    size_t size() const;

    // 访问链表头和尾
    KeyValuePair& front();
    const KeyValuePair& front() const;
    KeyValuePair& back();
    const KeyValuePair& back() const;

    // 迭代器接口
    ListIterator begin();
    ListIterator end();
    ListIterator find(const KeyType& key);

private:
    std::list<KeyValuePair> list_;
    std::unordered_map<KeyType, ListIterator> hash_map_;
};

#include "HashLinkedListParallel.cpp"  // 包含模板实现

#endif  // HASH_LINKED_LIST_PARALLEL_H
