#pragma once
#include <string>
#include <map>
#include <math.h>
#include <vector>
#include <stack>

using namespace std;

namespace tg
{
	class solution
	{
	public:
		int lengthOfLongestSubstring(string s)
		{
			const char* s_char = s.c_str();
			uint16_t index = 1;
			uint16_t last_start_index = 1;
			uint16_t max_length = 0;
			while (*s_char != '\0')
			{
				if (m_input.find(*s_char) != m_input.end())
				{
					if (last_start_index <= m_input[*s_char])
					{
						last_start_index = m_input[*s_char] + 1;
					}
				}
				if (max_length < index - last_start_index + 1)
				{
					max_length = index - last_start_index + 1;
				}
				m_input[*s_char] = index;
				index++;
				s_char++;
			}
			return max_length;
		}

		string longestPalindrome(string s)
		{
			const char* s_char = s.c_str();
			uint16_t index = 1;
			uint16_t max_length = 0;
			uint16_t max_index = 1;
			uint16_t move_times = 0;
			uint16_t current_length = 0;
			while (*s_char != '\0')
			{
				if (m_input.find(*s_char) != m_input.end())
				{
					if (max_length < index - m_input[*s_char] + 1)
					{
						move_times++;
						current_length = index - m_input[*s_char] + 1;
						if (current_length / 2 == move_times || move_times == index - 1)
						{
							max_length = current_length;
							max_index = m_input[*s_char];
						}
					}
				}	
				else
				{
					m_input[*s_char] = index;
				}
				
				index++;
				s_char++;
			}

			if (max_length == 0)
				max_length = 1;
			return s.substr(max_index -1, max_length);
		}

		typedef struct node
		{
			node(char value)
			{
				this->value = value;
			}
			char value;
			node* nodes[2];
		}tree_node;

		vector<string> generateParenthesis(int n)
		{
			//½¨Ê÷
			tree_node* root = new tree_node('(');
			build_tree(root, n);
			
		}

		void build_tree(tree_node* root, int n)
		{
			tree_node* node = root;
			node->nodes[0] = new tree_node('(');
			node->nodes[1] = new tree_node(')');
			for (;n == 0;n--)
			{
				build_tree(node->nodes[0], n);
				build_tree(node->nodes[1], n);
			}
		}

		void search()
		{

		}

	private:
		map<char, uint16_t> m_input;
	};
} // namespace tg