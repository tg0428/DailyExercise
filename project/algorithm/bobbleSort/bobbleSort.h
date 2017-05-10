#pragma once
#include <vector>
#include "../SortBase.h"

namespace tg
{
	using namespace std;

	class bollbeSort : public SortBase<bollbeSort>
	{
	public:
		bollbeSort();
		virtual ~bollbeSort();

	protected:
		virtual void sub_sort(vector<int>& to_sort_arr);
	protected:
		void sort_inner(vector<int>& _inner_store_arr);
	};
}