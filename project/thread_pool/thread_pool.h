#pragma once

#include "../common/common.h"
#include <stdint.h>
#include <list>

#include "thread_base.h"
#include "mutex.h"
#include "task.h"

namespace tg
{
	static void start(void* args);

	enum thread_terminate_method
	{
		GENTAL_TERMINATE = 0,
		IMMEDIATE_TERMINATE = 1,
		NOT_TERMINATE = 2
	};

	class thread_worker;
	class thread_pool
	{
	public:
		thread_pool(uint32_t init_thread_num);
		~thread_pool();

		void terminate_all_thread(bool is_immediately = false);
		void submit(task* task);

	protected:
		int create_idle_thread(uint32_t thread_num);
		void delete_thread(thread_base* thread_for_terminate);

		bool init();

	public:
		std::list<task*> m_task_queue;
		mutex* m_task_mutex;

		pthread_cond_t m_manage_cond;
		pthread_mutex_t m_manage_mutex;
		
		thread_terminate_method m_will_immediate_terminate_threads;
	
	private:
		uint32_t m_max_thread_num;
		uint32_t m_init_thread_num;
		uint32_t m_current_thread_num;

		std::list<thread_base*> m_thread_list;
	};
}// namespace tg