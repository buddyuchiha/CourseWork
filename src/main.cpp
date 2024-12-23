#include <iostream>
#include "..\algorithm\chain_hash_table.h"
#include "..\algorithm\hash_functions.h"


using namespace std;
using namespace ListHashTable;
using namespace TreeHashTable;


void test_hash_functionality() {
    cout << "=== Testing Hash Table with Various Hash Functions ===\n";

    cout << "\n1. Base Hash Function\n";
    HashTableTree<int, int> base_table(10, base_hash_function<int>);
    base_table.insert(1, 100);
    base_table.insert(2, 200);
    base_table.insert(3, 300);
    base_table.print();

    cout << "\n2. Murmur Hash Function\n";
    HashTableTree<int, int> murmur_table(10, murmur_hash<int>);
    murmur_table.insert(1, 100);
    murmur_table.insert(2, 200);
    murmur_table.insert(3, 300);
    murmur_table.print();

    cout << "\n3. FNV-1a Hash Function\n";
    HashTableTree<int, int> fnv_table(10, fnv1a_hash<int>);
    fnv_table.insert(1, 100);
    fnv_table.insert(2, 200);
    fnv_table.insert(3, 300);
    fnv_table.print();

    cout << "=== Testing Hash Table with String Hash Functions ===\n";

    cout << "\n1. SDBM Hash Function\n";
    HashTableTree<string, string> sdbm_table(10, sdbm_hash);
    sdbm_table.insert("apple", "fruit");
    sdbm_table.insert("car", "vehicle");
    sdbm_table.insert("house", "building");
    sdbm_table.print();

    cout << "\n2. DJB2 Hash Function\n";
    HashTableTree<string, string> djb2_table(10, djb2_hash);
    djb2_table.insert("apple", "fruit");
    djb2_table.insert("car", "vehicle");
    djb2_table.insert("house", "building");
    djb2_table.print();

    cout << "\n3. City Hash Function\n";
    HashTableTree<string, string> city_table(10, city_hash);
    city_table.insert("apple", "fruit");
    city_table.insert("car", "vehicle");
    city_table.insert("house", "building");
    city_table.print();

    cout << "\n=== Testing Completed ===\n";
}

int main() {
    test_hash_functionality();
    return 0;
}
