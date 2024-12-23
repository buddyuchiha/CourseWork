﻿#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include "..\algorithm\hash_functions.h"

using namespace std;

namespace algorithm {
    template <typename K, typename T>
    class HashTable {
    private:
        template <typename K, typename T>
        struct HashPair {
            K _key;
            T _value;
            HashPair* _next;
            bool _filled;
            HashPair(K key, T value) : _key(key), _value(value), _filled(true), _next(nullptr) {}
            HashPair() : _key(K()), _value(T()), _filled(false), _next(nullptr) {}
        };

        vector<HashPair<K, T>> _data;
        int _count = 0;
        size_t _size;
        bool rehashing_enabled = false;

        // Óêàçàòåëü íà õýø-ôóíêöèþ
        size_t(*hash_function)(K);

        void rehash() {
            size_t new_size = _size * 2;
            vector<HashPair<K, T>> old_data = std::move(_data);
            _data.resize(new_size);
            _size = new_size;
            _count = 0;

            for (auto& pair : old_data) {
                HashPair<K, T>* current = &pair;
                while (current && current->_filled) {
                    insert(current->_key, current->_value);
                    current = current->_next;
                }
            }
        }

        int random(int a, int b) {
            random_device random_device;
            mt19937 generator(random_device());
            uniform_int_distribution<> distribution(a, b);
            return distribution(generator);
        }

    public:
        HashTable(int size, size_t(*hash_func)(K) = base_hash_function<K>);
        HashTable(int size, int min_key, int max_key, int min_value, int max_value, size_t(*hash_func)(K) = base_hash_function<K>);
        ~HashTable();
        HashTable(const HashTable& other);

        void print();
        void insert(K key, T value);
        void insert_or_assign(K key, T value);
        bool contains(T value);
        T* search(K key);
        bool erase(K key);
        int count(K key);
        HashTable<K, T>& operator=(const HashTable<K, T>& other);
        int get_count();
        int get_size();

        void enable_rehashing();
        void disable_rehashing();
    };


    template<typename K, typename T>
    HashTable<K, T>::HashTable(int size, size_t(*hash_func)(K)) : _size(size), hash_function(hash_func) {
        _data.resize(_size);
    }

    template<typename K, typename T>
    HashTable<K, T>::~HashTable() {
        for (size_t i = 0; i < _size; ++i) {
            HashPair<K, T>* current = _data[i]._next;
            while (current) {
                HashPair<K, T>* to_delete = current;
                current = current->_next;
                delete to_delete;
            }
            _data[i]._next = nullptr;
        }
    }

    template<typename K, typename T>
    HashTable<K, T>::HashTable(const HashTable& other) : _size(other._size), _count(other._count) {
        _data.resize(_size);
        for (size_t i = 0; i < _size; ++i) {
            HashPair<K, T>* current = other._data[i]._next;
            while (current) {
                insert(current->_key, current->_value);
                current = current->_next;
            }
        }
    }

    template<typename K, typename T>
    HashTable<K, T>::HashTable(int size, int min_key, int max_key, int min_value, int max_value, size_t(*hash_func)(K))
        : _size(size), hash_function(hash_func) {
        _data.resize(_size);
        for (int i = 0; i < 25; ++i) {
            K key = random(min_key, max_key);
            T value = random(min_value, max_value);
            insert(key, value);
        }
    }

    template<typename K, typename T>
    void HashTable<K, T>::enable_rehashing() {
        rehashing_enabled = true;
    }

    template<typename K, typename T>
    void HashTable<K, T>::disable_rehashing() {
        rehashing_enabled = false;
    }
    template<typename K, typename T>
    void HashTable<K, T>::print()
    {
        for (int i = 0; i < _data.size(); i++) {
            cout << "Bucket: " << i << endl;
            HashPair<K, T>* temp = &_data[i];
            while (temp) {
                cout << "{" << "Key: " << temp->_key << " Value: " << temp->_value << "}" << endl;
                temp = temp->_next;
            }
            cout << endl;
        }
    }
    template<typename K, typename T>
    void HashTable<K, T>::insert(K key, T value) {
        if (rehashing_enabled && _count >= _size * 0.75) {
            rehash();
        }

        size_t index = hash_function(key) % _size;
        HashPair<K, T>* temp = &_data[index];
        if (temp->_filled) {
            while (temp->_next) {
                temp = temp->_next;
            }
            temp->_next = new HashPair<K, T>(key, value);
            temp->_next->_filled = true;
        }
        else {
            _data[index] = HashPair<K, T>(key, value);
            _data[index]._filled = true;
        }
        _count++;
    }

    template<typename K, typename T>
    void HashTable<K, T>::insert_or_assign(K key, T value) {
        size_t index = hash_function(key);
        HashPair<K, T>* temp = &_data[index];
        while (temp) {
            if (temp->_key == key) {
                temp->_value = value;
                return;
            }
            temp = temp->_next;
        }
        insert(key, value);
    }

    template<typename K, typename T>
    bool HashTable<K, T>::contains(T value) {
        for (auto& pair : _data) {
            HashPair<K, T>* temp = &pair;
            while (temp) {
                if (temp->_value == value) {
                    return true;
                }
                temp = temp->_next;
            }
        }
        return false;
    }

    template<typename K, typename T>
    T* HashTable<K, T>::search(K key) {
        size_t index = hash_function(key);
        if (!_data[index]._filled) {
            return nullptr;
        }
        else {
            HashPair<K, T>* temp = &_data[index];
            while (temp) {
                if (temp->_key == key) {
                    return &temp->_value;
                }
                temp = temp->_next;
            }
            return nullptr;
        }
    }

    template<typename K, typename T>
    bool HashTable<K, T>::erase(K key) {
        size_t index = hash_function(key);
        HashPair<K, T>* current = &_data[index];
        HashPair<K, T>* prev = nullptr;

        while (current) {
            if (current->_key == key && current->_filled) {
                if (prev) {
                    prev->_next = current->_next;
                    delete current;
                }
                else {
                    if (current->_next) {
                        HashPair<K, T>* next = current->_next;
                        _data[index] = *next;
                        delete next;
                    }
                    else {
                        _data[index]._filled = false;
                        _data[index]._next = nullptr;
                    }
                }
                _count--;
                return true;
            }
            prev = current;
            current = current->_next;
        }
        return false;
    }


    template<typename K, typename T>
    int HashTable<K, T>::count(K key) {
        size_t index = hash_function(key);
        int count = 0;
        HashPair<K, T>* current = &_data[index];
        while (current) {
            count++;
            current = current->_next;
        }
        return count;
    }

    template<typename K, typename T>
    HashTable<K, T>& HashTable<K, T>::operator=(const HashTable<K, T>& other) {
        if (this == &other) {
            return *this;
        }

        for (size_t i = 0; i < _size; ++i) {
            HashPair<K, T>* current = _data[i]._next;
            while (current) {
                HashPair<K, T>* to_delete = current;
                current = current->_next;
                delete to_delete;
            }
            _data[i]._next = nullptr;
        }

        _size = other._size;
        _count = other._count;
        _data.resize(_size);

        for (size_t i = 0; i < _size; ++i) {
            HashPair<K, T>* current = other._data[i]._next;
            while (current) {
                insert(current->_key, current->_value);
                current = current->_next;
            }
        }

        return *this;
    }

    template<typename K, typename T>
    int HashTable<K, T>::get_count() {
        int count_ = 0;
        for (const auto& pair : _data) {
            if (pair._filled) {
                count_ += count(pair._key) - 1;
            }
        }
        return count_;
    }

    template<typename K, typename T>
    int HashTable<K, T>::get_size() {
        return _data.size();
    }
}
namespace algorithm2 {
    template <typename K, typename T>
    class HashTableTree {
    private:
        template <typename K, typename T>
        struct AVLNode {
            K _key;
            T _value;
            AVLNode* left;
            AVLNode* right;
            int height;

            AVLNode(K key, T value)
                : _key(key), _value(value), left(nullptr), right(nullptr), height(1) {
            }
        };

        vector<AVLNode<K, T>*> _data;
        int _count = 0;
        size_t _size;
        bool rehashing_enabled = false;

        size_t(*hash_function)(K);

        int height(AVLNode<K, T>* node) {
            return node ? node->height : 0;
        }

        int balanceFactor(AVLNode<K, T>* node) {
            return node ? height(node->left) - height(node->right) : 0;
        }

        void updateHeight(AVLNode<K, T>* node) {
            node->height = 1 + max(height(node->left), height(node->right));
        }

        AVLNode<K, T>* rightRotate(AVLNode<K, T>* y) {
            AVLNode<K, T>* x = y->left;
            AVLNode<K, T>* T2 = x->right;

            x->right = y;
            y->left = T2;

            updateHeight(y);
            updateHeight(x);

            return x;
        }

        AVLNode<K, T>* leftRotate(AVLNode<K, T>* x) {
            AVLNode<K, T>* y = x->right;
            AVLNode<K, T>* T2 = y->left;

            y->left = x;
            x->right = T2;

            updateHeight(x);
            updateHeight(y);

            return y;
        }

        AVLNode<K, T>* balance(AVLNode<K, T>* node) {
            int balance = balanceFactor(node);

            if (balance > 1 && balanceFactor(node->left) >= 0) {
                return rightRotate(node);
            }

            if (balance < -1 && balanceFactor(node->right) <= 0) {
                return leftRotate(node);
            }

            if (balance > 1 && balanceFactor(node->left) < 0) {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }

            if (balance < -1 && balanceFactor(node->right) > 0) {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }

            return node;
        }

        AVLNode<K, T>* insert(AVLNode<K, T>* node, K key, T value) {
            if (!node) return new AVLNode<K, T>(key, value);

            if (key < node->_key) {
                node->left = insert(node->left, key, value);
            }
            else if (key > node->_key) {
                node->right = insert(node->right, key, value);
            }
            else {
                node->_value = value;
                return node;
            }

            updateHeight(node);
            return balance(node);
        }

        AVLNode<K, T>* search(AVLNode<K, T>* node, K key) {
            if (!node) return nullptr;

            if (key < node->_key) return search(node->left, key);
            else if (key > node->_key) return search(node->right, key);
            else return node;
        }

        AVLNode<K, T>* deleteNode(AVLNode<K, T>* node, K key) {
            if (!node) return node;

            if (key < node->_key) {
                node->left = deleteNode(node->left, key);
            }
            else if (key > node->_key) {
                node->right = deleteNode(node->right, key);
            }
            else {
                if (!node->left || !node->right) {
                    AVLNode<K, T>* temp = node->left ? node->left : node->right;
                    if (!temp) {
                        temp = node;
                        node = nullptr;
                    }
                    else {
                        *node = *temp;
                    }
                    delete temp;
                }
                else {
                    AVLNode<K, T>* temp = getMinValueNode(node->right);
                    node->_key = temp->_key;
                    node->_value = temp->_value;
                    node->right = deleteNode(node->right, temp->_key);
                }
            }

            if (!node) return node;

            updateHeight(node);
            return balance(node);
        }

        AVLNode<K, T>* getMinValueNode(AVLNode<K, T>* node) {
            AVLNode<K, T>* current = node;
            while (current && current->left) {
                current = current->left;
            }
            return current;
        }

        void rehash() {
            size_t new_size = _size * 2;
            vector<AVLNode<K, T>*> old_data = std::move(_data);
            _data.resize(new_size, nullptr);
            _size = new_size;
            _count = 0;

            for (auto& node : old_data) {
                if (node) {
                    insertFromTree(node);
                }
            }
        }

        void insertFromTree(AVLNode<K, T>* node) {
            if (!node) return;

            insert(node->_key, node->_value);
            insertFromTree(node->left);
            insertFromTree(node->right);
        }

        bool containsInTree(AVLNode<K, T>* node, T value) {
            if (!node) {
                return false;
            }

            if (node->_value == value) {
                return true;
            }

            return containsInTree(node->left, value) || containsInTree(node->right, value);
        }

    public:
        HashTableTree(int size, size_t(*hash_func)(K) = base_hash_function<K>);
        HashTableTree(int size, int min_key, int max_key, int min_value, int max_value, size_t(*hash_func)(K) = base_hash_function<K>);
        ~HashTableTree();
        HashTableTree(const HashTableTree& other);

        void print();
        void insert(K key, T value);
        void insert_or_assign(K key, T value);
        bool contains(T value);
        T* search(K key);
        bool erase(K key);
        int count(K key);
        HashTableTree<K, T>& operator=(const HashTableTree<K, T>& other);
        int get_count();
        int get_size();
        void deleteTree(AVLNode<K, T>* node);
        void printTree(AVLNode<K, T>* node);

        void enable_rehashing();
        void disable_rehashing();
    };

    template<typename K, typename T>
    HashTableTree<K, T>::HashTableTree(int size, size_t(*hash_func)(K)) : _size(size), hash_function(hash_func) {
        _data.resize(_size, nullptr);
    }

    template<typename K, typename T>
    HashTableTree<K, T>::~HashTableTree() {
        for (size_t i = 0; i < _size; ++i) {
            deleteTree(_data[i]);
        }
    }

    template<typename K, typename T>
    void HashTableTree<K, T>::deleteTree(AVLNode<K, T>* node) {
        if (node) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }

    template<typename K, typename T>
    HashTableTree<K, T>::HashTableTree(const HashTableTree& other) : _size(other._size), _count(other._count) {
        _data.resize(_size, nullptr);
        for (size_t i = 0; i < _size; ++i) {
            if (other._data[i]) {
                insertFromTree(other._data[i]);
            }
        }
    }

    template<typename K, typename T>
    void HashTableTree<K, T>::print() {
        for (size_t i = 0; i < _size; ++i) {
            cout << "Bucket: " << i << endl;
            printTree(_data[i]);
            cout << endl;
        }
    }

    template<typename K, typename T>
    void HashTableTree<K, T>::printTree(AVLNode<K, T>* node) {
        if (!node) return;
        cout << "{" << "Key: " << node->_key << " Value: " << node->_value << "}" << endl;
        printTree(node->left);
        printTree(node->right);
    }

    template<typename K, typename T>
    void HashTableTree<K, T>::insert(K key, T value) {
        if (rehashing_enabled && _count >= _size * 0.75) {
            rehash();
        }

        size_t index = hash_function(key) % _size;
        _data[index] = insert(_data[index], key, value);
        _count++;
    }

    template<typename K, typename T>
    void HashTableTree<K, T>::insert_or_assign(K key, T value) {
        size_t index = hash_function(key) % _size;
        AVLNode<K, T>* node = search(_data[index], key);
        if (node) {
            node->_value = value;
        }
        else {
            insert(key, value);
        }
    }

    template<typename K, typename T>
    bool HashTableTree<K, T>::contains(T value) {
        for (auto& node : _data) {
            if (node) {
                if (containsInTree(node, value)) {
                    return true;
                }
            }
        }
        return false;
    }

    template<typename K, typename T>
    T* HashTableTree<K, T>::search(K key) {
        size_t index = hash_function(key) % _size;
        AVLNode<K, T>* node = search(_data[index], key);
        return node ? &node->_value : nullptr;
    }

    template<typename K, typename T>
    bool HashTableTree<K, T>::erase(K key) {
        size_t index = hash_function(key) % _size;
        if (_data[index]) {
            _data[index] = deleteNode(_data[index], key);
            _count--;
            return true;
        }
        return false;
    }

    template<typename K, typename T>
    int HashTableTree<K, T>::count(K key) {
        size_t index = hash_function(key) % _size;
        int count = 0;
        if (_data[index]) {
            AVLNode<K, T>* node = search(_data[index], key);
            while (node) {
                count++;
                node = search(node->right, key);
            }
        }
        return count;
    }

    template<typename K, typename T>
    int HashTableTree<K, T>::get_count() {
        return _count;
    }

    template<typename K, typename T>
    int HashTableTree<K, T>::get_size() {
        return _size;
    }

    template<typename K, typename T>
    void HashTableTree<K, T>::enable_rehashing() {
        rehashing_enabled = true;
    }

    template<typename K, typename T>
    void HashTableTree<K, T>::disable_rehashing() {
        rehashing_enabled = false;
    }
}

