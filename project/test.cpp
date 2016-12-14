#define SOLUTION
#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS
//#define TRIE_TREE

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

	std::string s_new = "aaabaaaa";
	printf("%s: %s = %s\n", "longestPalindrome", "aaabaaaa", solution->longestPalindrome(s_new).c_str());

#endif // SOLUTION

	getchar();
	return 0;
}

