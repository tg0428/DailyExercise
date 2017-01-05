#include "thread_pool.h"
#include "thread_worker.h"

#include <assert.h>

namespace tg
{
	thread_pool::thread_pool(uint32_t init_thread_num)
	{
		m_init_thread_num = init_thread_num;
		m_max_thread_num = 10;
		m_will_immediate_terminate_threads = NOT_TERMINATE;

		m_idle_mutex = new mutex();
		m_busy_mutex = new mutex();
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

		delete m_idle_mutex;
		delete m_busy_mutex;

		m_idle_mutex = NULL;
		m_busy_mutex = NULL;
	}

	void thread_pool::terminate_all_thread(bool is_immediately/* = false*/)
	{
		m_will_immediate_terminate_threads = (thread_terminate_method)!is_immediately;

		pthread_mutex_lock(&m_manage_mutex);
		pthread_cond_wait(&m_manage_cond, &m_manage_mutex);
		pthread_mutex_unlock(&m_manage_mutex);

		m_idle_mutex->lock();
		m_busy_mutex->unlock();
		while(m_idle_list.size())
		{
			delete_idle_thread(m_idle_list.front());
		}
		m_idle_list.clear();
		m_busy_list.clear();

		m_idle_mutex->unlock();
		m_busy_mutex->unlock();
	}

	void thread_pool::submit(task * task)
	{
		m_task_mutex->lock();
		m_task_queue.push_back(task);
		m_task_mutex->unlock();
	}

	void thread_pool::process_finished(thread_base * thread_base_tg)
	{
		if (thread_base_tg != NULL)
		{
			move_thread_to_idle_list(thread_base_tg);
		}
	}

	bool thread_pool::init()
	{
		int ret = 0;
		
		ret = create_idle_thread(m_init_thread_num);
		assert(ret);

		ret = pthread_create(&m_manage_thread, NULL, thread_manager_thread_callback, this);
		assert(!ret);

		return true;
	}

	void thread_pool::start()
	{
		while (true)
		{
			if (m_will_immediate_terminate_threads == GENTAL_TERMINATE)
			{
				m_busy_mutex->lock();
				if (m_busy_list.size() > 0)
				{
					m_busy_mutex->unlock();
					continue;
				}
				m_busy_mutex->unlock();
				break;
			}
			else if (m_will_immediate_terminate_threads == IMMEDIATE_TERMINATE)
			{
				break;
			}

			m_idle_mutex->lock();
			if (m_idle_list.size() == 0)
			{
				m_idle_mutex->unlock();
				continue;
			}
			m_idle_mutex->unlock();

			m_task_mutex->lock();
			if (m_task_queue.size() > 0)
			{
				thread_base* thread_base = get_idle_thread();

				if (thread_base != NULL)
				{
					task* task = m_task_queue.front();
					if (task != NULL)
					{
						thread_base->set_task(task);
						thread_base->run();
					}
					m_task_queue.pop_front();
				}
			}
			m_task_mutex->unlock();
		}

		pthread_mutex_lock(&m_manage_mutex);
		pthread_cond_signal(&m_manage_cond);
		pthread_mutex_unlock(&m_manage_mutex);
	}

	void * thread_pool::thread_manager_thread_callback(void * args)
	{
		thread_pool* pool = (thread_pool*)args;
		if (pool != NULL)
		{
			pool->start();
		}
		return (0);
	}

	int thread_pool::create_idle_thread(uint32_t thread_num)
	{
		if (thread_num > m_max_thread_num)
		{
			thread_num = m_max_thread_num;
		}

		for (int count = 0; count < thread_num; ++count)
		{
			m_idle_mutex->lock();
			if (m_current_thread_num > m_max_thread_num)
			{
				assert(0);
				return 0;
			}

			thread_base* thread_base = new thread_worker();
			thread_base->create();
			thread_base->set_thread_pool(this);

			m_idle_list.push_back(thread_base);
			m_current_thread_num++;
			m_idle_mutex->unlock();
		}
		return thread_num;
	}

	void thread_pool::delete_idle_thread(thread_base* thread_for_terminate)
	{
		thread_for_terminate = m_idle_list.front();
		if (thread_for_terminate)
			thread_for_terminate->terminal();

		m_idle_list.pop_front();
		delete thread_for_terminate;
		thread_for_terminate = NULL;
	}

	void thread_pool::move_thread_to_busy_list(thread_base * thread_worker)
	{
		assert(m_idle_mutex || m_busy_mutex);
		
		m_busy_mutex->lock();
		m_busy_list.push_back(thread_worker);
		m_busy_mutex->unlock();

		m_idle_mutex->lock();
		if (m_idle_list.size() > 0)
			m_idle_list.pop_front();
		m_idle_mutex->unlock();
	}

	void thread_pool::move_thread_to_idle_list(thread_base * thread_worker)
	{
		assert(m_idle_mutex || m_busy_mutex);

		m_idle_mutex->lock();
		m_idle_list.push_back(thread_worker);
		m_idle_mutex->unlock();

		m_busy_mutex->lock();
		if (m_busy_list.size()>0)
			m_busy_list.pop_front();
		m_busy_mutex->unlock();
	}

	thread_base* thread_pool::get_idle_thread()
	{
		m_idle_mutex->lock();
		thread_base* temp = NULL;
		if (m_current_thread_num > 0 && m_idle_list.size() > 0)
		{
			temp = m_idle_list.front();
		}
		else if (m_current_thread_num < m_max_thread_num && m_idle_list.size() == 0)
		{
			m_idle_mutex->unlock();
			create_idle_thread(1);
			m_idle_mutex->lock();
			temp = m_idle_list.front();
		}
		else
		{
			return NULL;
		}

		m_idle_mutex->unlock();
		move_thread_to_busy_list(temp);
		return temp;
	}
}

