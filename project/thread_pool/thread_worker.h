#pragma once
#include "../common/common.h"
#include "thread_base.h"
#include "task.h"

namespace tg
{
	class task;
	class thread_worker : protected thread_base
	{
		friend class thread_pool;
	public:
		virtual void run();
		~thread_worker();

		void set_task(task* task);
		task* get_task();
		void do_job();
		
	private:
		thread_worker();
	private:
		task* m_task;
	};
}