#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip> // ��� �������������� ������ �������
#include <fstream> // ��� ������ � ����
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

// ������� ��� ������ ������ � ����
void write_to_file(const string& filename, const string& data) {
    ofstream file(filename, ios::app); // ����� ����������
    if (!file.is_open()) {
        cerr << "������: �� ������� ������� ���� " << filename << " ��� ������.\n";
        return;
    }
    file << data << endl;
    file.close();
}

// ���� �������� ������� � ����������� HashTableTree
void test_insertion_speed(const vector<size_t>& sizes, const string& filename) {
    using namespace chrono;

    write_to_file(filename, "���� �������� �������:\n");

    for (size_t N : sizes) {
        stringstream results;
        results << "���������� ���������: " << N << "\n";
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
                    results << "������ CuckooHashTable: " << e.what() << "\n";
                    break;
                }
            }
            end = high_resolution_clock::now();
            results << "CuckooHashTable: " << fixed << setprecision(3)
                << duration<double, milli>(end - start).count() << " ms\n";
        }
        else {
            results << "CuckooHashTable: ��������� (����� 10,000 ���������).\n";
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

// ���� �������� ������ � ����������� HashTableTree
void test_search_speed(const vector<size_t>& sizes, const string& filename) {
    using namespace chrono;

    write_to_file(filename, "���� �������� ������:\n");

    for (size_t N : sizes) {
        stringstream results;
        results << "���������� ���������: " << N << "\n";
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
            results << "CuckooHashTable: ��������� (����� 10,000 ���������).\n";
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
    vector<size_t> sizes = { 1000, 5000, 10000, 20000, 50000 }; // ����� ��� CuckooHashTable
    string filename = "C:\\Users\\buddy\\OneDrive\\������� ����\\��������\\results\\test_results.txt";


    test_insertion_speed(sizes, filename);
    test_search_speed(sizes, filename);

    cout << "���������� �������� � ����: " << filename << endl;

    return 0;
}
