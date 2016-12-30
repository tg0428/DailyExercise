#include "task.h"

namespace tg
{
	task::task()
	{
		m_thread_base = NULL;
	}
	task::~task()
	{
		if (m_thread_base != NULL)
		{
			delete m_thread_base;
		}
		m_thread_base = NULL;
	}
}

