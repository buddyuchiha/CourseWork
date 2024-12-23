#include <iostream>
#include "..\algorithm\chain_hash_table.h"
#include "..\algorithm\adress_hash_table.h"
#include "..\algorithm\cuckoo_hash_table.h"
#include "..\algorithm\hash_functions.h"

using namespace std;
using namespace CuckooHashTable;

int main() {
    // Для строк: используем специализированные хеш-функции для string
    HashTableCuckoo<string, int> table_str(10, city_hash, sdbm_hash);

    // Вставка строковых данных
    table_str.insert("apple", 100);
    table_str.insert("banana", 200);
    table_str.insert("cherry", 300);

    // Печать таблицы
    table_str.print();
    cout << endl;

    // Поиск по строковому ключу
    string key = "banana";
    int* value = table_str.search(key);
    if (value) {
        cout << "Found " << key << " with value: " << *value << endl;
    }
    else {
        cout << key << " not found." << endl;
    }

    // Удаление строки
    table_str.erase("banana");
    table_str.print();

    // Для целых чисел: используем одну хеш-функцию для int
    HashTableCuckoo<int, int> table_int(10,base_hash_function, base_hash_function<int>);

    // Вставка данных типа int
    table_int.insert(1, 100);
    table_int.insert(2, 200);
    table_int.insert(3, 300);

    // Печать таблицы
    table_int.print();
    cout << endl;

    // Поиск по ключу int
    int* value_int = table_int.search(2);
    if (value_int) {
        cout << "Found 2 with value: " << *value_int << endl;
    }
    else {
        cout << "Not found 2." << endl;
    }

    // Удаление элемента
    table_int.erase(2);
    table_int.print();

    return 0;
}
