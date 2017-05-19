#pragma once
#include "assert.h"
#include "stdio.h"

namespace tg
{
	static const int NODE_CAN_STORE_MAX_CHILDS = 26;
	static const char character[NODE_CAN_STORE_MAX_CHILDS] = 
	{
		'a','b','c','d','e','f','g','h','i','j','k',
		'l','m','n','o','p','q','r','s','t','u','v',
		'w','x','y','z'
	};

	class trie_tree
	{
	protected:
		struct node
		{
			~node() 
			{
				printf("%s=%d\n", "destory", sizeof(next)/sizeof(next[0]));
			}
			bool is_can_construct_cell;
			node* next[NODE_CAN_STORE_MAX_CHILDS];
		};
	public:
		trie_tree();
		~trie_tree();
	public:
		bool insert(const char* insert_content);
		bool search(const char* search_content);
		bool del(const char* delete_content);
		void remove_tree() { remove_tree(m_node_root); }
	private:
		void remove_tree(node* root);
		void init_child_tree(node* child);
	private:
		node* m_node_root;
	};
} // namespace tg
