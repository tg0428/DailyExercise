#include "utility.h"

namespace tg
{
	using namespace std;

	unsigned __int64 utility::getTickCount()
	{
		struct timeval tv;
		unsigned __int64 cur_tick;
		utility::gettimeofday(&tv, NULL);
		if ((&tv)->tv_usec > 1000000)
			return -1;
		else
		{
			cur_tick = (&tv)->tv_sec;
			cur_tick = cur_tick * 1000;
			cur_tick += ((&tv)->tv_usec + 999) / 1000;
			return cur_tick;
		}
	}

	int utility::gettimeofday(struct timeval * tp, void * tzp)
	{
#ifdef _WIN32
		time_t clock;
		struct tm tm;
		SYSTEMTIME wtm;
		GetLocalTime(&wtm);
		tm.tm_year = wtm.wYear - 1900;
		tm.tm_mon = wtm.wMonth - 1;
		tm.tm_mday = wtm.wDay;
		tm.tm_hour = wtm.wHour;
		tm.tm_min = wtm.wMinute;
		tm.tm_sec = wtm.wSecond;
		tm.tm_isdst = -1;
		clock = mktime(&tm);
		tp->tv_sec = clock;
		tp->tv_usec = wtm.wMilliseconds * 1000;
		return (0);
#else
		return ::gettimeofday(tp, (struct timezone*)tzp);
#endif
	}
}

