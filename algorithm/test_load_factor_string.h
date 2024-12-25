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
using namespace LinearHashTable;  
using namespace DoubleHashTable; 
using namespace CuckooHashTable; 
using namespace ListHashTable;  
using namespace TreeHashTable;   
using namespace chrono;          

namespace StringLoadTests {
    vector<pair<string, int>> generate_random_string_data(size_t n, size_t key_length = 10, int value_min = 1, int value_max = 1000000) {
        random_device rd;
        mt19937 generator(rd());
        uniform_int_distribution<> value_dist(value_min, value_max);

        const string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        uniform_int_distribution<> char_dist(0, characters.size() - 1);

        vector<pair<string, int>> data;
        for (size_t i = 0; i < n; ++i) {
            string key;
            for (size_t j = 0; j < key_length; ++j) {
                key += characters[char_dist(generator)];
            }
            int value = value_dist(generator);
            data.emplace_back(key, value);
        }
        return data;
    }

    template <typename HashFunction>
    void test_load_factor_string(
        ofstream& file,
        vector<size_t> sizes,
        HashFunction hash_func,
        const string& hash_name) {
        for (size_t N : sizes) {
            auto data = generate_random_string_data(N);

            HashTableLinear<string, int> linear_table(N, hash_func);
            for (const auto& [key, value] : data) {
                linear_table.insert(key, value);
            }
            double linear_load_factor = (double)linear_table.get_count() / (double)linear_table.get_size();
            file << "LinearHashTable," << hash_name << "," << N << ","
                << fixed << setprecision(3) << linear_load_factor << "\n";

            HashTableList<string, int> list_table(N, hash_func);
            for (const auto& [key, value] : data) {
                list_table.insert(key, value);
            }
            double list_load_factor = (double)list_table.get_count() / (double)list_table.get_size();
            file << "HashTableList," << hash_name << "," << N << ","
                << fixed << setprecision(3) << list_load_factor << "\n";

            HashTableTree<string, int> tree_table(N, hash_func);
            for (const auto& [key, value] : data) {
                tree_table.insert(key, value);
            }
            double tree_load_factor = (double)tree_table.get_count() / (double)tree_table.get_size();
            file << "HashTableTree," << hash_name << "," << N << ","
                << fixed << setprecision(3) << tree_load_factor << "\n";
        }
    }

    template <typename HashFunction1, typename HashFunction2>
    void test_load_factor_double_string(
        ofstream& file,
        vector<size_t> sizes,
        HashFunction1 hash_func1,
        HashFunction2 hash_func2,
        const string& hash_name1,
        const string& hash_name2) {
        for (size_t N : sizes) {
            auto data = generate_random_string_data(N);

            HashTableCuckoo<string, int> cuckoo_table(N, hash_func1, hash_func2);
            for (const auto& [key, value] : data) {
                cuckoo_table.insert(key, value);
            }
            double cuckoo_load_factor = (double)cuckoo_table.get_count() / (double)(cuckoo_table.get_size());
            file << "CuckooHashTable," << hash_name1 << "," << hash_name2 << "," << N << ","
                << fixed << setprecision(3) << cuckoo_load_factor << "\n";

            HashTableDouble<string, int> double_table(N, hash_func1, hash_func2);
            for (const auto& [key, value] : data) {
                double_table.insert(key, value);
            }
            double double_load_factor = (double)double_table.get_count() / (double)(double_table.get_size());
            file << "DoubleHashTable," << hash_name1 << "," << hash_name2 << "," << N << ","
                << fixed << setprecision(3) << double_load_factor << "\n";
        }
    }
}