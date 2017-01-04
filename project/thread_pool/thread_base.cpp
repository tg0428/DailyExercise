#include "thread_base.h"

#include <assert.h>

namespace tg
{
	thread_base::thread_base()
	{

	}

	thread_base::~thread_base()
	{
	}

	void thread_base::create()
	{
		int res = pthread_create(&m_pthread, NULL, thread_callback, this);
		if (res)
		{
			assert(0);
		}
	}

	void* thread_base::thread_callback(void * arg)
	{
		thread_base* base = (thread_base*)arg;
		if (base != NULL)
		{
			base->run();
		}
		return (0);
	}
}

