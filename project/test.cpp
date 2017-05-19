#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS
#define HAVE_STRUCT_TIMESPEC

// sys
#include <iostream>
#include <map>
#include <queue>

// uitlity
#include "util/utility.h"
// hash
#include "algorithm/hash/hash.h"
// RB-tree
#include "algorithm/search/RBTree/RBTree.h"
// heap
#include "algorithm/sort/heapSort/heapSort.h"
// priority queue
#include "algorithm/baseDataStructure/priorityQueue/priorityQueue.h"

using namespace tg;
using namespace std;

void rbTreeTest()
{
	RBTree* rbtree = new RBTree();

	srand(time(NULL));
	unsigned long startTick = utility::getTickCount();
	for (int index = 0; index < 100000; ++index)
	{
	rbtree->insertNode(index);
	}
	unsigned long duration = utility::getTickCount() - startTick;

	cout << "build rb-tree consume time(s) : " << duration / 1000 << endl;

	startTick = utility::getTickCount();
	rbtree->findNode(rand() % 100);
	duration = utility::getTickCount() - startTick;

	cout << "find ele consume time : " << duration << endl;

	cout << "size : " << rbtree->size();

	// -- 对比STL hash_map
	cout << "\n\n" << "----------------------" << endl;

	map<int, int> stlMap;
	startTick = utility::getTickCount();
	for (int index = 0; index < 100000; ++index)
	{
	stlMap.insert(std::make_pair(index, index));
	}
	duration = utility::getTickCount() - startTick;

	cout << "STL hash map build tree consume time : " << duration << endl;

	startTick = utility::getTickCount();
	stlMap.find(rand() % 100);
	duration = utility::getTickCount() - startTick;

	cout << "find ele consume time : " << duration << endl;

	cout << "size : " << stlMap.size();
}

void priorityQueueTest()
{
	struct elem
	{
		size_t key;

		bool operator < (elem& cmp) const
		{
			return (key < cmp.key);
		}

		elem(size_t value) : key(value) {}
	};

	// 生成随机序列
	srand(time(nullptr));
	vector<elem*> rand_v;
	for (int index = 0; index < 5000; ++index)
	{
		elem* ptr = new elem(rand());
		rand_v.push_back(ptr);
	}

	priority_queue<elem*> sys_pq;		// 系统实现

	priorityQueue<elem*> pq;			// TG实现

	unsigned long startTick = utility::getTickCount(), duration = 0UL;
	for (elem* ptr : rand_v)
	{
		sys_pq.push(ptr);
	}

	cout << sys_pq.top()->key << endl;
	sys_pq.pop();

	duration = utility::getTickCount() - startTick;
	cout << sys_pq.top()->key << " consume(ms) : " << duration << endl;

	cout << "\n ------------personal implements-------------- \n\n";


	startTick = utility::getTickCount();
	for (elem* ptr : rand_v)
	{
		pq.push(ptr);
	}

	cout << pq.top()->key << endl;
	pq.pop();

	duration = utility::getTickCount() - startTick;
	cout << pq.top()->key << " consume(ms) : " << duration << endl;

}

int main()
{
	priorityQueueTest();
 	getchar();
	return 0;
}

