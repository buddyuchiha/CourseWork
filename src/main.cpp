#include <iostream>
#include "..\algorithm\chain_hash_table.h"
#include "..\algorithm\adress_hash_table.h"
#include "..\algorithm\hash_functions.h"


using namespace std;
using namespace ListHashTable;
using namespace TreeHashTable;
using namespace LinearHashTable;


int main() {
    // Данные для тестирования
    vector<int> int_keys = { 1, 2, 11, 21, 31, 42 };
    vector<string> string_keys = { "apple", "banana", "grape", "orange", "peach", "plum" };

    // Проверяем целочисленные хэш-функции
    cout << "Testing integer hash functions:\n";

    // base_hash_function
    cout << "Base hash function:\n";
    HashTableLinear<int, string> int_table1(10, base_hash_function<int>);
    for (size_t i = 0; i < int_keys.size(); ++i) {
        int_table1.insert(int_keys[i], "Value_" + to_string(int_keys[i]));
    }
    int_table1.print();
    cout << "Collisions: " << int_table1.get_count() << "\n\n";

    // murmur_hash
    cout << "Murmur hash:\n";
    HashTableLinear<int, string> int_table2(10, murmur_hash<int>);
    for (size_t i = 0; i < int_keys.size(); ++i) {
        int_table2.insert(int_keys[i], "Value_" + to_string(int_keys[i]));
    }
    int_table2.print();
    cout << "Collisions: " << int_table2.get_count() << "\n\n";

    // fnv1a_hash
    cout << "FNV-1a hash:\n";
    HashTableLinear<int, string> int_table3(10, fnv1a_hash<int>);
    for (size_t i = 0; i < int_keys.size(); ++i) {
        int_table3.insert(int_keys[i], "Value_" + to_string(int_keys[i]));
    }
    int_table3.print();
    cout << "Collisions: " << int_table3.get_count() << "\n\n";

    // Проверяем строковые хэш-функции
    cout << "Testing string hash functions:\n";

    // sdbm_hash
    cout << "SDBM hash:\n";
    HashTableLinear<string, int> string_table1(10, sdbm_hash);
    for (size_t i = 0; i < string_keys.size(); ++i) {
        string_table1.insert(string_keys[i], i + 1);
    }
    string_table1.print();
    cout << "Collisions: " << string_table1.get_count() << "\n\n";

    // djb2_hash
    cout << "DJB2 hash:\n";
    HashTableLinear<string, int> string_table2(10, djb2_hash);
    for (size_t i = 0; i < string_keys.size(); ++i) {
        string_table2.insert(string_keys[i], i + 1);
    }
    string_table2.print();
    cout << "Collisions: " << string_table2.get_count() << "\n\n";

    // city_hash
    cout << "City hash:\n";
    HashTableLinear<string, int> string_table3(10, city_hash);
    for (size_t i = 0; i < string_keys.size(); ++i) {
        string_table3.insert(string_keys[i], i + 1);
    }
    string_table3.print();
    cout << "Collisions: " << string_table3.get_count() << "\n\n";

    return 0;
}
