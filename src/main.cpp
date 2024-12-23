#include <iostream>
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

int main() {
    // ���� 1: �������� � ����� ���-�������
    cout << "���� 1: �������� � ����� ���-�������" << endl;
    HashTableList<int, string> table(10);
    table.insert(1, "Value1");
    table.insert(2, "Value2");
    table.insert(3, "Value3");
    table.print(); // �������, ��� ����� �������� ������

    // ���� 2: ����� �������� �� �����
    cout << "���� 2: ����� �������� �� �����" << endl;
    string* val = table.search(2);
    if (val) {
        cout << "������� �������� ��� ����� 2: " << *val << endl;
    }
    else {
        cout << "�������� ��� ����� 2 �� �������." << endl;
    }

    // ���� 3: ������� ��� ���������� �������� �� �����
    cout << "���� 3: ������� ��� ���������� �������� �� �����" << endl;
    table.insert_or_assign(3, "UpdatedValue3"); // ������� �������� ��� ����� 3
    table.insert_or_assign(4, "Value4"); // ������� ����� ��������
    table.print(); // �������, ��� �������� ��� ����� 3 ����� ���������

    // ���� 4: �������� ��������
    cout << "���� 4: �������� ��������" << endl;
    bool erased = table.erase(2);
    if (erased) {
        cout << "������� � ������ 2 ��� ������." << endl;
    }
    else {
        cout << "�� ������� ������� ������� � ������ 2." << endl;
    }
    table.print(); // ����� �������� ����� 2 ��� �� ������ ���� � �������

    // ���� 5: �������� �� ������� ��������
    cout << "���� 5: �������� �� ������� ��������" << endl;
    bool contains = table.contains("Value4");
    if (contains) {
        cout << "������� �������� �������� 'Value4'." << endl;
    }
    else {
        cout << "������� �� �������� �������� 'Value4'." << endl;
    }

    // ���� 6: ������� ��������� � ������ ������
    cout << "���� 6: ������� ��������� � ������ ������" << endl;
    int count = table.count(3);
    cout << "���������� ��������� � ������ 3: " << count << endl;

    // ���� 7: �������� �� ���/���� �������������
    cout << "���� 7: ��������� � ���������� �������������" << endl;
    table.enable_rehashing();
    table.insert(5, "Value5"); // ��� ������������� ������������� ������ ���������
    table.disable_rehashing();
    table.insert(6, "Value6"); // ������������� ������ �� ����������
    table.print();

    // ���� 8: ����������� ���-�������
    cout << "���� 8: ����������� ���-�������" << endl;
    HashTableList<int, string> copied_table = table;
    copied_table.print(); // �������, ��� ������� ����� ����������� ���������

    return 0;
}

