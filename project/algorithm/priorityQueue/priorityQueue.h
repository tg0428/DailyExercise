#pragma once

// heap sort
#include "../heapSort/heapSort.h"

namespace tg
{
template<class Ty,
	class Cmp = Tgreater<typename Ty>>
	class priorityQueue : public heapSort<Ty, Cmp>
	{
	public:
		priorityQueue() { _Container.clear(); }
		~priorityQueue() { _Container.clear(); }

		void push(const Ty& t)
		{
			_Container.push_back(t);
		}

		void pop()
		{
			init_heap(_Container);
			_Container.pop_back();
		}

		Ty& top()
		{
			init_heap(_Container);
			return _Container.back();
		}

	private:
		vector<Ty> _Container;
	};
}