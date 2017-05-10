#include "quickSort.h"

namespace tg
{
	quickSort::quickSort():_pivotkey(0)
	{
	}

	quickSort::~quickSort()
	{
	}

	void quickSort::sub_sort(vector<int>& to_sort_arr)
	{
		// O(nlogn)
		sort(to_sort_arr, 0, to_sort_arr.size() - 1);
	}

	// O(n)
	int quickSort::Partition(vector<int>& partition_arr, int low, int high)
	{
		// record pivotkey
		_pivotkey = partition_arr[low];

		// partition
		while (low < high)
		{
			while (low < high && partition_arr[high] >= _pivotkey) --high;
			if (low < high)
				swap(partition_arr[low], partition_arr[high]);

			while (low < high && partition_arr[low] <= _pivotkey) ++low;
			if (low < high)
				swap(partition_arr[high], partition_arr[low]);
		}

		return low;
	}

	void quickSort::sort(vector<int>& partition_arr, int low, int high)
	{
		if (low < high)
		{
			int index = Partition(partition_arr, low, high);
			// quick sort left part
			sort(partition_arr, low, index - 1);
			// quick sort right part
			sort(partition_arr, index + 1, high);
		}
	}
}