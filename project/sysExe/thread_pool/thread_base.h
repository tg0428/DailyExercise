#pragma once
#include "../common/common.h"
#include "pthread.h"
#include <stdint.h>

#include "thread_pool.h"
#include "task.h"

namespace tg
{
	typedef void (*FUNC_POINT)(void* args);

	class task;
	class thread_base
	{
		friend class thread_pool;
	public:
		void create(FUNC_POINT func, thread_pool * pool);
		pthread_t get_thread_id() { return m_pthread; }
		virtual ~thread_base();

		virtual void run(void* args) = 0;
		virtual void terminal() = 0;

		static void* thread_callback(void* arg);

		thread_pool* get_thread_pool() { return m_thread_pool; }

	protected:
		thread_base();
		pthread_t m_pthread;
		FUNC_POINT m_func;

	private:	
		thread_pool* m_thread_pool;
	};
} // namespace tg