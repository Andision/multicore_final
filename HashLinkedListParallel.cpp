#include "HashLinkedListParallel.h"

template <typename KeyType, typename ValueType>
HashLinkedListParallel<KeyType, ValueType>::HashLinkedListParallel() {
    // 构造函数实现
}

template <typename KeyType, typename ValueType>
HashLinkedListParallel<KeyType, ValueType>::~HashLinkedListParallel() {
    // 析构函数实现
}

template <typename KeyType, typename ValueType>
void HashLinkedListParallel<KeyType, ValueType>::insert(const KeyType& key, const ValueType& value) {
    // Check if the key already exists in the hash map
    auto it = hash_map_.find(key);
    if (it != hash_map_.end()) {
        // If the key exists, update the value in the list (update the ValueType)
        it->second->second = value;  // Access the second (value) of the pair in the list
    } else {
        // If the key does not exist, insert the new key-value pair into both the list and the hash map
        list_.push_back({key, value});
        hash_map_[key] = std::prev(list_.end());  // Store iterator to the newly inserted element
    }
}

template <typename KeyType, typename ValueType>
bool HashLinkedListParallel<KeyType, ValueType>::contains(const KeyType& key) const {
    // 查找元素实现
}

template <typename KeyType, typename ValueType>
ValueType& HashLinkedListParallel<KeyType, ValueType>::at(const KeyType& key) {
    // 获取元素实现
}

template <typename KeyType, typename ValueType>
const ValueType& HashLinkedListParallel<KeyType, ValueType>::at(const KeyType& key) const {
    // 获取元素实现（const）
}

template <typename KeyType, typename ValueType>
void HashLinkedListParallel<KeyType, ValueType>::erase(const KeyType& key) {
}



template <typename KeyType, typename ValueType>
void HashLinkedListParallel<KeyType, ValueType>::clear() {
    // 清空所有元素实现
}

template <typename KeyType, typename ValueType>
bool HashLinkedListParallel<KeyType, ValueType>::empty() const {
    // 检查是否为空实现
}

template <typename KeyType, typename ValueType>
size_t HashLinkedListParallel<KeyType, ValueType>::size() const {
    // 获取元素数量实现
}

template <typename KeyType, typename ValueType>
typename HashLinkedListParallel<KeyType, ValueType>::KeyValuePair& HashLinkedListParallel<KeyType, ValueType>::front() {
    // 链表头元素访问
}

template <typename KeyType, typename ValueType>
const typename HashLinkedListParallel<KeyType, ValueType>::KeyValuePair& HashLinkedListParallel<KeyType, ValueType>::front() const {
    // 链表头元素访问（const）
}

template <typename KeyType, typename ValueType>
typename HashLinkedListParallel<KeyType, ValueType>::KeyValuePair& HashLinkedListParallel<KeyType, ValueType>::back() {
    // 链表尾元素访问
}

template <typename KeyType, typename ValueType>
const typename HashLinkedListParallel<KeyType, ValueType>::KeyValuePair& HashLinkedListParallel<KeyType, ValueType>::back() const {
    // 链表尾元素访问（const）
}

template <typename KeyType, typename ValueType>
typename HashLinkedListParallel<KeyType, ValueType>::ListIterator HashLinkedListParallel<KeyType, ValueType>::begin() {
    // 迭代器起始
}

template <typename KeyType, typename ValueType>
typename HashLinkedListParallel<KeyType, ValueType>::ListIterator HashLinkedListParallel<KeyType, ValueType>::end() {
    // 迭代器结束
}

template <typename KeyType, typename ValueType>
typename HashLinkedListParallel<KeyType, ValueType>::ListIterator HashLinkedListParallel<KeyType, ValueType>::find(const KeyType& key) {
    // 查找指定元素位置
}
