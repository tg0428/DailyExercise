#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS
#define HAVE_STRUCT_TIMESPEC
//#define PTHREAD
#define SOLUTION

#ifdef TRIE_TREE
#include "trieTree/trie_tree.h"
#endif // TRIE_TREE

#ifdef DYNAMIC_ARRAY
#include "dynamic_array.h"
#endif // DYNAMIC_ARRAY

#ifdef SOLUTION
#include "solution/solution.h"
#endif

#include "stdio.h"
#include "pthread.h"
#include "process.h"
#include "util/utility.h"

using namespace tg;

int main()
{
#ifdef TRIE_TREE
	tg::trie_tree* trie_tree = new tg::trie_tree();

	char* input = "abdcdabc";
	trie_tree->insert(input);
	printf("%s: %s = %s\n", "search result", "abdcda", trie_tree->search("abdcda") == 0 ? "not exist" : "exist");

	trie_tree->remove_tree();
	printf("%s: %s = %s\n", "search result", "abdcda", trie_tree->search("abdcda") == 0 ? "not exist" : "exist");
#endif // TRIE_TREE

#ifdef DYNAMIC_ARRAY
	//TODO
#endif // DYNAMIC_ARRAY

#ifdef SOLUTION

	tg::solution* solution = new tg::solution();

	//std::string s = "abba";
	//uint16_t res = solution->lengthOfLongestSubstring(s);
	//printf("%s: %s = %d\n", "ori str's length", "abba", s.length());
	//printf("%s: %s = %d\n", "longest substring length", "abba", res);

	//std::string s_new = "aaabaaaa";
	//printf("%s: %s = %s\n", "longestPalindrome", "aaabaaaa", solution->longestPalindrome(s_new).c_str());

	//solution->generateParenthesis(3);
	unsigned __int64 tick = utility::getTickCount();
	int n = 1;
	while (n-- > 0)
	{
		/////
	}
	unsigned __int64 tick_new = utility::getTickCount();
	printf("%s=%ld", "duration", tick_new - tick);

#endif // SOLUTION

#ifdef PTHREAD
	pid_t   pid;
	pthread_t   tid;

	pid = _getpid();
	tid = pthread_self();

	printf("pid %u tid %u (0x%x)\n", (unsigned int)pid, tid, tid);
#endif // PTHREAD

	getchar();
	return 0;
}

