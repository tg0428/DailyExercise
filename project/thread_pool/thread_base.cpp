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
			printf("invoke task run method, id = %lld\n", base->get_thread_id());
			base->run();
		}
		return (0);
	}
}

