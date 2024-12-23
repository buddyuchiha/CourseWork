#include <stdio.h>
#include <vector>
#include "..\algorithm\hash_functions.h"

using namespace std;

namespace CuckooHashTable {

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
        void insert(K key, T value);
        void insert_cuckoo(K key, T value, int table_id, int depth); // Добавлен четвёртый аргумент depth
        T* search(K key);
        bool erase(K key);
        void print();
        void insert_or_assign(K key, T value);
        int count(K key);
        bool contains(K key);
        int get_count();
        int get_size();
        void rehash();
    };

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

        // Вставляем старые элементы в новые таблицы
        for (size_t i = 0; i < old_keys1.size(); ++i) {
            if (old_keys1[i] != K()) {
                insert_cuckoo(old_keys1[i], old_values1[i], 1, 0); // Передаем необходимые аргументы
            }
        }
        for (size_t i = 0; i < old_keys2.size(); ++i) {
            if (old_keys2[i] != K()) {
                insert_cuckoo(old_keys2[i], old_values2[i], 2, 0); // Передаем необходимые аргументы
            }
        }
    }

    template <typename K, typename T>
    HashTableCuckoo<K, T>::HashTableCuckoo(size_t size, size_t(*hash1)(K), size_t(*hash2)(K))
        : _size1(size), _size2(size), hash_function_1(hash1), hash_function_2(hash2), _count1(0), _count2(0) {
        _keys1.resize(_size1, K());
        _values1.resize(_size1, T());
        _keys2.resize(_size2, K());
        _values2.resize(_size2, T());
    }

    // Исправление: передаем все 4 аргумента в insert_cuckoo
    template <typename K, typename T>
    void HashTableCuckoo<K, T>::insert(K key, T value) {
        insert_cuckoo(key, value, 1, 0); // Передаем аргументы, как требуется
    }

    // Основной метод для вставки с учетом "кукушкиного" хеширования
    template <typename K, typename T>
    void HashTableCuckoo<K, T>::insert_cuckoo(K key, T value, int table_id, int depth) {
        if (depth > _size1 + _size2) {
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
            }
            K evicted_key = _keys1[index];
            T evicted_value = _values1[index];
            _keys1[index] = key;
            _values1[index] = value;

            if (evicted_key != K()) {
                insert_cuckoo(evicted_key, evicted_value, 2, depth + 1); // Здесь передаем все аргументы
            }
        }
        else {
            index = hash_function_2(key) % _size2;
            if (_keys2[index] == key) {
                _values2[index] = value;
                return;
            }
            if (_keys2[index] == K()) {
                _count2++;
            }
            K evicted_key = _keys2[index];
            T evicted_value = _values2[index];
            _keys2[index] = key;
            _values2[index] = value;

            if (evicted_key != K()) {
                insert_cuckoo(evicted_key, evicted_value, 1, depth + 1); // Передаем все аргументы
            }
        }
    }

    template <typename K, typename T>
    T* HashTableCuckoo<K, T>::search(K key) {
        size_t index = hash_function_1(key) % _size1;
        if (_keys1[index] == key) {
            return &_values1[index];
        }

        index = hash_function_2(key) % _size2;
        if (_keys2[index] == key) {
            return &_values2[index];
        }

        return nullptr;
    }

    template <typename K, typename T>
    bool HashTableCuckoo<K, T>::erase(K key) {
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
    void HashTableCuckoo<K, T>::print() {
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
    void HashTableCuckoo<K, T>::insert_or_assign(K key, T value) {
        insert_cuckoo(key, value, 1, 0); // Передаем все аргументы
    }

    template <typename K, typename T>
    int HashTableCuckoo<K, T>::count(K key) {
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
    bool HashTableCuckoo<K, T>::contains(K key) {
        size_t index = hash_function_1(key) % _size1;
        if (_keys1[index] == key) {
            return true;
        }

        index = hash_function_2(key) % _size2;
        if (_keys2[index] == key) {
            return true;
        }

        return false;
    }

    template <typename K, typename T>
    int HashTableCuckoo<K, T>::get_count() {
        return _count1 + _count2;
    }

    template <typename K, typename T>
    int HashTableCuckoo<K, T>::get_size() {
        return _size1;
    }
}
