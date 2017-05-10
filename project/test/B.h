#pragma once
#include "stdio.h"

class A;
class B
{
public:
	~B() { printf("destruction B"); }
	void func();
	
	void callback();
	
	A * _a;
};