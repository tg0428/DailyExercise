#pragma once
#include <stdint.h>
#include <list>

#include "thread_base.h"
#include "task.h"

namespace tg
{
	class thread_base;
	template<typename T> struct future
	{
		future(T& t)
		{
			m_future_t = t;
		}
		T* get() { return m_future_t; }
		T* m_future_t;
	};

	class thread_pool
	{
	public:
		thread_pool(uint32_t init_thread_num);
		~thread_pool();

		void terminate_all_thread();
		template<typename V> future<V> submit(task<V>* task);

	protected:
		void create_idle_thread(uint32_t thread_num);
		void delete_idle_thread();
		void move_thread_to_busy_list(thread_base* thread_base);
		void move_thread_to_idle_list(thread_base* thread_base);
		template<typename V> void run(task<V>* task, void* args);

	private:
		uint32_t m_max_thread_num;
		uint32_t m_init_thread_num;
		std::list<thread_base*> m_idle_list;
		std::list<thread_base*> m_busy_list;
	};
}// namespace tg