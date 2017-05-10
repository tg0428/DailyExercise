#include "A.h"
#include "B.h"

void A::func(B * b)
{
	for (int index = 0; index < 5; ++index)
	{
		_map[index] = "hello bug";
	}
	//std::map<int, std::string>::iterator iter = _map.find(3);
	std::map<int, std::string>::iterator iter = _map.begin();
	b->callback();
	while (iter != _map.end())
	{
		printf(iter->second.c_str());
		iter++;
	}
}

void A::deal_func(void * arg)
{
	B * b = (B*)arg;
	if (b != NULL)
	{
		func(b);
	}
}

