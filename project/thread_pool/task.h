#pragma once
#include "thread_base.h"

namespace tg
{
	class thread_base;
	class task
	{
	public:
		virtual void run() = 0;
	};
}