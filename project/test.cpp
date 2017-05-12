#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS
#define HAVE_STRUCT_TIMESPEC

#include "util/utility.h"

#include <thread>
#include <map>
#include <iterator>
#include <utility>
#include <algorithm>
#include <vector>
#include <list>
#include <iostream>

// c++ 11
#include <functional>

// sort
#include "algorithm/quickSort/quickSort.h"
#include "algorithm/bubbleSort/bubbleSort.h"
#include "algorithm/heapSort/heapSort.h"

//hash
#include "algorithm/hash/hash.h"

using namespace tg;
using namespace std;

void print_arr(const vector<int>& vector_in, const char* priefix)
{
	printf("[%s] ", priefix);
	for_each(begin(vector_in), end(vector_in), [](const int& value) {
		printf("%d.  ", value);
	});

	printf("\r\n");
}

int main()
{
	hashtable<int,int>* ht = new hashtable<int,int>();

	ht->Insert(20, 40);
	ht->Insert(21, 40);
	ht->Insert(22, 40);
	ht->Insert(23, 40);
	ht->Insert(24, 40);
	ht->Insert(25, 40);
	ht->Insert(26, 40);
	ht->Insert(27, 40);
	ht->Insert(28, 40);
	ht->Insert(29, 40);
	ht->Insert(30, 40);
	ht->Insert(31, 40);
	ht->Insert(32, 40);

	ht->Remove(32);
	ht->Remove(29);
	ht->Remove(23);
	cout << ht->to_String().c_str();
 	getchar();
	return 0;
}

