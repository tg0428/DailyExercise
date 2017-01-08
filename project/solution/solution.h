#pragma once
#include <string>
#include <map>
#include <math.h>
#include <vector>
#include <stack>
#include <assert.h>

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
			bool flag = true;
			while (*s_char != '\0')
			{
				m_input_new[index] = *s_char;
				if (m_input.find(*s_char) != m_input.end())
				{
					for (uint32_t i = index - 1; i >= ((index + m_input[*s_char]) / 2 + 1); --i) {
						if ((index - m_input[*s_char] + 1) % 2 != 0) {
							if (i == (index + m_input[*s_char]) / 2)
								break;
							flag = flag && (m_input_new[index + m_input[*s_char] - i] == m_input_new[i]);
						}
						else {
							flag = flag && (m_input_new[index + m_input[*s_char] - i] == m_input_new[i]);
						}
						if (!flag) {
							break;
						}
					}
				}
				else {
					m_input[*s_char] = index;
					flag = false;
				}
				if (flag &&  index != 1) {
					if (max_length < index - m_input[*s_char] + 1)
					{
						max_length = index - m_input[*s_char] + 1;
						max_index = m_input[*s_char];
					}
				}
				
				index++;
				s_char++;
				flag = true;
			}
			if (index == 2)
				return s;
			if (max_length == 0)
				return s.substr(0, 1);
			return s.substr(max_index -1, max_length);
		}

		bool isPalindrome(int x) {
			if (x < 0)
				return false;
			uint32_t result = 0;
			uint32_t temp = x;
			while (temp) {
				result = temp % 10 + result * 10;
				temp = temp / 10;
			}
			return result == x;
		}

		typedef struct tree_node {
			tree_node(char value) {
				m_value = value;
			}
			char m_value;
			tree_node* left_child = NULL;
			tree_node* right_child = NULL;
		}tree_node;

		vector<string> generateParenthesis(int n) {
			tree_node* root = new tree_node('(');
			std::stack<char> stack;
			std::vector<string> vec;
			std::string temp = "(";
			build_tree(root, n * 2 - 1);
			search_result(root, stack, temp, n * 2 - 1);

			vec.push_back(temp);
			return vec;
		}

		void build_tree(tree_node* root, int n) {
			assert(root);
			root->left_child = new tree_node('(');
			root->right_child = new tree_node('(');
			for (; n > 1; --n) {
				build_tree(root->left_child, n);
				build_tree(root->right_child, n);
			}
		}

		void search_result(tree_node* root, std::stack<char>& result, std::string temp, int n) {
			if (result.top() - root->m_value) {
				temp.append(")");
				result.pop();
			}
			else {
				if (n > 0) {
					result.push(root->m_value);
					n--;
				}
			}
			search_result(root->left_child, result, temp, n);
			search_result(root->right_child, result, temp, n);
		}

	private:
		map<char, uint16_t> m_input;
		map<uint16_t, char> m_input_new;
	};
} // namespace tg