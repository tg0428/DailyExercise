#include "bobbleSort.h"
#include "../../util/utility.h"

namespace tg
{
	bollbeSort::bollbeSort()
	{
	}

	bollbeSort::~bollbeSort()
	{
	}

	void bollbeSort::sub_sort(vector<int>& to_sort_arr)
	{
		sort_inner(to_sort_arr);
	}
	
	// O(n2)
	void bollbeSort::sort_inner(vector<int>& _inner_store_arr)
	{
		// double for
		int ret = _inner_store_arr.size();
		bool is_switch = false;

		for (int index = 0; index < ret; ++index)
		{
			for (int index_inner = 0; index_inner < ret - index; ++index_inner)
			{
				if (index_inner + 1 < ret - index && _inner_store_arr[index_inner] > _inner_store_arr[index_inner + 1])
				{
					swap(_inner_store_arr[index_inner], _inner_store_arr[index_inner+1]);
					is_switch = true;
				}
			}
			if (!is_switch)
				break;
		}
	}
}

