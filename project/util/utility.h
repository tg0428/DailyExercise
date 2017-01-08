#pragma once
#include <time.h>
#ifdef _WIN32
#include <windows.h>
#endif

namespace tg
{
	class utility
	{
	public:
		static unsigned __int64 getTickCount();
		static int gettimeofday(struct timeval *tp, void *tzp);
	};
}