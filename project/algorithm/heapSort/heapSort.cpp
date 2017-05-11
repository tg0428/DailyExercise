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
		if (index <= size / 2 - 1)	// indexΪ��Ҷ�ӽ��
		{
			// Ѱ���ӽڵ��еĽϴ���
			if (right_child < size && to_adjust_arr[left_child] > to_adjust_arr[right_child])
				max_node_index = left_child;

			if (right_child == size)
				max_node_index = left_child;

			if (right_child < size && to_adjust_arr[left_child] < to_adjust_arr[right_child])
				max_node_index = right_child;

			// �ϴ����뵱ǰ���ڵ�Աȣ�����ֵ�����򽻻����������ٱ�������
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
		// ��ʼ���ѣ������һ����Ҷ�ӽ�㴦���бȽϣ�ֱ������Ϊһ�������Ϊֹ
		int last_noleap_node = origin_arr.size() / 2;

		for (int index = last_noleap_node - 1; index >= 0; --index)
		{
			adjust_heap(origin_arr, index, origin_arr.size());
		}
	}
}