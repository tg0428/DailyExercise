#include "mutex.h"

namespace tg
{
	mutex::mutex()
	{
		init();
	}

	mutex::~mutex()
	{
		pthread_mutex_destroy(&m_pthread_mutex);
	}

	bool mutex::lock()
	{
		pthread_mutex_lock(&m_pthread_mutex);
		return true;
	}

	bool mutex::unlock()
	{
		pthread_mutex_unlock(&m_pthread_mutex);
		return true;
	}

	void mutex::init()
	{
		pthread_mutex_init(&m_pthread_mutex, NULL);
	}
}
