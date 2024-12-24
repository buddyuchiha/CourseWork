#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <fstream>
#include "..\algorithm\chain_hash_table.h"
#include "..\algorithm\adress_hash_table.h"
#include "..\algorithm\cuckoo_hash_table.h"
#include "..\algorithm\hash_functions.h"
#include "..\algorithm\test_functions.h"

using namespace std;
using namespace LinearHashTable;  // Линейное пробирование
using namespace DoubleHashTable; // Двойное хэширование
using namespace CuckooHashTable; // Кукушкина хэш-таблица
using namespace ListHashTable;   // Метод цепочек (список)
using namespace TreeHashTable;   // Метод цепочек (AVL-дерево)
using namespace chrono;          // Для измерения времени
using namespace NumberTests;     // Тесты для одиночных хэш-функций
using namespace NumberTestsDouble; // Тесты для двух хэш-функций

// Main: вызов тестов
int main() {
    vector<size_t> sizes = { 1000, 5000, 10000, 20000, 50000 };

    // Открытие файлов для записи результатов
    ofstream int_results_file("C:\\Users\\buddy\\OneDrive\\Рабочий стол\\курсовая\\results\\test_int_results.csv");
    ofstream double_results_file("C:\\Users\\buddy\\OneDrive\\Рабочий стол\\курсовая\\results\\test_double_int_results.csv");

    // Запись заголовков в CSV
    int_results_file << "Table,HashFunction1,HashFunction2,Operation,DataSize,Time(ms)\n";
    double_results_file << "Table,HashFunction1,HashFunction2,Operation,DataSize,Time(ms)\n";

    // Тесты с одной хэш-функцией
    cout << "Starting Single Hash Function Tests...\n";
    test_insertion(int_results_file, sizes, base_hash_function<int>, "Base Hash Function");
    test_search(int_results_file, sizes, base_hash_function<int>, "Base Hash Function");
    test_erase(int_results_file, sizes, base_hash_function<int>, "Base Hash Function");

    test_insertion(int_results_file, sizes, murmur_hash<int>, "Murmur Hash Function");
    test_search(int_results_file, sizes, murmur_hash<int>, "Murmur Hash Function");
    test_erase(int_results_file, sizes, murmur_hash<int>, "Murmur Hash Function");

    test_insertion(int_results_file, sizes, fnv1a_hash<int>, "FNV-1a Hash Function");
    test_search(int_results_file, sizes, fnv1a_hash<int>, "FNV-1a Hash Function");
    test_erase(int_results_file, sizes, fnv1a_hash<int>, "FNV-1a Hash Function");

    // Тесты с двумя хэш-функциями
    cout << "Starting Double Hash Function Tests...\n";
    test_insertion_double(double_results_file, sizes, base_hash_function<int>, murmur_hash<int>, "Base Hash Function", "Murmur Hash Function");
    test_search_double(double_results_file, sizes, base_hash_function<int>, murmur_hash<int>, "Base Hash Function", "Murmur Hash Function");
    test_erase_double(double_results_file, sizes, base_hash_function<int>, murmur_hash<int>, "Base Hash Function", "Murmur Hash Function");

    test_insertion_double(double_results_file, sizes, murmur_hash<int>, fnv1a_hash<int>, "Murmur Hash Function", "FNV-1a Hash Function");
    test_search_double(double_results_file, sizes, murmur_hash<int>, fnv1a_hash<int>, "Murmur Hash Function", "FNV-1a Hash Function");
    test_erase_double(double_results_file, sizes, murmur_hash<int>, fnv1a_hash<int>, "Murmur Hash Function", "FNV-1a Hash Function");

    test_insertion_double(double_results_file, sizes, base_hash_function<int>, fnv1a_hash<int>, "Base Hash Function", "FNV-1a Hash Function");
    test_search_double(double_results_file, sizes, base_hash_function<int>, fnv1a_hash<int>, "Base Hash Function", "FNV-1a Hash Function");
    test_erase_double(double_results_file, sizes, base_hash_function<int>, fnv1a_hash<int>, "Base Hash Function", "FNV-1a Hash Function");

    // Закрытие файлов
    int_results_file.close();
    double_results_file.close();

    cout << "Tests completed. Results saved to CSV files.\n";

    return 0;
}
