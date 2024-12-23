#include <iostream>
#include "..\algorithm\chain_hash_table.h"
#include "..\algorithm\adress_hash_table.h"
#include "..\algorithm\cuckoo_hash_table.h"
#include "..\algorithm\hash_functions.h"

using namespace std;
using namespace CuckooHashTable;

int main() {
    // ��� �����: ���������� ������������������ ���-������� ��� string
    HashTableCuckoo<string, int> table_str(10, city_hash, sdbm_hash);

    // ������� ��������� ������
    table_str.insert("apple", 100);
    table_str.insert("banana", 200);
    table_str.insert("cherry", 300);

    // ������ �������
    table_str.print();
    cout << endl;

    // ����� �� ���������� �����
    string key = "banana";
    int* value = table_str.search(key);
    if (value) {
        cout << "Found " << key << " with value: " << *value << endl;
    }
    else {
        cout << key << " not found." << endl;
    }

    // �������� ������
    table_str.erase("banana");
    table_str.print();

    // ��� ����� �����: ���������� ���� ���-������� ��� int
    HashTableCuckoo<int, int> table_int(10,base_hash_function, base_hash_function<int>);

    // ������� ������ ���� int
    table_int.insert(1, 100);
    table_int.insert(2, 200);
    table_int.insert(3, 300);

    // ������ �������
    table_int.print();
    cout << endl;

    // ����� �� ����� int
    int* value_int = table_int.search(2);
    if (value_int) {
        cout << "Found 2 with value: " << *value_int << endl;
    }
    else {
        cout << "Not found 2." << endl;
    }

    // �������� ��������
    table_int.erase(2);
    table_int.print();

    return 0;
}
