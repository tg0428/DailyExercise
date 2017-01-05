#pragma once

#include "../common/common.h"
#include <stdint.h>
#include <list>

#include "thread_base.h"
#include "mutex.h"
#include "task.h"

namespace tg
{
	class thread_worker;
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

		void terminate_all_thread(bool is_immediately = false);
		void submit(task* task);
		void process_finished(thread_base* thread_base_tg);

	protected:
		int create_idle_thread(uint32_t thread_num);
		void delete_idle_thread(thread_base* thread_for_terminate);
		void move_thread_to_busy_list(thread_base* thread_worker);
		void move_thread_to_idle_list(thread_base* thread_worker);
		thread_base* get_idle_thread();
		template<typename V> void run(task* task, void* args);

		bool init();
		void start();
		static void* thread_manager_thread_callback(void* args);

	private:
		uint32_t m_max_thread_num;
		uint32_t m_init_thread_num;
		uint32_t m_current_thread_num;

		std::list<thread_base*> m_idle_list;
		std::list<thread_base*> m_busy_list;
		std::list<task*> m_task_queue;

		mutex* m_busy_mutex;
		mutex* m_idle_mutex;
		mutex* m_task_mutex;

		pthread_t m_manage_thread;
		pthread_cond_t m_manage_cond;
		pthread_mutex_t m_manage_mutex;

		enum thread_terminate_method
		{
			IMMEDIATE_TERMINATE = 0,
			GENTAL_TERMINATE = 1,
			NOT_TERMINATE = 2
		};

		thread_terminate_method m_will_immediate_terminate_threads;

	};
}// namespace tg