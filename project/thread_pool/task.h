#pragma once
#include "thread_base.h"
#include "thread_pool.h"

namespace tg
{
	class thread_base;
	template<typename T> class task
	{
		friend class thread_pool;
	public:
		task();
		~task();
	private:
		thread_base* get_work_thread() { return m_thread_base; };
		void set_work_thread(thread_base* work_thread) {m_thread_base = work_thread};
		virtual void run() = 0;
	private:
		thread_base* m_thread_base;
	};
}