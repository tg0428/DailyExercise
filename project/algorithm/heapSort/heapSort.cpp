#include "heapSort.h"
#include <functional>

namespace tg
{
	heapSort::~heapSort()
	{
	}

	void heapSort::sub_sort(vector<int>& to_sort_arr)
	{
		init_heap(to_sort_arr);

		for (int index = to_sort_arr.size(); index > 0; --index)
		{
			swap(to_sort_arr[0], to_sort_arr[index - 1]);
			adjust_heap(to_sort_arr, 0, index - 1);
		}
	}

	heapSort::heapSort()
	{
	}

	void heapSort::adjust_heap(vector<int>& to_adjust_arr, int index, int size)
	{
		int first_cmp_index = 0, second_cmp_index = 0;
		if (index <= size / 2 - 1)
		{
			if (2 * index + 2 < size - 1)
			{
				first_cmp_index = _compare_Int_func(2 * index + 1, 2 * index + 2, to_adjust_arr);
			}
			else
			{
				first_cmp_index = 2 * index + 1;
			}
			second_cmp_index = _compare_Int_func(first_cmp_index, index, to_adjust_arr);

			if (second_cmp_index != index)
				swap(to_adjust_arr[second_cmp_index], to_adjust_arr[index]);
			else
				return;
		}

		if (size > 1)
		{
			adjust_heap(to_adjust_arr, second_cmp_index, size);
		}
	}

	void heapSort::init_heap(vector<int>& origin_arr)
	{
		// 初始化堆，从最后一个非叶子结点处进行比较，直到调整为一个大根堆为止
		int last_noleap_node = origin_arr.size() / 2;

		for (int index = last_noleap_node - 1; index >= 0; --index)
		{
			int first_cmp_index = 0, second_cmp_index = 0;
			if (2 * index + 2 <= origin_arr.size() - 1)
			{
				first_cmp_index = _compare_Int_func(2*index+1, 2*index+2, origin_arr);
			}
			else
			{
				first_cmp_index = 2 * index + 1;
			}
			second_cmp_index = _compare_Int_func(index, first_cmp_index, origin_arr);
			swap(origin_arr[second_cmp_index], origin_arr[index]);
		}
	}

	int heapSort::_compare_Int_func(int lhs, int mhs, int rhs, vector<int>& vec)
	{
		if (vec[lhs] > vec[mhs])
			if (vec[lhs] > vec[rhs])
				return lhs;
			else
				return rhs;
		else
			if (vec[mhs] > vec[rhs])
				return mhs;
			else
				return rhs;
	}
}