#include "trie_tree.h"

namespace tg
{
	trie_tree::trie_tree()
	{
		m_node_root = new node();

		init_child_tree(m_node_root);
	}

	trie_tree::~trie_tree()
	{
		remove_tree(m_node_root);
	}

	bool trie_tree::insert(const char * insert_content)
	{
		// ����һ�ݸ��ڵ�
		node* copy_node = m_node_root;
		// �����������ַ���
		while (*insert_content != '\0')
		{
			if (copy_node != NULL)
			{
				// �ַ����ַ����뼯��λ������������λ�ã�ascii��
				if (copy_node->next[*insert_content - 'a'] == NULL)
				{
					// �����½ڵ�
					node* new_node = new node();
					// ���½ڵ���뵽ָ�����ַ���λ��
					copy_node->next[*insert_content - 'a'] = new_node;
					// �����ڵ�ָ�������½ڵ�
					copy_node = new_node;
				}
				else
				{
					copy_node = copy_node->next[*insert_content - 'a'];
				}
				// �ƶ�ָ�룬��ָ��ָ����һ���ַ�
				insert_content++;
			}
			else
			{
				return false;
			}
		}

		copy_node->is_can_construct_cell = true;

		return true;
	}

	bool trie_tree::search(const char * search_content)
	{
		node* copy_node = m_node_root;
		while (*search_content != '\0')
		{
			if (copy_node != NULL)
			{
				if (copy_node->next[*search_content - 'a'] == NULL)
					return false;

				copy_node = copy_node->next[*search_content - 'a'];
				search_content++;
			}
			else
			{
				return false;
			}
		}
		return true;
	}

	bool trie_tree::del(const char* delete_content)
	{
		node* copy_node = m_node_root;
		while (*delete_content != '\0')
		{
			if (copy_node != NULL)
			{
				if (copy_node->next[*delete_content - 'a'] == NULL)
					return false;

				copy_node = copy_node->next[*delete_content - 'a'];
				delete_content++;
			}
			else
			{
				return false;
			}
		}

		copy_node->is_can_construct_cell = false;
		return true;
	}

	void trie_tree::remove_tree(node* root)
	{
		for (int index = 0; index < NODE_CAN_STORE_MAX_CHILDS; index++)
		{
			if (root->next[index] != NULL)
			{
				remove_tree(root->next[index]);
				printf("%s=%d=%c & ", "index", index, character[index]);
			}
		}
		if (root == m_node_root)
		{
			delete m_node_root;
			m_node_root = NULL;
		}
		else
		{
			delete root;
			root = NULL;
		}
	}

	void trie_tree::init_child_tree(node * child)
	{
		for (int index = 0; index < NODE_CAN_STORE_MAX_CHILDS; index++)
		{
			child->next[index] = NULL;
		}
	}

} // namespace tg

