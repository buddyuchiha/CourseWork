#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <random>
#include "../algorithm/cuckoo_hash_table.h"
#include "../algorithm/chain_hash_table.h"
#include "../algorithm/adress_hash_table.h"
#include "../algorithm/hash_functions.h"

using namespace std;
using namespace LinearHashTable;
using namespace DoubleHashTable;
using namespace CuckooHashTable;
using namespace ListHashTable;
using namespace TreeHashTable;

void tree_hash_table_performance_test(const vector<pair<int, int>>& data, const vector<int>& search_keys, const string& filename) {
    HashTableTree<int, int> tree_table(data.size(), base_hash_function<int>);

    auto start = chrono::high_resolution_clock::now();
    for (const auto& [key, value] : data) {
        tree_table.insert(key, value);
    }
    auto end = chrono::high_resolution_clock::now();
    auto insertion_time = chrono::duration<double, milli>(end - start).count();

    start = chrono::high_resolution_clock::now();
    for (const auto& key : search_keys) {
        tree_table.search(key);
    }
    end = chrono::high_resolution_clock::now();
    auto search_time = chrono::duration<double, milli>(end - start).count();

    start = chrono::high_resolution_clock::now();
    for (const auto& key : search_keys) {
        tree_table.erase(key);
    }
    end = chrono::high_resolution_clock::now();
    auto deletion_time = chrono::duration<double, milli>(end - start).count();

    ofstream results_file(filename, ios::app);
    if (results_file.is_open()) {
        results_file << "TreeHashTable:\n";
        results_file << "Insertion time: " << fixed << setprecision(3) << insertion_time << " ms\n";
        results_file << "Search time: " << fixed << setprecision(3) << search_time << " ms\n";
        results_file << "Deletion time: " << fixed << setprecision(3) << deletion_time << " ms\n\n";
        results_file.close();
    }
}

void list_hash_table_performance_test(const vector<pair<int, int>>& data, const vector<int>& search_keys, const string& filename) {
    HashTableList<int, int> list_table(data.size());

    auto start = chrono::high_resolution_clock::now();
    for (const auto& [key, value] : data) {
        list_table.insert(key, value);
    }
    auto end = chrono::high_resolution_clock::now();
    auto insertion_time = chrono::duration<double, milli>(end - start).count();

    start = chrono::high_resolution_clock::now();
    for (const auto& key : search_keys) {
        list_table.search(key);
    }
    end = chrono::high_resolution_clock::now();
    auto search_time = chrono::duration<double, milli>(end - start).count();

    start = chrono::high_resolution_clock::now();
    for (const auto& key : search_keys) {
        list_table.erase(key);
    }
    end = chrono::high_resolution_clock::now();
    auto deletion_time = chrono::duration<double, milli>(end - start).count();

    ofstream results_file(filename, ios::app);
    if (results_file.is_open()) {
        results_file << "ListHashTable:\n";
        results_file << "Insertion time: " << fixed << setprecision(3) << insertion_time << " ms\n";
        results_file << "Search time: " << fixed << setprecision(3) << search_time << " ms\n";
        results_file << "Deletion time: " << fixed << setprecision(3) << deletion_time << " ms\n\n";
        results_file.close();
    }
}

void linear_hash_table_performance_test(const vector<pair<int, int>>& data, const vector<int>& search_keys, const string& filename) {
    HashTableLinear<int, int> linear_table(data.size());

    auto start = chrono::high_resolution_clock::now();
    for (const auto& [key, value] : data) {
        linear_table.insert(key, value);
    }
    auto end = chrono::high_resolution_clock::now();
    auto insertion_time = chrono::duration<double, milli>(end - start).count();

    start = chrono::high_resolution_clock::now();
    for (const auto& key : search_keys) {
        linear_table.search(key);
    }
    end = chrono::high_resolution_clock::now();
    auto search_time = chrono::duration<double, milli>(end - start).count();

    start = chrono::high_resolution_clock::now();
    for (const auto& key : search_keys) {
        linear_table.erase(key);
    }
    end = chrono::high_resolution_clock::now();
    auto deletion_time = chrono::duration<double, milli>(end - start).count();

    ofstream results_file(filename, ios::app);
    if (results_file.is_open()) {
        results_file << "LinearHashTable:\n";
        results_file << "Insertion time: " << fixed << setprecision(3) << insertion_time << " ms\n";
        results_file << "Search time: " << fixed << setprecision(3) << search_time << " ms\n";
        results_file << "Deletion time: " << fixed << setprecision(3) << deletion_time << " ms\n\n";
        results_file.close();
    }
}

void double_hash_table_performance_test(const vector<pair<int, int>>& data, const vector<int>& search_keys, const string& filename) {
    HashTableDouble<int, int> double_table(data.size(), base_hash_function<int>, murmur_hash<int>);

    auto start = chrono::high_resolution_clock::now();
    for (const auto& [key, value] : data) {
        double_table.insert(key, value);
    }
    auto end = chrono::high_resolution_clock::now();
    auto insertion_time = chrono::duration<double, milli>(end - start).count();

    start = chrono::high_resolution_clock::now();
    for (const auto& key : search_keys) {
        double_table.search(key);
    }
    end = chrono::high_resolution_clock::now();
    auto search_time = chrono::duration<double, milli>(end - start).count();

    start = chrono::high_resolution_clock::now();
    for (const auto& key : search_keys) {
        double_table.erase(key);
    }
    end = chrono::high_resolution_clock::now();
    auto deletion_time = chrono::duration<double, milli>(end - start).count();

    ofstream results_file(filename, ios::app);
    if (results_file.is_open()) {
        results_file << "DoubleHashTable:\n";
        results_file << "Insertion time: " << fixed << setprecision(3) << insertion_time << " ms\n";
        results_file << "Search time: " << fixed << setprecision(3) << search_time << " ms\n";
        results_file << "Deletion time: " << fixed << setprecision(3) << deletion_time << " ms\n\n";
        results_file.close();
    }
}

void cuckoo_hash_table_performance_test(const vector<pair<int, int>>& data, const vector<int>& search_keys, const string& filename) {
    HashTableCuckoo<int, int> cuckoo_table(data.size(), base_hash_function<int>, murmur_hash<int>);

    auto start = chrono::high_resolution_clock::now();
    for (const auto& [key, value] : data) {
        cuckoo_table.insert(key, value);
    }
    auto end = chrono::high_resolution_clock::now();
    auto insertion_time = chrono::duration<double, milli>(end - start).count();

    start = chrono::high_resolution_clock::now();
    for (const auto& key : search_keys) {
        cuckoo_table.search(key);
    }
    end = chrono::high_resolution_clock::now();
    auto search_time = chrono::duration<double, milli>(end - start).count();

    start = chrono::high_resolution_clock::now();
    for (const auto& key : search_keys) {
        cuckoo_table.erase(key);
    }
    end = chrono::high_resolution_clock::now();
    auto deletion_time = chrono::duration<double, milli>(end - start).count();

    ofstream results_file(filename, ios::app);
    if (results_file.is_open()) {
        results_file << "CuckooHashTable:\n";
        results_file << "Insertion time: " << fixed << setprecision(3) << insertion_time << " ms\n";
        results_file << "Search time: " << fixed << setprecision(3) << search_time << " ms\n";
        results_file << "Deletion time: " << fixed << setprecision(3) << deletion_time << " ms\n\n";
        results_file.close();
    }
}
