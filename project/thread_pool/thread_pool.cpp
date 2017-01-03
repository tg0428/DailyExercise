#include "thread_pool.h"
#include "thread_worker.h"

namespace tg
{
	thread_pool::thread_pool(uint32_t init_thread_num)
	{
		m_init_thread_num = init_thread_num;
		m_max_thread_num = 10;

		// init mutex
		m_idle_mutex = new mutex();
		m_busy_mutex = new mutex();

		init();
	}

	thread_pool::~thread_pool()
	{
		//TODO
	}

	void thread_pool::terminate_all_thread()
	{
	}

	void thread_pool::submit(task * task)
	{
		thread_base* thread_base = get_idle_thread();

		if (thread_base != NULL)
		{
			if (task != NULL)
				thread_base->set_task(task);
				thread_base->run();
		}
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
		int ret = create_idle_thread(m_init_thread_num);
		if (ret == m_init_thread_num)
			return true;
		else
			return false;
	}

	int thread_pool::create_idle_thread(uint32_t thread_num)
	{
		if (thread_num > m_max_thread_num)
		{
			thread_num = m_max_thread_num;
		}

		for (int count = 0; count < thread_num; ++count)
		{
			thread_base* thread_base = new thread_worker();
			thread_base->create();

			// insert new thread_woker into idle_list
			m_idle_list.push_back(thread_base);
		}
		return thread_num;
	}

	void thread_pool::delete_idle_thread()
	{
	}

	void thread_pool::move_thread_to_busy_list(thread_base * thread_worker)
	{
		// move idle thread to busy list
		m_busy_mutex->lock();
		m_busy_list.push_back(thread_worker);
		m_busy_mutex->unlock();

		//erase thread in idle list
		m_idle_mutex->lock();
		std::list<tg::thread_base*>::iterator it;
		it = find(m_idle_list.begin(), m_idle_list.end(), thread_worker);
		if (it != m_idle_list.end())
		{
			m_idle_list.erase(it);
		}
		m_idle_mutex->unlock();
	}

	void thread_pool::move_thread_to_idle_list(thread_base * thread_worker)
	{
		m_idle_mutex->lock();
		m_idle_list.push_back(thread_worker);
		m_idle_mutex->unlock();

		//erase thread in busy list
		m_busy_mutex->lock();
		std::list<tg::thread_base*>::iterator it;
		it = find(m_busy_list.begin(), m_busy_list.end(), thread_worker);
		if (it != m_busy_list.end())
		{
			m_busy_list.erase(it);
		}
		m_busy_mutex->unlock();
	}

	thread_base* thread_pool::get_idle_thread()
	{
		m_idle_mutex->lock();
		thread_base* temp = NULL;
		if (m_idle_list.size() > 0)
		{
			temp = m_idle_list.front();
		}
		else
		{
			if (m_busy_list.size() < m_max_thread_num)
			{
				tg::thread_base* thread_base_tg = new tg::thread_worker();
				thread_base_tg->create();
				temp = thread_base_tg;
				m_idle_list.push_back(thread_base_tg);
			}
		}
		m_idle_mutex->unlock();
		move_thread_to_busy_list(temp);
		return temp;
	}
}

