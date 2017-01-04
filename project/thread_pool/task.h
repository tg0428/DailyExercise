#pragma once
#include "thread_base.h"

namespace tg
{
	class thread_base;
	class task
	{
	public:
		virtual void run(const pthread_t thread_id) = 0;
	};
}