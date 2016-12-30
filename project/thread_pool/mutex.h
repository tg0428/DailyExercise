#pragma once
#include "pthread.h"

namespace tg
{
	class mutex
	{
	public:
		mutex();
		~mutex();
		bool lock();
		bool unlock();
	private:
		void init();
	private:
		pthread_mutex_t m_pthread_mutex;
	};
}
