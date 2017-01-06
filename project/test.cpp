#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS
#define HAVE_STRUCT_TIMESPEC

#include "thread_pool/thread_pool.h"
#include "thread_pool/task.h"
#include "util/utility.h"

#include <thread>

using namespace tg;

class new_task_ex : public task
{
	virtual void run()
	{
		printf("%lld", utility::getTickCount());
		printf("** des=%lld ------new task\n", 111);
		for (int i = 0; i < 5000000000; i++)
		{

		}
		printf("calc finish. \n");
	}
};

int main()
{
	thread_pool* pool = new thread_pool(3);

	new_task_ex* task_ex = new new_task_ex();
	pool->submit(task_ex);

	printf("submit finish. \n");

	getchar();
	pool->terminate_all_thread(true);

	getchar();
	return 0;
}

