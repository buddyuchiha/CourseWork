#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip> // Для форматирования вывода времени
#include <fstream> // Для записи в файл
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

// Функция для генерации случайных данных
vector<pair<int, int>> generate_random_data(size_t n, int key_min = 1, int key_max = 1000000, int value_min = 1, int value_max = 1000000) {
    vector<pair<int, int>> data;
    for (size_t i = 0; i < n; ++i) {
        int key = rand() % (key_max - key_min + 1) + key_min;
        int value = rand() % (value_max - value_min + 1) + value_min;
        data.emplace_back(key, value);
    }
    return data;
}

// Функция для записи данных в файл
void write_to_file(const string& filename, const string& data) {
    ofstream file(filename, ios::app); // Режим добавления
    if (!file.is_open()) {
        cerr << "Ошибка: не удалось открыть файл " << filename << " для записи.\n";
        return;
    }
    file << data << endl;
    file.close();
}

// Тест скорости вставки с добавлением HashTableTree
void test_insertion_speed(const vector<size_t>& sizes, const string& filename) {
    using namespace chrono;

    write_to_file(filename, "Тест скорости вставки:\n");

    for (size_t N : sizes) {
        stringstream results;
        results << "Количество элементов: " << N << "\n";
        auto data = generate_random_data(N);

        // LinearHashTable
        HashTableLinear<int, int> linear_table(10000);
        auto start = high_resolution_clock::now();
        for (const auto& [key, value] : data) {
            linear_table.insert(key, value);
        }
        auto end = high_resolution_clock::now();
        results << "LinearHashTable: " << fixed << setprecision(3)
            << duration<double, milli>(end - start).count() << " ms\n";

        // DoubleHashTable
        HashTableDouble<int, int> double_table(10000, base_hash_function<int>, murmur_hash<int>);
        start = high_resolution_clock::now();
        for (const auto& [key, value] : data) {
            double_table.insert(key, value);
        }
        end = high_resolution_clock::now();
        results << "DoubleHashTable: " << fixed << setprecision(3)
            << duration<double, milli>(end - start).count() << " ms\n";

        // CuckooHashTable
        if (N <= 10000) {
            HashTableCuckoo<int, int> cuckoo_table(10000, base_hash_function<int>, murmur_hash<int>);
            start = high_resolution_clock::now();
            for (const auto& [key, value] : data) {
                try {
                    cuckoo_table.insert(key, value);
                }
                catch (const runtime_error& e) {
                    results << "Ошибка CuckooHashTable: " << e.what() << "\n";
                    break;
                }
            }
            end = high_resolution_clock::now();
            results << "CuckooHashTable: " << fixed << setprecision(3)
                << duration<double, milli>(end - start).count() << " ms\n";
        }
        else {
            results << "CuckooHashTable: Пропущено (лимит 10,000 элементов).\n";
        }

        // HashTableList
        HashTableList<int, int> list_table(10000);
        start = high_resolution_clock::now();
        for (const auto& [key, value] : data) {
            list_table.insert(key, value);
        }
        end = high_resolution_clock::now();
        results << "HashTableList: " << fixed << setprecision(3)
            << duration<double, milli>(end - start).count() << " ms\n";

        // HashTableTree
        HashTableTree<int, int> tree_table(10000, base_hash_function<int>);
        start = high_resolution_clock::now();
        for (const auto& [key, value] : data) {
            tree_table.insert(key, value);
        }
        end = high_resolution_clock::now();
        results << "HashTableTree: " << fixed << setprecision(3)
            << duration<double, milli>(end - start).count() << " ms\n";

        results << "\n";
        write_to_file(filename, results.str());
    }
}

// Тест скорости поиска с добавлением HashTableTree
void test_search_speed(const vector<size_t>& sizes, const string& filename) {
    using namespace chrono;

    write_to_file(filename, "Тест скорости поиска:\n");

    for (size_t N : sizes) {
        stringstream results;
        results << "Количество элементов: " << N << "\n";
        auto data = generate_random_data(N);
        vector<int> search_keys;
        for (size_t i = 0; i < N / 2; ++i) {
            search_keys.push_back(data[i].first);
        }
        for (size_t i = 0; i < N / 2; ++i) {
            search_keys.push_back(rand() % 1000000);
        }

        // LinearHashTable
        HashTableLinear<int, int> linear_table(10000);
        for (const auto& [key, value] : data) {
            linear_table.insert(key, value);
        }
        auto start = high_resolution_clock::now();
        for (const auto& key : search_keys) {
            linear_table.search(key);
        }
        auto end = high_resolution_clock::now();
        results << "LinearHashTable: " << fixed << setprecision(3)
            << duration<double, milli>(end - start).count() << " ms\n";

        // DoubleHashTable
        HashTableDouble<int, int> double_table(10000, base_hash_function<int>, murmur_hash<int>);
        for (const auto& [key, value] : data) {
            double_table.insert(key, value);
        }
        start = high_resolution_clock::now();
        for (const auto& key : search_keys) {
            double_table.search(key);
        }
        end = high_resolution_clock::now();
        results << "DoubleHashTable: " << fixed << setprecision(3)
            << duration<double, milli>(end - start).count() << " ms\n";

        // CuckooHashTable
        if (N <= 10000) {
            HashTableCuckoo<int, int> cuckoo_table(10000, base_hash_function<int>, murmur_hash<int>);
            for (const auto& [key, value] : data) {
                cuckoo_table.insert(key, value);
            }
            start = high_resolution_clock::now();
            for (const auto& key : search_keys) {
                cuckoo_table.search(key);
            }
            end = high_resolution_clock::now();
            results << "CuckooHashTable: " << fixed << setprecision(3)
                << duration<double, milli>(end - start).count() << " ms\n";
        }
        else {
            results << "CuckooHashTable: Пропущено (лимит 10,000 элементов).\n";
        }

        // HashTableList
        HashTableList<int, int> list_table(10000);
        for (const auto& [key, value] : data) {
            list_table.insert(key, value);
        }
        start = high_resolution_clock::now();
        for (const auto& key : search_keys) {
            list_table.search(key);
        }
        end = high_resolution_clock::now();
        results << "HashTableList: " << fixed << setprecision(3)
            << duration<double, milli>(end - start).count() << " ms\n";

        // HashTableTree
        HashTableTree<int, int> tree_table(10000, base_hash_function<int>);
        for (const auto& [key, value] : data) {
            tree_table.insert(key, value);
        }
        start = high_resolution_clock::now();
        for (const auto& key : search_keys) {
            tree_table.search(key);
        }
        end = high_resolution_clock::now();
        results << "HashTableTree: " << fixed << setprecision(3)
            << duration<double, milli>(end - start).count() << " ms\n";

        results << "\n";
        write_to_file(filename, results.str());
    }
}

int main() {
    vector<size_t> sizes = { 1000, 5000, 10000, 20000, 50000 }; // Лимит для CuckooHashTable
    string filename = "C:\\Users\\buddy\\OneDrive\\Рабочий стол\\курсовая\\results\\test_results.txt";


    test_insertion_speed(sizes, filename);
    test_search_speed(sizes, filename);

    cout << "Результаты записаны в файл: " << filename << endl;

    return 0;
}
