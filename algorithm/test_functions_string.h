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

namespace StringTests {

    // Генерация случайных строк
    string generate_random_string(size_t length) {
        const string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        random_device rd;
        mt19937 generator(rd());
        uniform_int_distribution<> dist(0, characters.size() - 1);

        string random_string;
        for (size_t i = 0; i < length; ++i) {
            random_string += characters[dist(generator)];
        }
        return random_string;
    }

    // Генерация случайных данных (строки в качестве ключей, int в качестве значений)
    vector<pair<string, int>> generate_random_data_2(size_t n, size_t key_length = 10, int value_min = 1, int value_max = 1000000) {
        random_device rd;
        mt19937 generator(rd());
        uniform_int_distribution<> value_dist(value_min, value_max);

        vector<pair<string, int>> data;
        for (size_t i = 0; i < n; ++i) {
            string key = generate_random_string(key_length);
            int value = value_dist(generator);
            data.emplace_back(key, value);
        }
        return data;
    }

    // Тестирование вставки
    template <typename HashFunction>
    void test_insertion_string(ofstream& file, vector<size_t> sizes, HashFunction hash_func, const string& hash_name) {
        for (size_t N : sizes) {
            auto data = generate_random_data_2(N);

            // LinearHashTable
            HashTableLinear<string, int> linear_table(N, hash_func);
            auto start = high_resolution_clock::now();
            for (const auto& [key, value] : data) {
                linear_table.insert(key, value);
            }
            auto end = high_resolution_clock::now();
            file << "LinearHashTable," << hash_name << ",Insertion," << N << ","
                << fixed << setprecision(3) << duration<double, milli>(end - start).count() << "\n";

            // HashTableList
            HashTableList<string, int> list_table(N);
            start = high_resolution_clock::now();
            for (const auto& [key, value] : data) {
                list_table.insert(key, value);
            }
            end = high_resolution_clock::now();
            file << "HashTableList," << hash_name << ",Insertion," << N << ","
                << fixed << setprecision(3) << duration<double, milli>(end - start).count() << "\n";

            // HashTableTree
            HashTableTree<string, int> tree_table(N, hash_func);
            start = high_resolution_clock::now();
            for (const auto& [key, value] : data) {
                tree_table.insert(key, value);
            }
            end = high_resolution_clock::now();
            file << "HashTableTree," << hash_name << ",Insertion," << N << ","
                << fixed << setprecision(3) << duration<double, milli>(end - start).count() << "\n";
        }
    }

    // Тестирование поиска
    template <typename HashFunction>
    void test_search_string(ofstream& file, vector<size_t> sizes, HashFunction hash_func, const string& hash_name) {
        for (size_t N : sizes) {
            auto data = generate_random_data_2(N);

            // Создание таблиц и вставка данных
            HashTableLinear<string, int> linear_table(N, hash_func);
            HashTableList<string, int> list_table(N);
            HashTableTree<string, int> tree_table(N, hash_func);

            for (const auto& [key, value] : data) {
                linear_table.insert(key, value);
                list_table.insert(key, value);
                tree_table.insert(key, value);
            }

            // Генерация ключей для поиска
            vector<string> search_keys;
            for (size_t i = 0; i < N / 2; ++i) {
                search_keys.push_back(data[i].first); // Существующие ключи
            }
            for (size_t i = 0; i < N / 2; ++i) {
                search_keys.push_back(generate_random_string(10)); // Несуществующие ключи
            }

            // LinearHashTable
            auto start = high_resolution_clock::now();
            for (const auto& key : search_keys) {
                linear_table.search(key);
            }
            auto end = high_resolution_clock::now();
            file << "LinearHashTable," << hash_name << ",Search," << N << ","
                << fixed << setprecision(3) << duration<double, milli>(end - start).count() << "\n";

            // HashTableList
            start = high_resolution_clock::now();
            for (const auto& key : search_keys) {
                list_table.search(key);
            }
            end = high_resolution_clock::now();
            file << "HashTableList," << hash_name << ",Search," << N << ","
                << fixed << setprecision(3) << duration<double, milli>(end - start).count() << "\n";

            // HashTableTree
            start = high_resolution_clock::now();
            for (const auto& key : search_keys) {
                tree_table.search(key);
            }
            end = high_resolution_clock::now();
            file << "HashTableTree," << hash_name << ",Search," << N << ","
                << fixed << setprecision(3) << duration<double, milli>(end - start).count() << "\n";
        }
    }

    // Тестирование удаления
    template <typename HashFunction>
    void test_erase_string(ofstream& file, vector<size_t> sizes, HashFunction hash_func, const string& hash_name) {
        for (size_t N : sizes) {
            auto data = generate_random_data_2(N);

            // LinearHashTable
            HashTableLinear<string, int> linear_table(N, hash_func);
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

            // HashTableList
            HashTableList<string, int> list_table(N);
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

            // HashTableTree
            HashTableTree<string, int> tree_table(N, hash_func);
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
namespace StringTestsDouble {

    // Генерация случайных строк
    string generate_random_string(size_t length) {
        const string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        random_device rd;
        mt19937 generator(rd());
        uniform_int_distribution<> dist(0, characters.size() - 1);

        string random_string;
        for (size_t i = 0; i < length; ++i) {
            random_string += characters[dist(generator)];
        }
        return random_string;
    }

    // Генерация случайных данных (строки в качестве ключей, int в качестве значений)
    vector<pair<string, int>> generate_random_data_2(size_t n, size_t key_length = 10, int value_min = 1, int value_max = 1000000) {
        random_device rd;
        mt19937 generator(rd());
        uniform_int_distribution<> value_dist(value_min, value_max);

        vector<pair<string, int>> data;
        for (size_t i = 0; i < n; ++i) {
            string key = generate_random_string(key_length);
            int value = value_dist(generator);
            data.emplace_back(key, value);
        }
        return data;
    }

    // Тестирование вставки
    template <typename HashFunction1, typename HashFunction2>
    void test_insertion_double_string(ofstream& file, vector<size_t> sizes, HashFunction1 hash_func1, HashFunction2 hash_func2, const string& hash_name1, const string& hash_name2) {
        for (size_t N : sizes) {
            auto data = generate_random_data_2(N);

            // DoubleHashTable
            HashTableDouble<string, int> double_table(N, hash_func1, hash_func2);
            auto start = high_resolution_clock::now();
            for (const auto& [key, value] : data) {
                double_table.insert(key, value);
            }
            auto end = high_resolution_clock::now();
            file << "DoubleHashTable," << hash_name1 << "," << hash_name2 << ",Insertion," << N << ","
                << fixed << setprecision(3) << duration<double, milli>(end - start).count() << "\n";

            // CuckooHashTable
            HashTableCuckoo<string, int> cuckoo_table(N, hash_func1, hash_func2);
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
    void test_search_double_string(ofstream& file, vector<size_t> sizes, HashFunction1 hash_func1, HashFunction2 hash_func2, const string& hash_name1, const string& hash_name2) {
        for (size_t N : sizes) {
            auto data = generate_random_data_2(N);

            // Создание таблиц и вставка данных
            HashTableDouble<string, int> double_table(N, hash_func1, hash_func2);
            HashTableCuckoo<string, int> cuckoo_table(N, hash_func1, hash_func2);
            for (const auto& [key, value] : data) {
                double_table.insert(key, value);
                cuckoo_table.insert(key, value);
            }

            // Генерация ключей для поиска
            vector<string> search_keys;
            for (size_t i = 0; i < N / 2; ++i) {
                search_keys.push_back(data[i].first); // Существующие ключи
            }
            for (size_t i = 0; i < N / 2; ++i) {
                search_keys.push_back(generate_random_string(10)); // Несуществующие ключи
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
    void test_erase_double_string(ofstream& file, vector<size_t> sizes, HashFunction1 hash_func1, HashFunction2 hash_func2, const string& hash_name1, const string& hash_name2) {
        for (size_t N : sizes) {
            auto data = generate_random_data_2(N);

            // Создание таблиц и вставка данных
            HashTableDouble<string, int> double_table(N, hash_func1, hash_func2);
            HashTableCuckoo<string, int> cuckoo_table(N, hash_func1, hash_func2);
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
