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
    // Тест 1: создание и вывод хеш-таблицы
    cout << "Тест 1: Создание и вывод хеш-таблицы" << endl;
    HashTableList<int, string> table(10);
    table.insert(1, "Value1");
    table.insert(2, "Value2");
    table.insert(3, "Value3");
    table.print(); // Ожидаем, что будут выведены данные

    // Тест 2: поиск значений по ключу
    cout << "Тест 2: Поиск значений по ключу" << endl;
    string* val = table.search(2);
    if (val) {
        cout << "Найдено значение для ключа 2: " << *val << endl;
    }
    else {
        cout << "Значение для ключа 2 не найдено." << endl;
    }

    // Тест 3: вставка или обновление значения по ключу
    cout << "Тест 3: Вставка или обновление значения по ключу" << endl;
    table.insert_or_assign(3, "UpdatedValue3"); // Обновим значение для ключа 3
    table.insert_or_assign(4, "Value4"); // Вставим новое значение
    table.print(); // Ожидаем, что значение для ключа 3 будет обновлено

    // Тест 4: удаление элемента
    cout << "Тест 4: Удаление элемента" << endl;
    bool erased = table.erase(2);
    if (erased) {
        cout << "Элемент с ключом 2 был удален." << endl;
    }
    else {
        cout << "Не удалось удалить элемент с ключом 2." << endl;
    }
    table.print(); // После удаления ключа 2 его не должно быть в таблице

    // Тест 5: проверка на наличие значения
    cout << "Тест 5: Проверка на наличие значения" << endl;
    bool contains = table.contains("Value4");
    if (contains) {
        cout << "Таблица содержит значение 'Value4'." << endl;
    }
    else {
        cout << "Таблица не содержит значение 'Value4'." << endl;
    }

    // Тест 6: подсчет элементов с данным ключом
    cout << "Тест 6: Подсчет элементов с данным ключом" << endl;
    int count = table.count(3);
    cout << "Количество элементов с ключом 3: " << count << endl;

    // Тест 7: проверка на вкл/выкл рехеширования
    cout << "Тест 7: Включение и выключение рехеширования" << endl;
    table.enable_rehashing();
    table.insert(5, "Value5"); // При необходимости рехеширование должно произойти
    table.disable_rehashing();
    table.insert(6, "Value6"); // Рехеширование больше не происходит
    table.print();

    // Тест 8: копирование хеш-таблицы
    cout << "Тест 8: Копирование хеш-таблицы" << endl;
    HashTableList<int, string> copied_table = table;
    copied_table.print(); // Ожидаем, что таблица будет скопирована корректно

    return 0;
}

