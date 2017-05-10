#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS
#define HAVE_STRUCT_TIMESPEC

#include "util/utility.h"
//#include "smart_ptr/smart_ptr.h"

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
#include "algorithm/bobbleSort/bobbleSort.h"
#include "algorithm/heapSort/heapSort.h"

using namespace tg;
using namespace std;

// c++ 11
void cplusplus11_func(std::function<void(const string&)> func)
{
	if (func)
	{
		func("hello lambda");
	}
}

// c++ 11 set callback handler
class EmailProcesser
{
public:
	void recieveMsg(const string& msg)
	{
		if (_handle_func)
		{
			_handle_func(msg);
		}
	}

	void registeMsgCallback(std::function<void(const string&)> func)
	{
		if (func)
		{
			_handle_func = func;
		}
	}

private:
	std::function<void(const string&)> _handle_func;
};

class MessageSizeStroe
{
public:
	MessageSizeStroe():_max_size(0){}
	void checkMsgSize(const string& msg)
	{
		auto size = msg.length();
		if (size > _max_size)
		{
			_max_size = size;
		}
	}

	int getMsgMaxSize()
	{
		return _max_size;
	}

private:
	size_t _max_size;
};

// c++ 11 prefect forward
template<typename T>
void WrapperFunc(T && t)
{
	//auto origin_value = std::forward<T &&>(t);

	cout << std::boolalpha;
	cout << "is reference : " << std::is_reference<T>::value << endl;
	cout << "is rvalue referenece : " << std::is_rvalue_reference<T&&>::value << endl;
	cout << "is lvalue referenece : " << std::is_lvalue_reference<T&&>::value << endl;
}

typedef struct element
{
	element() 
	{
		cout << "construction.." << endl;
	}
	~element()
	{
		cout << "destruction.." << endl;
	}
}e;

// c++ 11 return rvalue
element get_value(){
	return element();
}

void process(shared_ptr<int> args_ptr)
{
	cout << "use count: " << args_ptr.use_count() << endl;
}

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
	vector<int> disorder_vector{5,2,3,10,8,55,1,99,6,120};

	/*for (int index = 0; index < 15; ++index)
	{
		disorder_vector.push_back(rand());
	}*/

	// declare a Sort Object
	//SortBase<quickSort> * object_4_qs = SortBase<quickSort>::create_instance();
	//SortBase<bollbeSort>* object_4_bs = SortBase<bollbeSort>::create_instance();
	SortBase<heapSort>* object_4_hs = SortBase<heapSort>::create_instance();

	// use quick sort algorithm to sort arr
	//object_4_qs->sort(disorder_vector);
	//object_4_bs->Sort(disorder_vector);
	object_4_hs->Sort(disorder_vector);

	print_arr(disorder_vector, "ÅÅÐòºó");

	printf("ºÄÊ± -- %d ms", object_4_hs->cusume_time());

 	getchar();
	return 0;
}

