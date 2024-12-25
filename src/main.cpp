#include <iostream>
#include <vector>
#include <fstream>
#include "..\algorithm\hash_functions.h"
#include "..\algorithm\test_functions.h"
#include "..\algorithm\test_functions_string.h"
#include "..\algorithm\test_load_factor.h"
#include "..\algorithm\test_load_factor_string.h"

using namespace std;
using namespace NumberTests;     // Тесты для одиночных хэш-функций
using namespace NumberTestsDouble; // Тесты для двух хэш-функций
using namespace StringTests;     // Тесты со строковыми ключами
using namespace StringTestsDouble; // Тесты с двумя строковыми хэш-функциями
using namespace LoadTests;
using namespace StringLoadTests;

// Main: вызов тестов
int main() {
    vector<size_t> sizes = { 1000, 5000, 10000, 20000, 50000 };

    // Открытие файлов для записи результатов
    ofstream int_results_file("C:\\Users\\buddy\\OneDrive\\Рабочий стол\\курсовая\\results\\test_int_results.csv");
    ofstream double_results_file("C:\\Users\\buddy\\OneDrive\\Рабочий стол\\курсовая\\results\\test_double_int_results.csv");
    ofstream string_results_file("C:\\Users\\buddy\\OneDrive\\Рабочий стол\\курсовая\\results\\test_string_results.csv");
    ofstream double_string_results_file("C:\\Users\\buddy\\OneDrive\\Рабочий стол\\курсовая\\results\\test_double_string_results.csv");
    ofstream int_load_results_file("C:\\Users\\buddy\\OneDrive\\Рабочий стол\\курсовая\\results\\test_int_load_results.csv");
    ofstream double_load_results_file("C:\\Users\\buddy\\OneDrive\\Рабочий стол\\курсовая\\results\\test_double_int_load_results.csv");
    ofstream string_load_results_file("C:\\Users\\buddy\\OneDrive\\Рабочий стол\\курсовая\\results\\test_string_load_results.csv");
    ofstream double_string_load_results_file("C:\\Users\\buddy\\OneDrive\\Рабочий стол\\курсовая\\results\\test_double_string_load_results.csv");
    // Запись заголовков в CSV
    int_results_file << "Table,HashFunction1,HashFunction2,Operation,DataSize,Time(ms)\n";
    double_results_file << "Table,HashFunction1,HashFunction2,Operation,DataSize,Time(ms)\n";
    string_results_file << "Table,HashFunction1,HashFunction2,Operation,DataSize,Time(ms)\n";
    double_string_results_file << "Table,HashFunction1,HashFunction2,Operation,DataSize,Time(ms)\n";
    int_load_results_file << "Table,HashFunction1,HashFunction2,DataSize,LoadFactor\n";
    double_load_results_file << "Table,HashFunction1,HashFunction2,DataSize,LoadFactor\n";
    string_load_results_file << "Table,HashFunction1,HashFunction2,DataSize,LoadFactor\n";
    double_string_load_results_file << "Table,HashFunction1,HashFunction2,DataSize,LoadFactor\n";

    // Тесты с одной хэш-функцией для чисел
    cout << "Starting Single Hash Function Tests for Numbers...\n";
    test_insertion(int_results_file, sizes, base_hash_function<int>, "Base Hash Function");
    test_search(int_results_file, sizes, base_hash_function<int>, "Base Hash Function");
    test_erase(int_results_file, sizes, base_hash_function<int>, "Base Hash Function");

    test_insertion(int_results_file, sizes, murmur_hash<int>, "Murmur Hash Function");
    test_search(int_results_file, sizes, murmur_hash<int>, "Murmur Hash Function");
    test_erase(int_results_file, sizes, murmur_hash<int>, "Murmur Hash Function");

    test_insertion(int_results_file, sizes, fnv1a_hash<int>, "FNV-1a Hash Function");
    test_search(int_results_file, sizes, fnv1a_hash<int>, "FNV-1a Hash Function");
    test_erase(int_results_file, sizes, fnv1a_hash<int>, "FNV-1a Hash Function");

    // Тесты с двумя хэш-функциями для чисел
    cout << "Starting Double Hash Function Tests for Numbers...\n";
    test_insertion_double(double_results_file, sizes, base_hash_function<int>, murmur_hash<int>, "Base Hash Function", "Murmur Hash Function");
    test_search_double(double_results_file, sizes, base_hash_function<int>, murmur_hash<int>, "Base Hash Function", "Murmur Hash Function");
    test_erase_double(double_results_file, sizes, base_hash_function<int>, murmur_hash<int>, "Base Hash Function", "Murmur Hash Function");

    test_insertion_double(double_results_file, sizes, murmur_hash<int>, fnv1a_hash<int>, "Murmur Hash Function", "FNV-1a Hash Function");
    test_search_double(double_results_file, sizes, murmur_hash<int>, fnv1a_hash<int>, "Murmur Hash Function", "FNV-1a Hash Function");
    test_erase_double(double_results_file, sizes, murmur_hash<int>, fnv1a_hash<int>, "Murmur Hash Function", "FNV-1a Hash Function");

    test_insertion_double(double_results_file, sizes, base_hash_function<int>, fnv1a_hash<int>, "Base Hash Function", "FNV-1a Hash Function");
    test_search_double(double_results_file, sizes, base_hash_function<int>, fnv1a_hash<int>, "Base Hash Function", "FNV-1a Hash Function");
    test_erase_double(double_results_file, sizes, base_hash_function<int>, fnv1a_hash<int>, "Base Hash Function", "FNV-1a Hash Function");

    // Тесты с одной хэш-функцией для строк
    cout << "Starting Single Hash Function Tests for Strings...\n";
    test_insertion_string(string_results_file, sizes, sdbm_hash, "SDBM Hash Function");
    test_search_string(string_results_file, sizes, sdbm_hash, "SDBM Hash Function");
    test_erase_string(string_results_file, sizes, sdbm_hash, "SDBM Hash Function");

    test_insertion_string(string_results_file, sizes, djb2_hash, "DJB2 Hash Function");
    test_search_string(string_results_file, sizes, djb2_hash, "DJB2 Hash Function");
    test_erase_string(string_results_file, sizes, djb2_hash, "DJB2 Hash Function");

    test_insertion_string(string_results_file, sizes, city_hash, "City Hash Function");
    test_search_string(string_results_file, sizes, city_hash, "City Hash Function");
    test_erase_string(string_results_file, sizes, city_hash, "City Hash Function");

    // Тесты с двумя хэш-функциями для строк
    cout << "Starting Double Hash Function Tests for Strings...\n";
    test_insertion_double_string(double_string_results_file, sizes, sdbm_hash, djb2_hash, "SDBM Hash Function", "DJB2 Hash Function");
    test_search_double_string(double_string_results_file, sizes, sdbm_hash, djb2_hash, "SDBM Hash Function", "DJB2 Hash Function");
    test_erase_double_string(double_string_results_file, sizes, sdbm_hash, djb2_hash, "SDBM Hash Function", "DJB2 Hash Function");

    test_insertion_double_string(double_string_results_file, sizes, sdbm_hash, city_hash, "SDBM Hash Function", "City Hash Function");
    test_search_double_string(double_string_results_file, sizes, sdbm_hash, city_hash, "SDBM Hash Function", "City Hash Function");
    test_erase_double_string(double_string_results_file, sizes, sdbm_hash, city_hash, "SDBM Hash Function", "City Hash Function");

    test_insertion_double_string(double_string_results_file, sizes, djb2_hash, city_hash, "DJB2 Hash Function", "City Hash Function");
    test_search_double_string(double_string_results_file, sizes, djb2_hash, city_hash, "DJB2 Hash Function", "City Hash Function");
    test_erase_double_string(double_string_results_file, sizes, djb2_hash, city_hash, "DJB2 Hash Function", "City Hash Function");
    
    cout << "Starting Load Factor Tests for Single Hash Tables...\n";
    test_load_factor(int_load_results_file, sizes, base_hash_function<int>, "Base Hash Function");
    test_load_factor(int_load_results_file, sizes, murmur_hash<int>, "Murmur Hash Function");
    test_load_factor(int_load_results_file, sizes, fnv1a_hash<int>, "FNV-1a Hash Function");

    cout << "Starting Load Factor Tests for Double Hash Tables...\n";
    test_load_factor_double(double_load_results_file, sizes, base_hash_function<int>, murmur_hash<int>, "Base Hash Function", "Murmur Hash Function");
    test_load_factor_double(double_load_results_file, sizes, murmur_hash<int>, fnv1a_hash<int>, "Murmur Hash Function", "FNV-1a Hash Function");
    test_load_factor_double(double_load_results_file, sizes, base_hash_function<int>, fnv1a_hash<int>, "Base Hash Function", "FNV-1a Hash Function");

     //Тесты коэффициентов заполнения для строковых таблиц
    cout << "Starting Load Factor Tests for String Tables...\n";

    // Для одной хэш-функции
    test_load_factor_string(string_load_results_file, sizes, sdbm_hash, "SDBM Hash Function");
    test_load_factor_string(string_load_results_file, sizes, djb2_hash, "DJB2 Hash Function");
    test_load_factor_string(string_load_results_file, sizes, city_hash, "City Hash Function");

    // Для двух хэш-функций
    test_load_factor_double_string(double_string_load_results_file, sizes, sdbm_hash, djb2_hash, "SDBM Hash Function", "DJB2 Hash Function");
    test_load_factor_double_string(double_string_load_results_file, sizes, sdbm_hash, city_hash, "SDBM Hash Function", "City Hash Function");
    test_load_factor_double_string(double_string_load_results_file, sizes, djb2_hash, city_hash, "DJB2 Hash Function", "City Hash Function");

    // Закрытие файлов
    int_results_file.close();
    double_results_file.close();
    string_results_file.close();
    double_string_results_file.close();
    int_load_results_file.close();
    double_load_results_file.close();
    string_load_results_file.close();
    double_string_load_results_file.close();

    cout << "All tests completed. Results saved to CSV files.\n";

    return 0;
}
