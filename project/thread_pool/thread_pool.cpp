#include "thread_pool.h"

namespace tg
{
	thread_pool::thread_pool(uint32_t init_thread_num)
	{
		m_init_thread_num = init_thread_num;
	}

	thread_pool::~thread_pool()
	{
	}

	void thread_pool::terminate_all_thread()
	{
	}

	template<typename V>
	inline void thread_pool::run(task<V> * task, void * args)
	{
	}

	void thread_pool::create_idle_thread(uint32_t thread_num)
	{
	}

	void thread_pool::delete_idle_thread()
	{
	}

	void thread_pool::move_thread_to_busy_list(thread_base * thread_base)
	{
	}

	void thread_pool::move_thread_to_idle_list(thread_base * thread_base)
	{
	}

	template<typename V>
	inline future<V> thread_pool::submit(task<V>* task)
	{
		return future<V>();
	}
}

