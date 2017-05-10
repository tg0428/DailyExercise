#include "thread_pool.h"
#include "thread_worker.h"

#include <assert.h>
#include <thread>

namespace tg
{
	thread_pool::thread_pool(uint32_t init_thread_num)
	{
		m_init_thread_num = init_thread_num;
		m_max_thread_num = 10;
		m_will_immediate_terminate_threads = NOT_TERMINATE;

		m_task_mutex = new mutex();

		pthread_mutex_init(&m_manage_mutex, NULL);
		pthread_cond_init(&m_manage_cond, NULL);

		init();
	}

	thread_pool::~thread_pool()
	{
		terminate_all_thread();
		pthread_mutex_destroy(&m_manage_mutex);
		pthread_cond_destroy(&m_manage_cond);
	}

	void thread_pool::terminate_all_thread(bool is_immediately/* = false*/)
	{
		m_will_immediate_terminate_threads = (thread_terminate_method)is_immediately;
		// broadcast each waiting thread not wait
		pthread_mutex_lock(&m_manage_mutex);
		pthread_cond_broadcast(&m_manage_cond);
		pthread_mutex_unlock(&m_manage_mutex);

		m_task_mutex->lock();
		while(m_thread_list.size())
		{
			delete_thread(m_thread_list.front());
		}

		while (m_task_queue.size())
		{
			delete m_task_queue.front();
			m_task_queue.pop_front();
		}
		m_task_mutex->unlock();
	}

	void thread_pool::submit(task * task)
	{
		m_task_mutex->lock();
		m_task_queue.push_back(task);
		m_task_mutex->unlock();

		pthread_mutex_lock(&m_manage_mutex);
		pthread_cond_broadcast(&m_manage_cond);
		pthread_mutex_unlock(&m_manage_mutex);
	}

	bool thread_pool::init()
	{
		int ret = 0;
		
		ret = create_idle_thread(m_init_thread_num);
		assert(ret);

		return true;
	}

	void start(void* args)
	{
		thread_pool* pool = (thread_pool*)args;
		while (true)
		{
			pool->m_task_mutex->lock();
			while (pool->m_task_queue.size() == 0 && pool->m_will_immediate_terminate_threads == NOT_TERMINATE)
			{
				pthread_mutex_lock(&pool->m_manage_mutex);
				pthread_cond_wait(&pool->m_manage_cond, &pool->m_manage_mutex);
				pthread_mutex_unlock(&pool->m_manage_mutex);
			}

			if (pool->m_will_immediate_terminate_threads == IMMEDIATE_TERMINATE
				|| (pool->m_will_immediate_terminate_threads == GENTAL_TERMINATE && pool->m_task_queue.empty()))
			{
				break;
			}

			task* task = pool->m_task_queue.front();

			pool->m_task_queue.pop_front();
			pool->m_task_mutex->unlock();

			task->run();
		}
		pool->m_task_mutex->unlock();
	}

	int thread_pool::create_idle_thread(uint32_t thread_num)
	{
		if (thread_num > m_max_thread_num)
		{
			thread_num = m_max_thread_num;
		}

		for (int count = 0; count < thread_num; ++count)
		{
			if (m_current_thread_num > m_max_thread_num)
			{
				assert(0);
				return 0;
			}

			thread_base* thread_base = new thread_worker();
			thread_base->create(start, this);
			m_thread_list.push_back(thread_base);

			m_current_thread_num++;
		}
		return thread_num;
	}

	void thread_pool::delete_thread(thread_base* thread_for_terminate)
	{
		if (thread_for_terminate)
			thread_for_terminate->terminal();

		m_thread_list.pop_front();
		delete thread_for_terminate;
		thread_for_terminate = NULL;
	}
}

