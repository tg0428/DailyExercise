#pragma once
#include <vector>

#include "../../util/utility.h"
#include "../SortBase.h"

namespace tg
{
	using namespace std;
	class quickSort : public SortBase
	{
	public:
		quickSort();
		virtual ~quickSort();

		virtual void sub_sort(vector<int>& to_sort_arr);

	protected:
		int Partition(vector<int>& partition_arr, int low, int high);
		void sort(vector<int>& partition_arr, int low, int high);

	private:
		int _pivotkey;
		unsigned long _start_sort_tick;
	};
}