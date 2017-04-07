#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS
#define HAVE_STRUCT_TIMESPEC

#include "thread_pool/thread_pool.h"
#include "thread_pool/task.h"
#include "util/utility.h"
#include "lru_cache/lru_cache.h"

#include <thread>
#include <map>
#include <iterator>
#include <utility>
#include <algorithm>
#include <vector>

using namespace tg;
using namespace std;

typedef struct v
{
	int _value;
	v(int value) :_value(value) {}
	void print()
	{
		printf("enter print.. value : %d\r\n", _value);
	}
}element;

int main()
{
	/*lru_cache<std::string, std::string>* lru = new lru_cache<std::string,std::string>(5);
	lru->put(std::string("111"), std::string("1111"));
	printf("%c",lru->get("111"));*/
	//uint64_t a = -1;
	//printf("%d \r\n %d \r\n %d", INT_MAX, ULLONG_MAX, a);
	//////////////////////////////////////////////////////////////////////////
	
	vector<element*> v;

	for (int index = 0; index < 5; ++index)
	{
		v.push_back(new element(index));
	}

	/*vector<element*>::iterator iter = v.begin();
	while (iter != v.end())
	{
		printf("vector size : %d\r\n", v.size());
		v.erase(iter);
		(*iter)->print();
		iter++;
	}*/

	bool flag = false;
	for (int index = 0;index < v.size();++index)
	{	
		v[index]->print();
		
		printf("vector size : %d \r\n", v.size());
		if (!flag)
		{
			flag = true;
			v.push_back(new element(666));
			v.push_back(new element(666));
			v.push_back(new element(666));
			v.push_back(new element(666));
		}
	}
	getchar();
	return 0;
}

