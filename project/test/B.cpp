#include "B.h"
#include "A.h"

void B::func()
{
	_a = new A();
	_a->deal_func(this);
}

void B::callback()
{
	delete _a;
	_a = NULL;
}
