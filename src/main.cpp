#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip> // ��� �������������� ������ �������
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

// ������� ��� ��������� ��������� ������
vector<pair<int, int>> generate_random_data(size_t n, int key_min = 1, int key_max = 1000000, int value_min = 1, int value_max = 1000000) {
    vector<pair<int, int>> data;
    for (size_t i = 0; i < n; ++i) {
        int key = rand() % (key_max - key_min + 1) + key_min;
        int value = rand() % (value_max - value_min + 1) + value_min;
        data.emplace_back(key, value);
    }
    return data;
}

// ���� �������� ������� � ����������� HashTableTree
void test_insertion_speed(vector<size_t> sizes) {
    using namespace chrono;

    for (size_t N : sizes) {
        cout << "Testing insertion speed for N = " << N << "\n";
        auto data = generate_random_data(N);

        // LinearHashTable
        HashTableLinear<int, int> linear_table(10000);
        auto start = high_resolution_clock::now();
        for (const auto& [key, value] : data) {
            linear_table.insert(key, value);
        }
        auto end = high_resolution_clock::now();
        cout << "LinearHashTable Insertion Time: "
            << fixed << setprecision(3)
            << duration<double, milli>(end - start).count() << "ms\n";

        // DoubleHashTable
        HashTableDouble<int, int> double_table(10000, base_hash_function<int>, murmur_hash<int>);
        start = high_resolution_clock::now();
        for (const auto& [key, value] : data) {
            double_table.insert(key, value);
        }
        end = high_resolution_clock::now();
        cout << "DoubleHashTable Insertion Time: "
            << fixed << setprecision(3)
            << duration<double, milli>(end - start).count() << "ms\n";

        // CuckooHashTable (����������� �� 10,000 ���������)
        if (N <= 10000) {
            HashTableCuckoo<int, int> cuckoo_table(10000, base_hash_function<int>, murmur_hash<int>);
            start = high_resolution_clock::now();
            for (const auto& [key, value] : data) {
                try {
                    cuckoo_table.insert(key, value);
                }
                catch (const runtime_error& e) {
                    cout << "Error during CuckooHashTable insertion: " << e.what() << "\n";
                    break;
                }
            }
            end = high_resolution_clock::now();
            cout << "CuckooHashTable Insertion Time: "
                << fixed << setprecision(3)
                << duration<double, milli>(end - start).count() << "ms\n";
        }
        else {
            cout << "CuckooHashTable skipped for N = " << N << " (limit 20,000 elements).\n";
        }

        // HashTableList (Linked List)
        HashTableList<int, int> list_table(10000);
        start = high_resolution_clock::now();
        for (const auto& [key, value] : data) {
            list_table.insert(key, value);
        }
        end = high_resolution_clock::now();
        cout << "HashTableList Insertion Time: "
            << fixed << setprecision(3)
            << duration<double, milli>(end - start).count() << "ms\n";

        // HashTableTree (AVL Tree)
        HashTableTree<int, int> tree_table(10000, base_hash_function<int>);
        start = high_resolution_clock::now();
        for (const auto& [key, value] : data) {
            tree_table.insert(key, value);
        }
        end = high_resolution_clock::now();
        cout << "HashTableTree Insertion Time: "
            << fixed << setprecision(3)
            << duration<double, milli>(end - start).count() << "ms\n\n";
    }
}

// Тестирование скорости удаления для разных хеш-таблиц
void test_erase_speed(vector<size_t> sizes) {
    using namespace chrono;

    for (size_t N : sizes) {
        cout << "Testing erase speed for N = " << N << "\n";
        auto data = generate_random_data(N);

        // LinearHashTable
        HashTableLinear<int, int> linear_table(10000);
        for (const auto& [key, value] : data) {
            linear_table.insert(key, value);
        }
        auto start = high_resolution_clock::now();
        for (const auto& [key, value] : data) {
            linear_table.erase(key);
        }
        auto end = high_resolution_clock::now();
        cout << "LinearHashTable Erase Time: "
            << fixed << setprecision(3)
            << duration<double, milli>(end - start).count() << "ms\n";

        // DoubleHashTable
        HashTableDouble<int, int> double_table(10000, base_hash_function<int>, murmur_hash<int>);
        for (const auto& [key, value] : data) {
            double_table.insert(key, value);
        }
        start = high_resolution_clock::now();
        for (const auto& [key, value] : data) {
            double_table.erase(key);
        }
        end = high_resolution_clock::now();
        cout << "DoubleHashTable Erase Time: "
            << fixed << setprecision(3)
            << duration<double, milli>(end - start).count() << "ms\n";

        // CuckooHashTable
        if (N <= 10000) {
            HashTableCuckoo<int, int> cuckoo_table(10000, base_hash_function<int>, murmur_hash<int>);
            for (const auto& [key, value] : data) {
                cuckoo_table.insert(key, value);
            }
            start = high_resolution_clock::now();
            for (const auto& [key, value] : data) {
                cuckoo_table.erase(key);
            }
            end = high_resolution_clock::now();
            cout << "CuckooHashTable Erase Time: "
                << fixed << setprecision(3)
                << duration<double, milli>(end - start).count() << "ms\n";
        }
        else {
            cout << "CuckooHashTable skipped for N = " << N << " (limit 20,000 elements).\n";
        }

        // HashTableList
        HashTableList<int, int> list_table(10000);
        for (const auto& [key, value] : data) {
            list_table.insert(key, value);
        }
        start = high_resolution_clock::now();
        for (const auto& [key, value] : data) {
            list_table.erase(key);
        }
        end = high_resolution_clock::now();
        cout << "HashTableList Erase Time: "
            << fixed << setprecision(3)
            << duration<double, milli>(end - start).count() << "ms\n";

        // HashTableTree (AVL Tree)
        HashTableTree<int, int> tree_table(10000, base_hash_function<int>);
        for (const auto& [key, value] : data) {
            tree_table.insert(key, value);
        }
        start = high_resolution_clock::now();
        for (const auto& [key, value] : data) {
            tree_table.erase(key);
        }
        end = high_resolution_clock::now();
        cout << "HashTableTree Erase Time: "
            << fixed << setprecision(3)
            << duration<double, milli>(end - start).count() << "ms\n\n";
    }
}


// ���� �������� ������ � ����������� HashTableTree
void test_search_speed(vector<size_t> sizes) {
    using namespace chrono;

    for (size_t N : sizes) {
        cout << "Testing search speed for N = " << N << "\n";
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
        cout << "LinearHashTable Search Time: "
            << fixed << setprecision(3)
            << duration<double, milli>(end - start).count() << "ms\n";

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
        cout << "DoubleHashTable Search Time: "
            << fixed << setprecision(3)
            << duration<double, milli>(end - start).count() << "ms\n";

        // CuckooHashTable (����������� �� 10,000 ���������)
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
            cout << "CuckooHashTable Search Time: "
                << fixed << setprecision(3)
                << duration<double, milli>(end - start).count() << "ms\n";
        }
        else {
            cout << "CuckooHashTable skipped for N = " << N << " (limit 20,000 elements).\n";
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
        cout << "HashTableList Search Time: "
            << fixed << setprecision(3)
            << duration<double, milli>(end - start).count() << "ms\n";

        // HashTableTree (AVL Tree)
        HashTableTree<int, int> tree_table(10000, base_hash_function<int>);
        for (const auto& [key, value] : data) {
            tree_table.insert(key, value);
        }
        start = high_resolution_clock::now();
        for (const auto& key : search_keys) {
            tree_table.search(key);
        }
        end = high_resolution_clock::now();
        cout << "HashTableTree Search Time: "
            << fixed << setprecision(3)
            << duration<double, milli>(end - start).count() << "ms\n\n";
    }
}

int main() {
    vector<size_t> sizes = { 1000, 5000, 10000, 20000, 50000 }; // Примерные размеры для тестирования

    cout << "Starting Insertion Speed Test:\n";
    test_insertion_speed(sizes);

    cout << "\nStarting Search Speed Test:\n";
    test_search_speed(sizes);

    cout << "\nStarting Erase Speed Test:\n";
    test_erase_speed(sizes);  // Новый тест на удаление

    return 0;
}
