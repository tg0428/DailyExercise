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
	// use rand num to init a disorder vector
	srand((unsigned)time(NULL));
	vector<int> disorder_vector;

	for (int index = 0; index < 30; ++index)
	{
		disorder_vector.push_back(rand());
	}

	// declare a Sort Object
	SortBase<heapSort>* object_4_hs = SortBase<heapSort>::create_instance();

	// use sort algorithm to sort arr
	object_4_hs->Sort(disorder_vector);

	print_arr(disorder_vector, "ÅÅÐòºó");

	printf("ºÄÊ± -- %d ms", object_4_hs->cusume_time());

 	getchar();
	return 0;
}

