#pragma once
#include "../common/common.h"
#include "pthread.h"
#include <stdint.h>

#include "thread_pool.h"
#include "task.h"

namespace tg
{
	class task;
	class thread_base
	{
		friend class thread_pool;
	public:
		void create();
		pthread_t get_thread_id() { return m_pthread; }
		virtual ~thread_base();

		virtual void run() = 0;
		virtual task* get_task() = 0;
		virtual void set_task(task* task) = 0;

		static void* thread_callback(void* arg);

		void set_thread_pool(thread_pool* thread_pool) { m_thread_pool = thread_pool; }
		thread_pool* get_thread_pool() { return m_thread_pool; }

	protected:
		thread_base();

	private:
		pthread_t m_pthread;		
		thread_pool* m_thread_pool;
	};
} // namespace tg