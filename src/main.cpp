#include <iostream>
#include "..\algorithm\chain_hash_table.h"
#include "..\algorithm\adress_hash_table.h"
#include "..\algorithm\hash_functions.h"


using namespace std;
using namespace ListHashTable;
using namespace TreeHashTable;
using namespace LinearHashTable;
using namespace DoubleHashTable;


int main() {
    // �������� ������� � ������� ������������
    HashTableDouble<int, string> table(10, base_hash_function<int>, murmur_hash<int>);

    cout << "=== Testing HashTableDouble ===\n";

    // 1. ������������ insert()
    cout << "Inserting elements...\n";
    table.insert(1, "One");
    table.insert(2, "Two");
    table.insert(11, "Eleven"); // ��������
    table.insert(21, "Twenty-One"); // ��������
    table.insert(31, "Thirty-One"); // ��������
    table.print();

    // 2. ������������ search()
    cout << "\nSearching for keys:\n";
    for (int key : {1, 11, 21, 42}) {
        string* result = table.search(key);
        if (result) {
            cout << "Key " << key << " found with value: " << *result << "\n";
        }
        else {
            cout << "Key " << key << " not found.\n";
        }
    }

    // 3. ������������ contains()
    cout << "\nChecking if values exist:\n";
    for (string value : {"Two", "Twenty-One", "Thirty-Two"}) {
        if (table.contains(value)) {
            cout << "Value '" << value << "' exists in the table.\n";
        }
        else {
            cout << "Value '" << value << "' does not exist in the table.\n";
        }
    }

    // 4. ������������ insert_or_assign()
    cout << "\nInserting or assigning new values for existing keys:\n";
    table.insert_or_assign(2, "Second");
    table.insert_or_assign(21, "Updated-Twenty-One");
    table.print();

    // 5. ������������ erase()
    cout << "\nErasing keys:\n";
    for (int key : {1, 21, 42}) {
        if (table.erase(key)) {
            cout << "Key " << key << " erased successfully.\n";
        }
        else {
            cout << "Key " << key << " not found.\n";
        }
    }
    table.print();

    // 6. ������������ get_count()
    cout << "\nNumber of collisions: " << table.get_count() << "\n";

    // 7. ������������ get_size() � count()
    cout << "\nTable size: " << table.get_size() << "\n";
    cout << "Number of elements in the table: " << table.count() << "\n";

    return 0;
}
