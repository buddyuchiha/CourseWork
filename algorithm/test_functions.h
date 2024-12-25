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

namespace NumberTests {

    vector<pair<int, int>> generate_random_data(size_t n, int key_min = 1, int key_max = 1000000, int value_min = 1, int value_max = 1000000) {
        vector<pair<int, int>> data;
        for (size_t i = 0; i < n; ++i) {
            int key = rand() % (key_max - key_min + 1) + key_min;
            int value = rand() % (value_max - value_min + 1) + value_min;
            data.emplace_back(key, value);
        }
        return data;
    }

    template <typename HashFunction>
    void test_insertion(ofstream& file, vector<size_t> sizes, HashFunction hash_func, const string& hash_name) {
        for (size_t N : sizes) {
            auto data = generate_random_data(N);

            HashTableLinear<int, int> linear_table(N, hash_func);
            auto start = high_resolution_clock::now();
            for (const auto& [key, value] : data) {
                linear_table.insert(key, value);
            }
            auto end = high_resolution_clock::now();
            file << "LinearHashTable," << hash_name << ",Insertion," << N << ","
                << fixed << setprecision(3) << duration<double, milli>(end - start).count() << "\n";

            HashTableList<int, int> list_table(N);
            start = high_resolution_clock::now();
            for (const auto& [key, value] : data) {
                list_table.insert(key, value);
            }
            end = high_resolution_clock::now();
            file << "HashTableList," << hash_name << ",Insertion," << N << ","
                << fixed << setprecision(3) << duration<double, milli>(end - start).count() << "\n";

            HashTableTree<int, int> tree_table(N, hash_func);
            start = high_resolution_clock::now();
            for (const auto& [key, value] : data) {
                tree_table.insert(key, value);
            }
            end = high_resolution_clock::now();
            file << "HashTableTree," << hash_name << ",Insertion," << N << ","
                << fixed << setprecision(3) << duration<double, milli>(end - start).count() << "\n";
        }
    }

    template <typename HashFunction>
    void test_search(ofstream& file, vector<size_t> sizes, HashFunction hash_func, const string& hash_name) {
        for (size_t N : sizes) {
            auto data = generate_random_data(N);

            HashTableLinear<int, int> linear_table(N, hash_func);
            HashTableList<int, int> list_table(N);
            HashTableTree<int, int> tree_table(N, hash_func);

            for (const auto& [key, value] : data) {
                linear_table.insert(key, value);
                list_table.insert(key, value);
                tree_table.insert(key, value);
            }

            vector<int> search_keys;
            for (size_t i = 0; i < N / 2; ++i) {
                search_keys.push_back(data[i].first); 
            }
            for (size_t i = 0; i < N / 2; ++i) {
                search_keys.push_back(rand() % 1000000);
            }

            auto start = high_resolution_clock::now();
            for (const auto& key : search_keys) {
                linear_table.search(key);
            }
            auto end = high_resolution_clock::now();
            file << "LinearHashTable," << hash_name << ",Search," << N << ","
                << fixed << setprecision(3) << duration<double, milli>(end - start).count() << "\n";

            start = high_resolution_clock::now();
            for (const auto& key : search_keys) {
                list_table.search(key);
            }
            end = high_resolution_clock::now();
            file << "HashTableList," << hash_name << ",Search," << N << ","
                << fixed << setprecision(3) << duration<double, milli>(end - start).count() << "\n";

            start = high_resolution_clock::now();
            for (const auto& key : search_keys) {
                tree_table.search(key);
            }
            end = high_resolution_clock::now();
            file << "HashTableTree," << hash_name << ",Search," << N << ","
                << fixed << setprecision(3) << duration<double, milli>(end - start).count() << "\n";
        }
    }

    template <typename HashFunction>
    void test_erase(ofstream& file, vector<size_t> sizes, HashFunction hash_func, const string& hash_name) {
        for (size_t N : sizes) {
            auto data = generate_random_data(N);

            HashTableLinear<int, int> linear_table(N, hash_func);
            for (const auto& [key, value] : data) {
                linear_table.insert(key, value);
            }
            auto start = high_resolution_clock::now();
            for (const auto& [key, value] : data) {
                linear_table.erase(key);
            }
            auto end = high_resolution_clock::now();
            file << "LinearHashTable," << hash_name << ",Erase," << N << ","
                << fixed << setprecision(3) << duration<double, milli>(end - start).count() << "\n";

            HashTableList<int, int> list_table(N);
            for (const auto& [key, value] : data) {
                list_table.insert(key, value);
            }
            start = high_resolution_clock::now();
            for (const auto& [key, value] : data) {
                list_table.erase(key);
            }
            end = high_resolution_clock::now();
            file << "HashTableList," << hash_name << ",Erase," << N << ","
                << fixed << setprecision(3) << duration<double, milli>(end - start).count() << "\n";

            HashTableTree<int, int> tree_table(N, hash_func);
            for (const auto& [key, value] : data) {
                tree_table.insert(key, value);
            }
            start = high_resolution_clock::now();
            for (const auto& [key, value] : data) {
                tree_table.erase(key);
            }
            end = high_resolution_clock::now();
            file << "HashTableTree," << hash_name << ",Erase," << N << ","
                << fixed << setprecision(3) << duration<double, milli>(end - start).count() << "\n";
        }
    }
}

namespace NumberTestsDouble {

    vector<pair<int, int>> generate_random_data(size_t n, int key_min = 1, int key_max = 1000000, int value_min = 1, int value_max = 1000000) {
        vector<pair<int, int>> data;
        for (size_t i = 0; i < n; ++i) {
            int key = rand() % (key_max - key_min + 1) + key_min;
            int value = rand() % (value_max - value_min + 1) + value_min;
            data.emplace_back(key, value);
        }
        return data;
    }

    // Тестирование вставки
    template <typename HashFunction1, typename HashFunction2>
    void test_insertion_double(ofstream& file, vector<size_t> sizes, HashFunction1 hash_func1, HashFunction2 hash_func2, const string& hash_name1, const string& hash_name2) {
        for (size_t N : sizes) {
            auto data = generate_random_data(N);

            // DoubleHashTable
            HashTableDouble<int, int> double_table(N, hash_func1, hash_func2);
            auto start = high_resolution_clock::now();
            for (const auto& [key, value] : data) {
                double_table.insert(key, value);
            }
            auto end = high_resolution_clock::now();
            file << "DoubleHashTable," << hash_name1 << "," << hash_name2 << ",Insertion," << N << ","
                << fixed << setprecision(3) << duration<double, milli>(end - start).count() << "\n";

            // CuckooHashTable
            HashTableCuckoo<int, int> cuckoo_table(N, hash_func1, hash_func2);
            start = high_resolution_clock::now();
            for (const auto& [key, value] : data) {
                cuckoo_table.insert(key, value);
            }
            end = high_resolution_clock::now();
            file << "CuckooHashTable," << hash_name1 << "," << hash_name2 << ",Insertion," << N << ","
                << fixed << setprecision(3) << duration<double, milli>(end - start).count() << "\n";
        }
    }

    // Тестирование поиска
    template <typename HashFunction1, typename HashFunction2>
    void test_search_double(ofstream& file, vector<size_t> sizes, HashFunction1 hash_func1, HashFunction2 hash_func2, const string& hash_name1, const string& hash_name2) {
        for (size_t N : sizes) {
            auto data = generate_random_data(N);

            // Создание таблиц и вставка данных
            HashTableDouble<int, int> double_table(N, hash_func1, hash_func2);
            HashTableCuckoo<int, int> cuckoo_table(N, hash_func1, hash_func2);
            for (const auto& [key, value] : data) {
                double_table.insert(key, value);
                cuckoo_table.insert(key, value);
            }

            // Генерация ключей для поиска
            vector<int> search_keys;
            for (size_t i = 0; i < N / 2; ++i) {
                search_keys.push_back(data[i].first); // Существующие ключи
            }
            for (size_t i = 0; i < N / 2; ++i) {
                search_keys.push_back(rand() % 1000000); // Несуществующие ключи
            }
                // DoubleHashTable
                auto start = high_resolution_clock::now();
                for (const auto& key : search_keys) {
                    double_table.search(key);
                }
                auto end = high_resolution_clock::now();
                file << "DoubleHashTable," << hash_name1 << "," << hash_name2 << ",Search," << N << ","
                    << fixed << setprecision(3) << duration<double, milli>(end - start).count() << "\n";

                // CuckooHashTable
                start = high_resolution_clock::now();
                for (const auto& key : search_keys) {
                    cuckoo_table.search(key);
                }
                end = high_resolution_clock::now();
                file << "CuckooHashTable," << hash_name1 << "," << hash_name2 << ",Search," << N << ","
                    << fixed << setprecision(3) << duration<double, milli>(end - start).count() << "\n";
            
        }
    }

    // Тестирование удаления
    template <typename HashFunction1, typename HashFunction2>
    void test_erase_double(ofstream& file, vector<size_t> sizes, HashFunction1 hash_func1, HashFunction2 hash_func2, const string& hash_name1, const string& hash_name2) {
        for (size_t N : sizes) {
            auto data = generate_random_data(N);

            // Создание таблиц и вставка данных
            HashTableDouble<int, int> double_table(N, hash_func1, hash_func2);
            HashTableCuckoo<int, int> cuckoo_table(N, hash_func1, hash_func2);
            for (const auto& [key, value] : data) {
                double_table.insert(key, value);
                cuckoo_table.insert(key, value);
            }

            // DoubleHashTable
            auto start = high_resolution_clock::now();
            for (const auto& [key, value] : data) {
                double_table.erase(key);
            }
            auto end = high_resolution_clock::now();
            file << "DoubleHashTable," << hash_name1 << "," << hash_name2 << ",Erase," << N << ","
                << fixed << setprecision(3) << duration<double, milli>(end - start).count() << "\n";

            // CuckooHashTable
            start = high_resolution_clock::now();
            for (const auto& [key, value] : data) {
                cuckoo_table.erase(key);
            }
            end = high_resolution_clock::now();
            file << "CuckooHashTable," << hash_name1 << "," << hash_name2 << ",Erase," << N << ","
                << fixed << setprecision(3) << duration<double, milli>(end - start).count() << "\n";
        }
    }
}

