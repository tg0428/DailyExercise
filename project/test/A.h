#pragma once
#include "stdio.h"
#include <map>

using namespace std;

class B;
class A
{
public:
	A() {}
	~A() { printf("destruction"); }

	void deal_func(void* arg);

	map<int, string> _map;

private:
	void func(B * b);
};