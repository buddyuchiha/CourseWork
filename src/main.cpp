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


	for (int i = 25; i <= 475; i += 50) {
		cout << "Size: " << i << endl;
		cout << "Number of col: " << task(100, i) / 100.0 << endl;;
		cout << endl;
	}
	
}
