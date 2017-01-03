#include "thread_worker.h"

#include <assert.h>

namespace tg
{
	thread_worker::thread_worker()
	{
	}

	void thread_worker::run()
	{
		printf("extend thread run method be invoked, id = %lld\n", get_thread_id());
		do_job();
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
			m_task->run();
		}
		get_thread_pool()->process_finished(this);
		m_task = NULL;
	}
}
