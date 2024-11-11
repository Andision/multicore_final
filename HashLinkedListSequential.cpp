#include "HashLinkedListSequential.h"

template <typename KeyType, typename ValueType>
HashLinkedListSequential<KeyType, ValueType>::HashLinkedListSequential() {
    // 构造函数实现
}

template <typename KeyType, typename ValueType>
HashLinkedListSequential<KeyType, ValueType>::~HashLinkedListSequential() {
    // 析构函数实现
}

template <typename KeyType, typename ValueType>
void HashLinkedListSequential<KeyType, ValueType>::insert(const KeyType& key, const ValueType& value) {
    auto it = hash_map_.find(key);
    if (it != hash_map_.end()) {
        it->second->second = value;
    } else {
        list_.emplace_back(key, value);
        hash_map_[key] = --list_.end();
    }
}

template <typename KeyType, typename ValueType>
bool HashLinkedListSequential<KeyType, ValueType>::contains(const KeyType& key) const {
    // 查找元素实现
}

template <typename KeyType, typename ValueType>
ValueType& HashLinkedListSequential<KeyType, ValueType>::at(const KeyType& key) {
    // 获取元素实现
}

template <typename KeyType, typename ValueType>
const ValueType& HashLinkedListSequential<KeyType, ValueType>::at(const KeyType& key) const {
    // 获取元素实现（const）
}

template <typename KeyType, typename ValueType>
void HashLinkedListSequential<KeyType, ValueType>::erase(const KeyType& key) {
    // 删除元素实现
}

template <typename KeyType, typename ValueType>
void HashLinkedListSequential<KeyType, ValueType>::clear() {
    // 清空所有元素实现
}

template <typename KeyType, typename ValueType>
bool HashLinkedListSequential<KeyType, ValueType>::empty() const {
    // 检查是否为空实现
}

template <typename KeyType, typename ValueType>
size_t HashLinkedListSequential<KeyType, ValueType>::size() const {
    // 获取元素数量实现
}

template <typename KeyType, typename ValueType>
typename HashLinkedListSequential<KeyType, ValueType>::KeyValuePair& HashLinkedListSequential<KeyType, ValueType>::front() {
    // 链表头元素访问
}

template <typename KeyType, typename ValueType>
const typename HashLinkedListSequential<KeyType, ValueType>::KeyValuePair& HashLinkedListSequential<KeyType, ValueType>::front() const {
    // 链表头元素访问（const）
}

template <typename KeyType, typename ValueType>
typename HashLinkedListSequential<KeyType, ValueType>::KeyValuePair& HashLinkedListSequential<KeyType, ValueType>::back() {
    // 链表尾元素访问
}

template <typename KeyType, typename ValueType>
const typename HashLinkedListSequential<KeyType, ValueType>::KeyValuePair& HashLinkedListSequential<KeyType, ValueType>::back() const {
    // 链表尾元素访问（const）
}

template <typename KeyType, typename ValueType>
typename HashLinkedListSequential<KeyType, ValueType>::ListIterator HashLinkedListSequential<KeyType, ValueType>::begin() {
    // 迭代器起始
}

template <typename KeyType, typename ValueType>
typename HashLinkedListSequential<KeyType, ValueType>::ListIterator HashLinkedListSequential<KeyType, ValueType>::end() {
    // 迭代器结束
}

template <typename KeyType, typename ValueType>
typename HashLinkedListSequential<KeyType, ValueType>::ListIterator HashLinkedListSequential<KeyType, ValueType>::find(const KeyType& key) {
    // 查找指定元素位置
}
