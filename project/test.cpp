#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS
#define HAVE_STRUCT_TIMESPEC

#include "thread_pool/thread_pool.h"
#include "thread_pool/task.h"

using namespace tg;
class new_task : public task
{
	virtual void run()
	{
		printf("------new task\n");
	}
};

int main()
{
	thread_pool* pool = new thread_pool(3);
	new_task* task = new new_task();
	pool->submit(task);

	new_task* task_another = new new_task();
	pool->submit(task_another);

	getchar();
	return 0;
}

