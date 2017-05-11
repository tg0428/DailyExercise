#pragma once
#include <vector>

#include "../common/Singleton.h"
#include "../util/utility.h"

namespace tg
{
	using namespace std;

	template<class T>
	class SortBase : public Singleton<T>
	{
	public:
		virtual ~SortBase() {};
		virtual unsigned long cusume_time() 
		{
			if (_start_sort_tick != 0)
			{
				return utility::getTickCount() - _start_sort_tick;
			}
			return 0;
		};

		void Sort(vector<int>& to_sort_arr)
		{
			bool ret = to_sort_arr.empty();
			if (!ret)
			{
				sub_sort(to_sort_arr);
			}
		}
		
	protected:
		virtual void sub_sort(vector<int>& to_sort_arr) = 0;
		SortBase() { _start_sort_tick = utility::getTickCount(); };
		unsigned long _start_sort_tick;
	};
}