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
		size_t left_child = 2 * index + 1, right_child = 2 * index + 2, max_node_index = 0;
		if (index <= size / 2 - 1)	// index为非叶子结点
		{
			// 寻找子节点中的较大者
			if (right_child < size && to_adjust_arr[left_child] > to_adjust_arr[right_child])
				max_node_index = left_child;

			if (right_child == size)
				max_node_index = left_child;

			if (right_child < size && to_adjust_arr[left_child] < to_adjust_arr[right_child])
				max_node_index = right_child;

			// 较大者与当前根节点对比，交换值，无序交换，则无需再遍历子树
			if (to_adjust_arr[max_node_index] > to_adjust_arr[index])
				swap(to_adjust_arr[index], to_adjust_arr[max_node_index]);
			else
				return;
		}

		if (size > 1)
		{
			adjust_heap(to_adjust_arr, max_node_index, size);
		}
	}

	void heapSort::init_heap(vector<int>& origin_arr)
	{
		// 初始化堆，从最后一个非叶子结点处进行比较，直到调整为一个大根堆为止
		int last_noleap_node = origin_arr.size() / 2;

		for (int index = last_noleap_node - 1; index >= 0; --index)
		{
			adjust_heap(origin_arr, index, origin_arr.size());
		}
	}
}