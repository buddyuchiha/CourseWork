#pragma once
#include <iostream>
#include <vector>
#include "..\algorithm\hash_functions.h"

using namespace std;

namespace CuckooHashTable {

    const int MAX_DEPTH = 500; // Максимальная глубина переселений

    template <typename K, typename T>
    class HashTableCuckoo {
    private:
        vector<K> _keys1, _keys2;
        vector<T> _values1, _values2;
        size_t _size1, _size2;
        size_t _count1, _count2;
        size_t(*hash_function_1)(K);
        size_t(*hash_function_2)(K);

    public:
        HashTableCuckoo(size_t size, size_t(*hash1)(K), size_t(*hash2)(K));
        void insert(const K& key, const T& value);
        void insert_cuckoo(const K& key, const T& value, int table_id, int depth);
        T* search(const K& key) const;
        bool erase(const K& key);
        void print() const;
        void insert_or_assign(const K& key, const T& value);
        int count(const K& key) const;
        bool contains(const K& key) const;
        int get_count() const;
        int get_size() const;
        void rehash();
    };

    template <typename K, typename T>
    HashTableCuckoo<K, T>::HashTableCuckoo(size_t size, size_t(*hash1)(K), size_t(*hash2)(K))
        : _size1(size), _size2(size), _count1(0), _count2(0), hash_function_1(hash1), hash_function_2(hash2) {
        _keys1.resize(_size1, K());
        _values1.resize(_size1, T());
        _keys2.resize(_size2, K());
        _values2.resize(_size2, T());
    }

    template <typename K, typename T>
    void HashTableCuckoo<K, T>::insert(const K& key, const T& value) {
        insert_cuckoo(key, value, 1, 0);
    }

    template <typename K, typename T>
    void HashTableCuckoo<K, T>::insert_cuckoo(const K& key, const T& value, int table_id, int depth) {
        if (depth >= MAX_DEPTH) {
            cerr << "Exceeded maximum depth of relocations for key: " << key << ". Rehashing required.\n";
            rehash();
            insert(key, value);
            return;
        }

        size_t index;
        if (table_id == 1) {
            index = hash_function_1(key) % _size1;

            if (_keys1[index] == key) {
                _values1[index] = value;
                return;
            }

            if (_keys1[index] == K()) {
                _count1++;
                _keys1[index] = key;
                _values1[index] = value;
                return;
            }

            K evicted_key = _keys1[index];
            T evicted_value = _values1[index];
            _keys1[index] = key;
            _values1[index] = value;

            insert_cuckoo(evicted_key, evicted_value, 2, depth + 1);
        }
        else {
            index = hash_function_2(key) % _size2;

            if (_keys2[index] == key) {
                _values2[index] = value;
                return;
            }

            if (_keys2[index] == K()) {
                _count2++;
                _keys2[index] = key;
                _values2[index] = value;
                return;
            }

            K evicted_key = _keys2[index];
            T evicted_value = _values2[index];
            _keys2[index] = key;
            _values2[index] = value;

            insert_cuckoo(evicted_key, evicted_value, 1, depth + 1);
        }
    }

    template <typename K, typename T>
    T* HashTableCuckoo<K, T>::search(const K& key) const {
        size_t index = hash_function_1(key) % _size1;
        if (_keys1[index] == key) {
            return const_cast<T*>(&_values1[index]);
        }

        index = hash_function_2(key) % _size2;
        if (_keys2[index] == key) {
            return const_cast<T*>(&_values2[index]);
        }

        return nullptr;
    }

    template <typename K, typename T>
    bool HashTableCuckoo<K, T>::erase(const K& key) {
        size_t index = hash_function_1(key) % _size1;
        if (_keys1[index] == key) {
            _keys1[index] = K();
            _values1[index] = T();
            _count1--;
            return true;
        }

        index = hash_function_2(key) % _size2;
        if (_keys2[index] == key) {
            _keys2[index] = K();
            _values2[index] = T();
            _count2--;
            return true;
        }

        return false;
    }

    template <typename K, typename T>
    void HashTableCuckoo<K, T>::print() const {
        cout << "Table 1: " << endl;
        for (size_t i = 0; i < _size1; ++i) {
            if (_keys1[i] != K()) {
                cout << "Index " << i << ": {" << _keys1[i] << ", " << _values1[i] << "}" << endl;
            }
        }

        cout << "Table 2: " << endl;
        for (size_t i = 0; i < _size2; ++i) {
            if (_keys2[i] != K()) {
                cout << "Index " << i << ": {" << _keys2[i] << ", " << _values2[i] << "}" << endl;
            }
        }
    }

    template <typename K, typename T>
    void HashTableCuckoo<K, T>::insert_or_assign(const K& key, const T& value) {
        insert_cuckoo(key, value, 1, 0);
    }

    template <typename K, typename T>
    int HashTableCuckoo<K, T>::count(const K& key) const {
        int count = 0;
        size_t index = hash_function_1(key) % _size1;
        if (_keys1[index] == key) {
            count++;
        }

        index = hash_function_2(key) % _size2;
        if (_keys2[index] == key) {
            count++;
        }

        return count;
    }

    template <typename K, typename T>
    bool HashTableCuckoo<K, T>::contains(const K& key) const {
        return search(key) != nullptr;
    }

    template <typename K, typename T>
    int HashTableCuckoo<K, T>::get_count() const {
        int filled_buckets = 0;

        // Подсчёт заполненных корзин в первой таблице
        for (size_t i = 0; i < _size1; ++i) {
            if (_keys1[i] != K()) { // Если ключ не равен значению по умолчанию (пустой)
                filled_buckets++;
            }
        }

        // Подсчёт заполненных корзин во второй таблице
        for (size_t i = 0; i < _size2; ++i) {
            if (_keys2[i] != K()) { // Если ключ не равен значению по умолчанию (пустой)
                filled_buckets++;
            }
        }

        return filled_buckets;
    }


    template <typename K, typename T>
    int HashTableCuckoo<K, T>::get_size() const {
        return _size1;
    }

    template <typename K, typename T>
    void HashTableCuckoo<K, T>::rehash() {
        size_t new_size = _size1 * 2;
        vector<K> old_keys1 = std::move(_keys1);
        vector<T> old_values1 = std::move(_values1);
        vector<K> old_keys2 = std::move(_keys2);
        vector<T> old_values2 = std::move(_values2);

        _keys1.resize(new_size, K());
        _values1.resize(new_size, T());
        _keys2.resize(new_size, K());
        _values2.resize(new_size, T());

        _size1 = _size2 = new_size;
        _count1 = _count2 = 0;

        for (size_t i = 0; i < old_keys1.size(); ++i) {
            if (old_keys1[i] != K()) {
                insert_cuckoo(old_keys1[i], old_values1[i], 1, 0);
            }
        }
        for (size_t i = 0; i < old_keys2.size(); ++i) {
            if (old_keys2[i] != K()) {
                insert_cuckoo(old_keys2[i], old_values2[i], 2, 0);
            }
        }
    }
}
