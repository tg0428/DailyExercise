#include "thread_worker.h"

#include <assert.h>

namespace tg
{
	thread_worker::thread_worker()
	{
	}

	void thread_worker::run(void* args)
	{
		if (m_func != NULL && args != NULL)
			m_func(args);
	}

	void thread_worker::terminal()
	{
		pthread_detach(m_pthread);
	}

	thread_worker::~thread_worker()
	{
		printf("destory\n");
	}
}
