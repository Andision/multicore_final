#ifndef HASH_LINKED_LIST_H
#define HASH_LINKED_LIST_H

#include <list>
#include <unordered_map>
#include <utility>
#include "LinkedList.h"  // 使用自定义的 LinkedList

template <typename KeyType, typename ValueType>
class HashLinkedListSequential {
public:
    using KeyValuePair = std::pair<KeyType, ValueType>;
    // using ListIterator = typename std::list<KeyValuePair>::iterator;
    using ListIterator = typename LinkedList<KeyValuePair>::Iterator;

    // 构造函数与析构函数
    HashLinkedListSequential();
    ~HashLinkedListSequential();

    // 插入元素
    void insert(const KeyType& key, const ValueType& value);
    
    // 查找元素
    bool contains(const KeyType& key) const;

    // 获取元素的值
    ValueType& at(const KeyType& key);
    const ValueType& at(const KeyType& key) const;

    // 删除指定键的元素
    void erase(const KeyType& key);

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
    LinkedList<KeyValuePair> list_;
    std::unordered_map<KeyType, ListIterator> hash_map_;
};

#include "HashLinkedListSequential.cpp"  // 包含模板实现

#endif  // HASH_LINKED_LIST_H
