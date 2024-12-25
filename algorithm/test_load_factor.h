#pragma once
#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <fstream>
#include "..\algorithm\chain_hash_table.h"
#include "..\algorithm\adress_hash_table.h"
#include "..\algorithm\cuckoo_hash_table.h"
#include "..\algorithm\hash_functions.h"

using namespace std;
using namespace LinearHashTable;  // Линейное пробирование
using namespace DoubleHashTable; // Двойное хэширование
using namespace CuckooHashTable; // Кукушкина хэш-таблица
using namespace ListHashTable;   // Метод цепочек (список)
using namespace TreeHashTable;   // Метод цепочек (AVL-дерево)
using namespace chrono;          // Для измерения времени

namespace LoadTests {
    vector<pair<int, int>> generate_random_data(size_t n, int key_min = 1, int key_max = 1000000, int value_min = 1, int value_max = 1000000) {
        vector<pair<int, int>> data;
        for (size_t i = 0; i < n; ++i) {
            int key = rand() % (key_max - key_min + 1) + key_min;
            int value = rand() % (value_max - value_min + 1) + value_min;
            data.emplace_back(key, value);
        }
        return data;
    }

    // Test for single hash function tables (Linear, List, Tree)
    template <typename HashFunction>
    void test_load_factor(
        ofstream& file,
        vector<size_t> sizes,
        HashFunction hash_func,
        const string& hash_name) {
        for (size_t N : sizes) {
            auto data = generate_random_data(N);

            // LinearHashTable
            HashTableLinear<int, int> linear_table(N, hash_func);
            for (const auto& [key, value] : data) {
                linear_table.insert(key, value);
            }
            double linear_load_factor = (double)linear_table.get_count() / (double)linear_table.get_size();
            file << "LinearHashTable," << hash_name << "," << N << ","
                << fixed << setprecision(3) << linear_load_factor << "\n";

            // HashTableList
            HashTableList<int, int> list_table(N);
            for (const auto& [key, value] : data) {
                list_table.insert(key, value);
            }
            double list_load_factor = (double)list_table.get_count() / (double)list_table.get_size();
            file << "HashTableList," << hash_name << "," << N << ","
                << fixed << setprecision(3) << list_load_factor << "\n";

            // HashTableTree
            HashTableTree<int, int> tree_table(N, hash_func);
            for (const auto& [key, value] : data) {
                tree_table.insert(key, value);
            }
            double tree_load_factor = (double)tree_table.get_count() / (double)tree_table.get_size();
            file << "HashTableTree," << hash_name << "," << N << ","
                << fixed << setprecision(3) << tree_load_factor << "\n";
        }
    }

    // Test for tables requiring two hash functions (Cuckoo, Double)
    template <typename HashFunction1, typename HashFunction2>
    void test_load_factor_double(
        ofstream& file,
        vector<size_t> sizes,
        HashFunction1 hash_func1,
        HashFunction2 hash_func2,
        const string& hash_name1,
        const string& hash_name2) {
        for (size_t N : sizes) {
            auto data = generate_random_data(N);

            // CuckooHashTable
            HashTableCuckoo<int, int> cuckoo_table(N, hash_func1, hash_func2);
            for (const auto& [key, value] : data) {
                cuckoo_table.insert(key, value);
            }
            double cuckoo_load_factor = (double)cuckoo_table.get_count() / (double)(cuckoo_table.get_size() * 2);
            file << "CuckooHashTable," << hash_name1 << "," << hash_name2 << "," << N << ","
                << fixed << setprecision(3) << cuckoo_load_factor << "\n";

            // DoubleHashTable
            HashTableDouble<int, int> double_table(N, hash_func1, hash_func2);
            for (const auto& [key, value] : data) {
                double_table.insert(key, value);
            }
            double double_load_factor = (double)double_table.get_count() / (double)double_table.get_size();
            file << "DoubleHashTable," << hash_name1 << "," << hash_name2 << "," << N << ","
                << fixed << setprecision(3) << double_load_factor << "\n";
        }
    }
}