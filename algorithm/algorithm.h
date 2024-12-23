#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include<random>

using namespace std;


namespace algorithm {
	template <typename K, typename T>
	class HashTable {
	private:
		template <typename K, typename T>
		struct HashPair {
			K _key;
			T _value;
			HashPair* _next;
			bool _filled;
			HashPair(K key, T value) : _key(key), _value(value), _filled(true), _next(nullptr) {}
			HashPair() : _key(K()), _value(T()), _filled(false), _next(nullptr) {}
		};
		vector<HashPair<K, T>> _data;
		int _count = 0;
		size_t _size;
		size_t hash_function(K key) {
			size_t a = 2654435761;
			size_t w = sizeof(int) * 8;
			size_t l = log2(_data.size());
			size_t result = ((key * a) % static_cast<size_t>(pow(2, w))) >> (w - l);
			return result;
		}
		int random(int a, int b) {
			random_device random_device;
			mt19937 generator(random_device());
			uniform_int_distribution<> distribution(a, b);
			return distribution(generator);
		}
	public:
		HashTable(int size);
		~HashTable();
		HashTable(const HashTable& other);
		HashTable(int size, int min_key, int max_key, int min_value, int max_value);
		void print();
		void insert(K key, T value);
		void insert_or_assign(K key, T value);
		bool contains(T value);
		T* search(K key);
		bool erase(K key);
		int count(K key);
		HashTable<K, T>& operator=(const HashTable<K, T>& other);
		int get_count();
		int get_size();
	};

	template<typename K, typename T>
	HashTable<K, T>::HashTable(int size) : _size(size)
	{
		_data.resize(_size);
	}

	template<typename K, typename T>
	HashTable<K, T>::~HashTable() {
		for (size_t i = 0; i < _size; ++i) {
			HashPair<K, T>* current = _data[i]._next;
			while (current) {
				HashPair<K, T>* to_delete = current;
				current = current->_next;
				delete to_delete;
			}
			_data[i]._next = nullptr;
		}
	}


	template<typename K, typename T>
	HashTable<K, T>::HashTable(const HashTable& other) : _size(other._size), _count(other._count) {
		_data.resize(_size);
		for (size_t i = 0; i < _size; ++i) {
			HashPair<K, T>* current = other._data[i]._next;
			while (current) {
				insert(current->_key, current->_value);
				current = current->_next;
			}
		}
	}

	template<typename K, typename T>
	HashTable<K, T>::HashTable(int size, int min_key, int max_key, int min_value, int max_value) : _size(size)
	{
		_data.resize(_size);
		for (int i = 0; i < 25; ++i) {
			K key = random(min_key, max_key);
			T value = random(min_value, max_value);
			insert(key, value);
		}
	}
	template<typename K, typename T>
	void HashTable<K, T>::print()
	{
		for (int i = 0; i < _data.size(); i++) {
			cout << "Bucket: " << i << endl;
			HashPair<K, T>* temp = &_data[i];
			while (temp) {
				cout << "{" << "Key: " << temp->_key << " Value: " << temp->_value << "}" << endl;
				temp = temp->_next;
			}
			cout << endl;
		}
	}

	template<typename K, typename T>
	void HashTable<K, T>::insert(K key, T value)
	{
		size_t index = hash_function(key);
		HashPair<K, T>* temp = &_data[index];
		if (temp->_filled) {
			while (temp->_next) {
				temp = temp->_next;
			}
			temp->_next = new HashPair<K, T>(key, value);
			temp->_next->_filled = true;
		}
		else {
			_data[index] = HashPair<K, T>(key, value);
			_data[index]._filled = true;
		}

	}

	template<typename K, typename T>
	void HashTable<K, T>::insert_or_assign(K key, T value) {
		size_t index = hash_function(key);
		HashPair<K, T>* temp = &_data[index];
		while (temp) {
			if (temp->_key == key) {
				temp->_value = value;
				return;
			}
			temp = temp->_next;
		}
		insert(key, value);
	}


	template<typename K, typename T>
	bool HashTable<K, T>::contains(T value) {
		for (auto& pair : _data) {
			HashPair<K, T>* temp = &pair;
			while (temp) {
				if (temp->_value == value) {
					return true;
				}
				temp = temp->_next;
			}
		}
		return false;
	}

	template<typename K, typename T>
	T* HashTable<K, T>::search(K key)
	{
		size_t index = hash_function(key);
		if (!_data[index]._filled) {
			return nullptr;
		}
		else {
			HashPair<K, T>* temp = &_data[index];
			while (temp) {
				if (temp->_key == key) {
					return &temp->_value;
				}
				temp = temp->_next;
			}
			return nullptr;
		}
	}

	template<typename K, typename T>
	bool HashTable<K, T>::erase(K key) {
		size_t index = hash_function(key);
		HashPair<K, T>* current = &_data[index];
		HashPair<K, T>* prev = nullptr;

		while (current) {
			if (current->_key == key) {
				if (prev) {
					prev->_next = current->_next;
					delete current;  
				}
				else {
					if (current->_next) {
						HashPair<K, T>* next = current->_next;
						_data[index] = *next;
						delete next;
					}
					else {
						_data[index] = HashPair<K, T>();
					}
					delete current;

				}
				return true;
			}
			prev = current;
			current = current->_next;
		}
		return false;  
	}


	template<typename K, typename T>
	int HashTable<K, T>::count(K key) {
		size_t index = hash_function(key);
		int count = 0;
		HashPair<K, T>* current = &_data[index];
		while (current) {
			count++;
			current = current->_next;
		}
		return count;
	}

	template<typename K, typename T>
	HashTable<K, T>& HashTable<K, T>::operator=(const HashTable<K, T>& other) {
		if (this == &other) {
			return *this;
		}

		for (size_t i = 0; i < _size; ++i) {
			HashPair<K, T>* current = _data[i]._next;
			while (current) {
				HashPair<K, T>* to_delete = current;
				current = current->_next;
				delete to_delete;
			}
			_data[i]._next = nullptr;
		}

		_size = other._size;
		_count = other._count;
		_data.resize(_size);

		for (size_t i = 0; i < _size; ++i) {
			HashPair<K, T>* current = other._data[i]._next;
			while (current) {
				insert(current->_key, current->_value);
				current = current->_next;
			}
		}

		return *this;
	}

	template<typename K, typename T>
	int HashTable<K, T>::get_count() {
		int count_ = 0;
		for (const auto& pair : _data) {
			if (pair._filled) {
				count_ += count(pair._key) - 1;
			}
		}
		return count_;
	}

	template<typename K, typename T>
	int HashTable<K, T>::get_size()
	{
		return _data.size();
	}
}