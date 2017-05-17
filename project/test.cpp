#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS
#define HAVE_STRUCT_TIMESPEC

#include "util/utility.h"
#include <iostream>
#include <map>

// hash
#include "algorithm/hash/hash.h"
// RB-tree
#include "algorithm/RBTree/RBTree.h"

using namespace tg;
using namespace std;

int main()
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

	// -- ¶Ô±ÈSTL hash_map
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
 	getchar();
	return 0;
}

