#include <iostream>
#include "..\algorithm\algorithm.h"
#include "..\algorithm\hash_functions.h"


using namespace std;
using namespace algorithm;
using namespace algorithm2;


size_t hash_function(int key) {
    return key % 10; // Простой хеш-функции для примера
}


int main() {
    // Тест 1: Инициализация хеш-таблицы с размером 10
    HashTableTree<int, int> ht(10);
    cout << "Initial count: " << ht.get_count() << endl;  // Ожидаем 0
    cout << "Initial size: " << ht.get_size() << endl;    // Ожидаем 10

    // Тест 2: Вставка элементов в таблицу
    ht.insert(5, 100);
    ht.insert(15, 200);  // Это вызовет коллизию с ключом 5 (simple_hash_function(5) == simple_hash_function(15))

    cout << "After insertions:" << endl;
    cout << "Count: " << ht.get_count() << endl;  // Ожидаем 2
    cout << "Value for key 5: " << *ht.search(5) << endl;  // Ожидаем 100
    cout << "Value for key 15: " << *ht.search(15) << endl; // Ожидаем 200

    // Тест 3: Вставка с заменой значения (если ключ уже существует)
    ht.insert_or_assign(5, 500);  // Ключ 5 уже существует, значение должно быть обновлено
    cout << "After inserting or assigning key 5 with new value:" << endl;
    cout << "Value for key 5: " << *ht.search(5) << endl;  // Ожидаем 500

    // Тест 4: Проверка наличия значения
    cout << "Contains 100: " << (ht.contains(100) ? "Yes" : "No") << endl;  // Ожидаем No
    cout << "Contains 500: " << (ht.contains(500) ? "Yes" : "No") << endl;   // Ожидаем Yes

    // Тест 5: Удаление элемента
    ht.erase(5);  // Удаление элемента с ключом 5
    cout << "After deleting key 5:" << endl;
    cout << "Count: " << ht.get_count() << endl;  // Ожидаем 1
    cout << "Value for key 5: " << (ht.search(5) ? to_string(*ht.search(5)) : "Not found") << endl;  // Ожидаем "Not found"

    // Тест 6: Повторная вставка элемента с тем же ключом
    ht.insert(5, 300);  // Вставляем снова ключ 5 с новым значением
    cout << "After reinserting key 5 with new value:" << endl;
    cout << "Count: " << ht.get_count() << endl;  // Ожидаем 2
    cout << "Value for key 5: " << *ht.search(5) << endl; // Ожидаем 300

    // Тест 7: Количество вхождений ключа
    ht.insert(5, 400);  // Вставляем элемент с ключом 5 снова (это не заменит значение)
    cout << "Count of key 5: " << ht.count(5) << endl;  // Ожидаем 2

    // Тест 8: Включение рехеширования
    ht.enable_rehashing();
    for (int i = 0; i < 100; ++i) {
        ht.insert(i, i * 10);  // Вставляем много элементов
    }
    cout << "After enabling rehashing and inserting 100 elements:" << endl;
    cout << "Count: " << ht.get_count() << endl;  // Ожидаем 102 (по сути 102 элемента)

    // Тест 9: Отключение рехеширования
    ht.disable_rehashing();
    ht.insert(101, 1010);  // Вставляем еще один элемент
    cout << "After disabling rehashing and inserting key 101:" << endl;
    cout << "Count: " << ht.get_count() << endl;  // Ожидаем 103

    // Тест 10: Проверка пустой таблицы после удаления
    ht.erase(15);  // Удаляем элемент с ключом 15
    ht.erase(5);   // Удаляем элемент с ключом 5
    cout << "After deleting keys 15 and 5:" << endl;
    cout << "Count: " << ht.get_count() << endl;  // Ожидаем 101

    // Вывод состояния таблицы
    cout << "Final state of the hash table:" << endl;
    ht.print();  // Печать всех элементов таблицы

    return 0;
}
