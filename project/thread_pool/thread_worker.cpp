#include "thread_worker.h"

#include <assert.h>

namespace tg
{
	thread_worker::thread_worker()
	{
		m_task = NULL;
	}

	void thread_worker::run()
	{
		do_job();
	}

	void thread_worker::terminal()
	{
		pthread_join(get_thread_id(), NULL);
	}

	thread_worker::~thread_worker()
	{
		printf("destory\n");
		if (m_task != NULL)
		{
			delete m_task;
			m_task = NULL;
		}
	}

	void thread_worker::set_task(task * task)
	{
		m_task = task;
	}

	task* thread_worker::get_task()
	{
		return m_task;
	}

	void thread_worker::do_job()
	{
		thread_pool* pool = get_thread_pool();
		if (m_task != NULL && pool != NULL)
		{
			m_task->run(get_thread_id());
			pool->process_finished(this);
		}

		delete m_task;
		m_task = NULL;
	}
}
