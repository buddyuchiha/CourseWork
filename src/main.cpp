#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
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

// Генерация случайных данных
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
void test_insertion_double(vector<size_t> sizes, HashFunction1 hash_func1, HashFunction2 hash_func2, const string& hash_name1, const string& hash_name2) {
    cout << "\nTesting Insertion Speed for DoubleHashTable and CuckooHashTable\n";
    cout << "Hash Functions: " << hash_name1 << " and " << hash_name2 << "\n";

    for (size_t N : sizes) {
        cout << "\nTesting insertion speed for N = " << N << "\n";
        auto data = generate_random_data(N);

        // DoubleHashTable
        cout << "Testing DoubleHashTable...\n";
        HashTableDouble<int, int> double_table(N, hash_func1, hash_func2);
        auto start = high_resolution_clock::now();
        for (const auto& [key, value] : data) {
            double_table.insert(key, value);
        }
        auto end = high_resolution_clock::now();
        cout << "DoubleHashTable Insertion Time: "
            << fixed << setprecision(3)
            << duration<double, milli>(end - start).count() << " ms\n";

        // CuckooHashTable
        cout << "Testing CuckooHashTable...\n";
        HashTableCuckoo<int, int> cuckoo_table(N, hash_func1, hash_func2);
        start = high_resolution_clock::now();
        for (const auto& [key, value] : data) {
            cuckoo_table.insert(key, value);
        }
        end = high_resolution_clock::now();
        cout << "CuckooHashTable Insertion Time: "
            << fixed << setprecision(3)
            << duration<double, milli>(end - start).count() << " ms\n";
    }
}

// Тестирование поиска
template <typename HashFunction1, typename HashFunction2>
void test_search_double(vector<size_t> sizes, HashFunction1 hash_func1, HashFunction2 hash_func2, const string& hash_name1, const string& hash_name2) {
    cout << "\nTesting Search Speed for DoubleHashTable and CuckooHashTable\n";
    cout << "Hash Functions: " << hash_name1 << " and " << hash_name2 << "\n";

    for (size_t N : sizes) {
        cout << "\nTesting search speed for N = " << N << "\n";
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

        // Тестирование поиска
        cout << "Testing DoubleHashTable Search...\n";
        auto start = high_resolution_clock::now();
        for (const auto& key : search_keys) {
            double_table.search(key);
        }
        auto end = high_resolution_clock::now();
        cout << "DoubleHashTable Search Time: "
            << fixed << setprecision(3)
            << duration<double, milli>(end - start).count() << " ms\n";

        cout << "Testing CuckooHashTable Search...\n";
        start = high_resolution_clock::now();
        for (const auto& key : search_keys) {
            cuckoo_table.search(key);
        }
        end = high_resolution_clock::now();
        cout << "CuckooHashTable Search Time: "
            << fixed << setprecision(3)
            << duration<double, milli>(end - start).count() << " ms\n";
    }
}

// Тестирование удаления
template <typename HashFunction1, typename HashFunction2>
void test_erase_double(vector<size_t> sizes, HashFunction1 hash_func1, HashFunction2 hash_func2, const string& hash_name1, const string& hash_name2) {
    cout << "\nTesting Erase Speed for DoubleHashTable and CuckooHashTable\n";
    cout << "Hash Functions: " << hash_name1 << " and " << hash_name2 << "\n";

    for (size_t N : sizes) {
        cout << "\nTesting erase speed for N = " << N << "\n";
        auto data = generate_random_data(N);

        // Создание таблиц и вставка данных
        HashTableDouble<int, int> double_table(N, hash_func1, hash_func2);
        HashTableCuckoo<int, int> cuckoo_table(N, hash_func1, hash_func2);
        for (const auto& [key, value] : data) {
            double_table.insert(key, value);
            cuckoo_table.insert(key, value);
        }

        // Тестирование удаления
        cout << "Testing DoubleHashTable Erase...\n";
        auto start = high_resolution_clock::now();
        for (const auto& [key, value] : data) {
            double_table.erase(key);
        }
        auto end = high_resolution_clock::now();
        cout << "DoubleHashTable Erase Time: "
            << fixed << setprecision(3)
            << duration<double, milli>(end - start).count() << " ms\n";

        cout << "Testing CuckooHashTable Erase...\n";
        start = high_resolution_clock::now();
        for (const auto& [key, value] : data) {
            cuckoo_table.erase(key);
        }
        end = high_resolution_clock::now();
        cout << "CuckooHashTable Erase Time: "
            << fixed << setprecision(3)
            << duration<double, milli>(end - start).count() << " ms\n";
    }
}

// Main: вызов тестов
int main() {
    vector<size_t> sizes = { 1000, 5000, 10000, 20000, 50000 };

    cout << "Starting Tests...\n";

    // Тесты для BaseHash и MurmurHash
    test_insertion_double(sizes, base_hash_function<int>, murmur_hash<int>, "Base Hash Function", "Murmur Hash Function");
    test_search_double(sizes, base_hash_function<int>, murmur_hash<int>, "Base Hash Function", "Murmur Hash Function");
    test_erase_double(sizes, base_hash_function<int>, murmur_hash<int>, "Base Hash Function", "Murmur Hash Function");

    // Тесты для MurmurHash и FNV-1a
    test_insertion_double(sizes, murmur_hash<int>, fnv1a_hash<int>, "Murmur Hash Function", "FNV-1a Hash Function");
    test_search_double(sizes, murmur_hash<int>, fnv1a_hash<int>, "Murmur Hash Function", "FNV-1a Hash Function");
    test_erase_double(sizes, murmur_hash<int>, fnv1a_hash<int>, "Murmur Hash Function", "FNV-1a Hash Function");

    return 0;
}
