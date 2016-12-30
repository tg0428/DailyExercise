#pragma once
#include "pthread.h"
#include <stdint.h>

#include "thread_pool.h"

namespace tg
{
	class thread_base
	{
		friend class thread_pool;
	public:
		void create(thread_base* thread_base);
		pthread_t get_thread_id() { return m_pthread; }
		virtual ~thread_base();

		virtual void run() = 0;

		static void thread_callback(void* arg);
	private:
		thread_base();
	private:
		pthread_t m_pthread;
	};
} // namespace tg