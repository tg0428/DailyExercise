#pragma once
#include <vector>

#include "../common/Singleton.h"
#include "../util/utility.h"

namespace tg
{
	using namespace std;

	template<class Ty>
	struct Tless
	{
		bool operator()(const Ty& lhs, const Ty& rhs)
		{
			return (lhs < rhs);
		}
	};

	template<class Ty>
	struct Tgreater
	{
		bool operator()(const Ty& lhs, const Ty& rhs)
		{
			return (lhs > rhs);
		}
	};

	class SortBase
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

	protected:
		SortBase() { _start_sort_tick = utility::getTickCount(); };
		unsigned long _start_sort_tick;
	};
}