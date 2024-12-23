#include <iostream>
#include "..\algorithm\algorithm.h"

using namespace std;
using namespace algorithm;


int task(int experiments, int size) {
	int sum = 0;
	for (int i = 0; i < experiments; i++) {
		HashTable <int, int> task_table(size, 1, 100, 1, 1000);
		sum += task_table.get_count();
	}
	return sum;
}


int main() {
    // ������� ���-������� �������������� �������
    HashTable<int, int> table(10);

    // �������� �������������
    table.enable_rehashing();
    cout << "Rehashing enabled" << endl;

    // ������������ �������
    cout << "Inserting values..." << endl;
    for (int i = 1; i <= 15; ++i) {
        table.insert(i, i * 10);
        cout << "Inserted: Key = " << i << ", Value = " << i * 10 << endl;
    }

    // ������ �������
    cout << "\nHash Table after insertion:" << endl;
    table.print();

    // ������������ ������
    cout << "\nSearching values..." << endl;
    for (int i = 1; i <= 15; ++i) {
        int* value = table.search(i);
        if (value) {
            cout << "Found: Key = " << i << ", Value = " << *value << endl;
        }
        else {
            cout << "Key " << i << " not found" << endl;
        }
    }

    // ������������ ��������
    cout << "\nDeleting keys 3, 7, 10..." << endl;
    table.erase(3);
    table.erase(7);
    table.erase(10);

    // ������ ������� ����� ��������
    cout << "\nHash Table after deletion:" << endl;
    table.print();

    // �������� contains
    cout << "\nChecking if values exist:" << endl;
    for (int i = 1; i <= 15; ++i) {
        if (table.contains(i * 10)) {
            cout << "Value " << i * 10 << " exists in the table" << endl;
        }
        else {
            cout << "Value " << i * 10 << " does not exist in the table" << endl;
        }
    }

    // ������������ insert_or_assign
    cout << "\nTesting insert_or_assign..." << endl;
    table.insert_or_assign(5, 999);
    table.insert_or_assign(13, 888);
    table.insert_or_assign(20, 777); // ����� ����

    // ������ ������� ����� insert_or_assign
    cout << "\nHash Table after insert_or_assign:" << endl;
    table.print();

    // ��������� ������� �������
    cout << "\nHash Table size: " << table.get_size() << endl;

    // ��������� ���������� ���������
    cout << "Hash Table element count: " << table.get_count() << endl;

    // ���������� �������������
    table.disable_rehashing();
    cout << "\nRehashing disabled" << endl;

    // ���������� ����� �������� ��� �������������
    cout << "Inserting more values without rehashing..." << endl;
    for (int i = 16; i <= 20; ++i) {
        table.insert(i, i * 10);
    }

    // ������ �������
    cout << "\nHash Table after inserting more values:" << endl;
    table.print();

    return 0;
}
