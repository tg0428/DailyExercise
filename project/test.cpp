#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS
#define HAVE_STRUCT_TIMESPEC

#include "util/utility.h"
#include <iostream>

//hash
#include "algorithm/hash/hash.h"

using namespace tg;
using namespace std;

int main()
{
	hashtable<string, string> ht_s;
	ht_s.Insert("hello", "world");
	ht_s.Insert("bucket", "hello");
	cout << ht_s.to_String().c_str() << " table size : " << ht_s.Size() << endl;

	hashtable<int, int> ht_left_value;

	srand(time(NULL));
	int choose_key = 0, value = 0;
	unsigned long start_build_tick = utility::getTickCount();
	for (int index = 0; index < 10000; ++index)
	{
		choose_key++;
		value = rand();
		ht_left_value.Insert(choose_key, value);
	}
	unsigned long duration_build = utility::getTickCount() - start_build_tick;

	cout << "build cusume time : " << duration_build << endl;

	unsigned long start_find_tick = utility::getTickCount();
	int ret = ht_left_value.Find(choose_key);
	unsigned long duration_find = utility::getTickCount() - start_find_tick;

	cout << "find : origin pair -- ["
		<< choose_key 
		<< ","
		<< value
		<< "] result : [ key :"
		<< choose_key
		<< ", " 
		<< ret 
		<< "] size :"
		<< ht_left_value.Size() << endl;
		 
	cout << " find cusume time : "
		<< duration_find
		<< endl;

 	getchar();
	return 0;
}

