#pragma once

#include <iostream>
#include <vector>
#include "..\algorithm\hash_functions.h"

using namespace std;

namespace LinearHashTable {

    template <typename K, typename T>
    class HashTableLinear {
    private:
        struct HashPair {
            K _key;
            T _value;
            bool _filled;

            HashPair() : _filled(false) {}
            HashPair(K key, T value) : _key(key), _value(value), _filled(true) {}
        };

        vector<HashPair> _data;
        size_t _size;
        size_t _count;
        size_t(*hash_function)(K);

        void rehash();

    public:
        HashTableLinear(size_t size, size_t(*hash_func)(K) = base_hash_function<K>);

        void insert(K key, T value);
        void insert_or_assign(K key, T value);
        bool contains(K key);
        size_t get_count();
        T* search(K key);
        bool erase(K key);
        void print();
        size_t count() const;
        size_t get_size() const;
    };

    template <typename K, typename T>
    HashTableLinear<K, T>::HashTableLinear(size_t size, size_t(*hash_func)(K))
        : _size(size), hash_function(hash_func), _count(0) {
        _data.resize(_size);
    }

    template <typename K, typename T>
    void HashTableLinear<K, T>::rehash() {
        size_t new_size = _size * 2;
        vector<HashPair> old_data = move(_data);
        _data.resize(new_size);
        _size = new_size;
        _count = 0;

        for (auto& pair : old_data) {
            if (pair._filled) {
                insert(pair._key, pair._value);
            }
        }
    }

    template <typename K, typename T>
    void HashTableLinear<K, T>::insert(K key, T value) {
        if (_count >= _size * 0.75) {
            rehash();
        }

        size_t index = hash_function(key) % _size;
        size_t i = 0;
        while (_data[(index + i) % _size]._filled) {
            if (_data[(index + i) % _size]._key == key) {
                _data[(index + i) % _size]._value = value;
                return;
            }
            i++;
        }

        _data[(index + i) % _size] = HashPair(key, value);
        _count++;
    }

    template <typename K, typename T>
    void HashTableLinear<K, T>::insert_or_assign(K key, T value) {
        if (_count >= _size * 0.75) {
            rehash();
        }

        size_t index = hash_function(key) % _size;
        size_t i = 0;
        while (_data[(index + i) % _size]._filled) {
            if (_data[(index + i) % _size]._key == key) {
                _data[(index + i) % _size]._value = value;
                return;
            }
            i++;
        }

        _data[(index + i) % _size] = HashPair(key, value);
        _count++;
    }

    template <typename K, typename T>
    bool HashTableLinear<K, T>::contains(K key) {
        size_t index = hash_function(key) % _size;
        size_t i = 0;

        while (_data[(index + i) % _size]._filled) {
            if (_data[(index + i) % _size]._key == key) {
                return true;
            }
            i++;
        }

        return false;
    }

    template <typename K, typename T>
    size_t HashTableLinear<K, T>::get_count() {
        size_t filled_slots = 0;

        // Проходим по всем слотам
        for (size_t i = 0; i < _size; i++) {
            if (_data[i]._filled) {
                filled_slots++;
            }
        }

        return filled_slots;
    }

    template <typename K, typename T>
    T* HashTableLinear<K, T>::search(K key) {
        size_t index = hash_function(key) % _size;
        size_t i = 0;

        while (_data[(index + i) % _size]._filled) {
            if (_data[(index + i) % _size]._key == key) {
                return &_data[(index + i) % _size]._value;
            }
            i++;
        }

        return nullptr; 
    }


    template <typename K, typename T>
    bool HashTableLinear<K, T>::erase(K key) {
        size_t index = hash_function(key) % _size;
        size_t i = 0;

        while (_data[(index + i) % _size]._filled) {
            if (_data[(index + i) % _size]._key == key) {
                _data[(index + i) % _size]._filled = false;
                _count--;
                return true;
            }
            i++;
        }

        return false;
    }

    template <typename K, typename T>
    void HashTableLinear<K, T>::print() {
        for (size_t i = 0; i < _size; i++) {
            if (_data[i]._filled) {
                cout << "Index " << i << ": {" << _data[i]._key << ", " << _data[i]._value << "}\n";
            }
        }
    }

    template <typename K, typename T>
    size_t HashTableLinear<K, T>::count() const {
        return _count;
    }

    template <typename K, typename T>
    size_t HashTableLinear<K, T>::get_size() const {
        return _size;
    }
}


namespace DoubleHashTable {

    template <typename K, typename T>
    class HashTableDouble {
    private:
        struct HashPair {
            K _key;
            T _value;
            bool _filled;

            HashPair() : _filled(false) {}
            HashPair(K key, T value) : _key(key), _value(value), _filled(true) {}
        };

        vector<HashPair> _data;
        size_t _size;
        size_t _count;
        size_t(*hash_function1)(K); 
        size_t(*hash_function2)(K); 

        void rehash();

    public:
        HashTableDouble(size_t size, size_t(*hash_func1)(K), size_t(*hash_func2)(K));

        void insert(K key, T value);
        void insert_or_assign(K key, T value);
        bool contains(T value);
        size_t get_count();
        T* search(K key);
        bool erase(K key);
        void print();
        size_t count() const;
        size_t get_size() const;
    };

    template <typename K, typename T>
    HashTableDouble<K, T>::HashTableDouble(size_t size, size_t(*hash_func1)(K), size_t(*hash_func2)(K))
        : _size(size), hash_function1(hash_func1), hash_function2(hash_func2), _count(0) {
        _data.resize(_size);
    }

    template <typename K, typename T>
    void HashTableDouble<K, T>::rehash() {
        size_t new_size = _size * 2;
        vector<HashPair> old_data = move(_data);
        _data.resize(new_size);
        _size = new_size;
        _count = 0;

        for (auto& pair : old_data) {
            if (pair._filled) {
                insert(pair._key, pair._value);
            }
        }
    }

    template <typename K, typename T>
    void HashTableDouble<K, T>::insert(K key, T value) {
        if (_count >= _size * 0.75) {
            rehash();
        }

        size_t index = hash_function1(key) % _size;
        size_t step = hash_function2(key);
        size_t i = 0;

        while (_data[(index + i * step) % _size]._filled) {
            if (_data[(index + i * step) % _size]._key == key) {
                _data[(index + i * step) % _size]._value = value;
                return;
            }
            i++;
        }

        _data[(index + i * step) % _size] = HashPair(key, value);
        _count++;
    }

    template <typename K, typename T>
    void HashTableDouble<K, T>::insert_or_assign(K key, T value) {
        if (_count >= _size * 0.75) {
            rehash();
        }

        size_t index = hash_function1(key) % _size;
        size_t step = hash_function2(key);
        size_t i = 0;

        while (_data[(index + i * step) % _size]._filled) {
            if (_data[(index + i * step) % _size]._key == key) {
                _data[(index + i * step) % _size]._value = value;
                return;
            }
            i++;
        }

        _data[(index + i * step) % _size] = HashPair(key, value);
        _count++;
    }

    template <typename K, typename T>
    bool HashTableDouble<K, T>::contains(T value) {
        for (size_t i = 0; i < _size; i++) {
            if (_data[i]._filled && _data[i]._value == value) {
                return true;
            }
        }
        return false;
    }

    template <typename K, typename T>
    size_t HashTableDouble<K, T>::get_count() {
        size_t filled_slots = 0;

        // Проходим по всем слотам
        for (size_t i = 0; i < _size; i++) {
            if (_data[i]._filled) {
                filled_slots++;
            }
        }

        return filled_slots;
    }


    template <typename K, typename T>
    T* HashTableDouble<K, T>::search(K key) {
        size_t index = hash_function1(key) % _size;
        size_t step = hash_function2(key);
        size_t i = 0;

        while (_data[(index + i * step) % _size]._filled) {
            if (_data[(index + i * step) % _size]._key == key) {
                return &_data[(index + i * step) % _size]._value;
            }
            i++;
        }

        return nullptr;
    }

    template <typename K, typename T>
    bool HashTableDouble<K, T>::erase(K key) {
        size_t index = hash_function1(key) % _size;
        size_t step = hash_function2(key);
        size_t i = 0;

        while (_data[(index + i * step) % _size]._filled) {
            if (_data[(index + i * step) % _size]._key == key) {
                _data[(index + i * step) % _size]._filled = false;
                _count--;
                return true;
            }
            i++;
        }

        return false;
    }

    template <typename K, typename T>
    void HashTableDouble<K, T>::print() {
        for (size_t i = 0; i < _size; i++) {
            if (_data[i]._filled) {
                cout << "Index " << i << ": {" << _data[i]._key << ", " << _data[i]._value << "}\n";
            }
        }
    }

    template <typename K, typename T>
    size_t HashTableDouble<K, T>::count() const {
        return _count;
    }

    template <typename K, typename T>
    size_t HashTableDouble<K, T>::get_size() const {
        return _size;
    }
}
