#include <iostream>
#include "..\algorithm\algorithm.h"
#include "..\algorithm\hash_functions.h"


using namespace std;
using namespace algorithm;
using namespace algorithm2;


size_t hash_function(int key) {
    return key % 10; // ������� ���-������� ��� �������
}


int main() {
    // ���� 1: ������������� ���-������� � �������� 10
    HashTableTree<int, int> ht(10);
    cout << "Initial count: " << ht.get_count() << endl;  // ������� 0
    cout << "Initial size: " << ht.get_size() << endl;    // ������� 10

    // ���� 2: ������� ��������� � �������
    ht.insert(5, 100);
    ht.insert(15, 200);  // ��� ������� �������� � ������ 5 (simple_hash_function(5) == simple_hash_function(15))

    cout << "After insertions:" << endl;
    cout << "Count: " << ht.get_count() << endl;  // ������� 2
    cout << "Value for key 5: " << *ht.search(5) << endl;  // ������� 100
    cout << "Value for key 15: " << *ht.search(15) << endl; // ������� 200

    // ���� 3: ������� � ������� �������� (���� ���� ��� ����������)
    ht.insert_or_assign(5, 500);  // ���� 5 ��� ����������, �������� ������ ���� ���������
    cout << "After inserting or assigning key 5 with new value:" << endl;
    cout << "Value for key 5: " << *ht.search(5) << endl;  // ������� 500

    // ���� 4: �������� ������� ��������
    cout << "Contains 100: " << (ht.contains(100) ? "Yes" : "No") << endl;  // ������� No
    cout << "Contains 500: " << (ht.contains(500) ? "Yes" : "No") << endl;   // ������� Yes

    // ���� 5: �������� ��������
    ht.erase(5);  // �������� �������� � ������ 5
    cout << "After deleting key 5:" << endl;
    cout << "Count: " << ht.get_count() << endl;  // ������� 1
    cout << "Value for key 5: " << (ht.search(5) ? to_string(*ht.search(5)) : "Not found") << endl;  // ������� "Not found"

    // ���� 6: ��������� ������� �������� � ��� �� ������
    ht.insert(5, 300);  // ��������� ����� ���� 5 � ����� ���������
    cout << "After reinserting key 5 with new value:" << endl;
    cout << "Count: " << ht.get_count() << endl;  // ������� 2
    cout << "Value for key 5: " << *ht.search(5) << endl; // ������� 300

    // ���� 7: ���������� ��������� �����
    ht.insert(5, 400);  // ��������� ������� � ������ 5 ����� (��� �� ������� ��������)
    cout << "Count of key 5: " << ht.count(5) << endl;  // ������� 2

    // ���� 8: ��������� �������������
    ht.enable_rehashing();
    for (int i = 0; i < 100; ++i) {
        ht.insert(i, i * 10);  // ��������� ����� ���������
    }
    cout << "After enabling rehashing and inserting 100 elements:" << endl;
    cout << "Count: " << ht.get_count() << endl;  // ������� 102 (�� ���� 102 ��������)

    // ���� 9: ���������� �������������
    ht.disable_rehashing();
    ht.insert(101, 1010);  // ��������� ��� ���� �������
    cout << "After disabling rehashing and inserting key 101:" << endl;
    cout << "Count: " << ht.get_count() << endl;  // ������� 103

    // ���� 10: �������� ������ ������� ����� ��������
    ht.erase(15);  // ������� ������� � ������ 15
    ht.erase(5);   // ������� ������� � ������ 5
    cout << "After deleting keys 15 and 5:" << endl;
    cout << "Count: " << ht.get_count() << endl;  // ������� 101

    // ����� ��������� �������
    cout << "Final state of the hash table:" << endl;
    ht.print();  // ������ ���� ��������� �������

    return 0;
}
