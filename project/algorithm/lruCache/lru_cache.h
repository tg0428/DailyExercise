#pragma once

#include <vector>
#include <hash_map>

namespace tg
{
	template <class K, class V>
	class lru_cache
	{
	protected:
		struct node
		{
			K key;
			V value;
			node* prev;
			node* next;
		};
		std::vector<node*> m_addr_manager;
		std::hash_map<K, node*> m_hash;
		node* m_head;
		node* m_tail;
		node* m_entity;

	public:
		lru_cache(uint16_t max_size)
		{
			m_entity = new node[max_size];
			while (max_size-- > 0)
			{
				m_addr_manager.push_back(m_entity + max_size);
			}
			m_head = new node();
			m_tail = new node();
			m_head->next = m_tail;
			m_tail->prev = m_head;
			m_head->prev = NULL;
			m_tail->next = NULL;
		}
		~lru_cache()
		{
			delete m_head;
			delete m_head;
			delete []m_entity;

			m_tail = NULL;
			m_head = NULL;
			m_entity = NULL;
		}
		V get(const K& key)
		{
			node* node = m_hash[key];
			if (node != NULL)
			{
				detach_node(node);
				attach_node(node);
				return node->value;
			}
			else
			{
				return V();
			}
		}
		void put(K& key, V& value)
		{
			node* node = m_hash[key];
			if (node != NULL)
			{
				detach_node(node);
				attach_node(node);
				node->value = value;
			}
			else
			{
				if (m_addr_manager.empty())
				{
					node = m_tail->prev;
					detach_node(node);
					m_hash.erase(node->key);
				}
				else
				{
					node = m_addr_manager.back();
					m_addr_manager.pop_back();
				}
				node->key = key;
				node->value = value;
				m_hash[key] = node;
				attach_node(node);
			}
		}
	protected:
		void detach_node(node* node)
		{
			node->prev->next = node->next;
			node->next->prev = node->prev;
		}
		void attach_node(node* node)
		{
			node->prev = m_head;
			node->next = m_head->next;
			m_head->next->prev = node;
			m_head->next = node;
		}
	};
}