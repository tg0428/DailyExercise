#pragma once
#include "../common/common.h"
#include "thread_base.h"
#include "task.h"

namespace tg
{
	class task;
	class thread_worker : protected thread_base
	{
		friend class thread_pool;
	public:
		virtual void run(void* args);
		virtual void terminal();
		~thread_worker();

	private:
		thread_worker();
	};
}