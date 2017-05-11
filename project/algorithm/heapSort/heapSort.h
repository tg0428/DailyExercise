#pragma once
#include <vector>
#include "../SortBase.h"

namespace tg
{
	class heapSort : public SortBase<heapSort>
	{
	public:
		heapSort();
		virtual ~heapSort();

	protected:
		virtual void sub_sort(vector<int>& to_sort_arr);
		
		void adjust_heap(vector<int>& to_adjust_arr, int index, int size);
		void init_heap(vector<int>& origin_arr);
	};
}