#pragma once
#include "thread_base.h"
#include "task.h"

namespace tg
{
	class thread_base;
	class task;
	class thread_worker : public thread_base
	{
		friend class thread_pool;
	public:
		virtual void run();
		~thread_worker();

	private:
		thread_worker();

		void set_task(task* insert_task, void* task_datas);
		void get_task(task* want_task);

		void set_thread_pool(thread_pool* thread_pool) { m_thread_pool = thread_pool; }
		thread_pool* get_thread_pool() { return m_thread_pool; }

	private:
		task* m_task;
		void* m_task_data;
		thread_pool* m_thread_pool;

	};
}