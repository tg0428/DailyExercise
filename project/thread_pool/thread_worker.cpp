#include "thread_worker.h"

#include <assert.h>

namespace tg
{
	thread_worker::thread_worker()
	{
	}

	void thread_worker::run()
	{
		do_job();
	}

	void thread_worker::terminal()
	{

	}

	thread_worker::~thread_worker()
	{
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
		if (m_task != NULL)
		{
			m_task->run(get_thread_id());
		}
		thread_pool* pool = get_thread_pool();
		if (pool != NULL)
		{
			pool->process_finished(this);
		}
		delete m_task;
		m_task = NULL;
	}
}
