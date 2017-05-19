#pragma once
#include <vector>
#include <sstream>
#include <algorithm>

namespace tg
{
	using namespace std;

template<typename T>
	struct _DefaultHashFunc
	{
		size_t operator()(T key, size_t capacity) const
		{
			// hash function .. 除留余数法
			// 利用编译器 选择相应重载函数生成hash值
			return hash(key, capacity);
		}

		size_t hash(string key, size_t capacity) const
		{
			unsigned long factor = 0;
			for (int pos = 0; pos < key.size(); ++pos)
			{
				factor = factor * 3 + key[pos];
			}
			return factor % capacity;
		}

		size_t hash(size_t key, size_t capacity) const
		{
			return key % capacity;
		}
	};

	static const int __num_primes = 28;
	static const unsigned long __prime_list[__num_primes] =
		{
			53ul, 97ul, 193ul, 389ul, 769ul,
			1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
			49157ul, 98317ul, 196613ul, 393241ul, 786433ul,
			1572869ul, 3145739ul, 6291469ul, 12582917ul, 25165843ul,
			50331653ul, 100663319ul, 201326611ul, 402653189ul, 805306457ul,
			1610612741ul, 3221225473ul, 4294967291ul
		};

template<typename K, typename V, typename HASHFUNCTION = _DefaultHashFunc<K>>
	class bucketImpl
	{
	public:
		bucketImpl() { _num_ele = 0; }
		~bucketImpl() { free_bucket(); }

		typedef struct bucketNode
		{
			K _Key;
			V _Value;
			bucketNode * _Next;
			bucketNode(const K& key, const V& value, bucketNode* node)
				: _Key(key), _Value(value), _Next(node)
			{
			}
		} Node;

	public:
		bool insert(const K& key, const V& value)
		{
			return insert_unqiue(key, value);
		}

		bool remove(const K& key)
		{
			if (_buckets_v.empty())
				return false;

			size_t pos = HASHFUNCTION()(key, _buckets_v.capacity());

			Node * node = _buckets_v[pos];
			// bak for move next pointer
			Node * node_bak = node;

			if (node == nullptr)
				return false;
		
			if (node->_Key == key)
			{
				_buckets_v[pos] = node->_Next;
				delete node;
				node = nullptr;

				--_num_ele;
				resize(_num_ele);
			}
			else
			{
				while (node)
				{
					if (node->_Key == key)
					{
						// move pointer to next
						node_bak->_Next = node->_Next;
						delete node;
						node = nullptr;

						// decrease ele num
						--_num_ele;
						resize(_num_ele);
						return true;
					}
					node_bak = node;
					node = node->_Next;
				}
			}
			
			return false;
		}

		Node * find(const K& key)
		{
			size_t pos = HASHFUNCTION()(key, _buckets_v.capacity());

			Node * node = _buckets_v[pos];

			while (node)
			{
				if (node->_Key == key)
					return node;
				node = node->_Next;
			}
			return node;
		}

		int size() { return _num_ele; }
		string to_string()
		{
			stringstream ss;
			for_each(begin(_buckets_v), end(_buckets_v), [&](const Node * node) {
				while (node)
				{
					ss << "{" << node->_Key << ", " << node->_Value << "} \r\n";
					node = node->_Next;
				}
			});
			return ss.str();
		}

		void free_bucket()
		{
			for_each(begin(_buckets_v), end(_buckets_v), [](Node * node) {
				while (node)
				{
					Node * bak = node;
					node = node->_Next;

					delete bak;
					bak = nullptr;
				}
			});
		}

	private:
		unsigned long next_size(size_t num) { return calc_prime_index(num); }
		unsigned long calc_prime_index(size_t num)
		{
			const unsigned long * first = __prime_list;
			const unsigned long * last = __prime_list + __num_primes;
			const unsigned long * index = lower_bound(first, last, num);

			return index == last ? *(last - 1) : *first;
		}

		void resize(size_t new_num)
		{
			size_t old_num = _buckets_v.size();
			if (new_num > old_num)			// make sure load_factor is less than value 1.. (load_factor = num_ele / buckets's capacity)
			{
				const unsigned long num = next_size(new_num);
				if (num > old_num)
				{
					bucketsVector tmp(num, nullptr);
					for (size_t pos = 0; pos < old_num; ++pos)
					{
						Node * node = _buckets_v[pos];
						while (node)
						{
							size_t new_bucket_pos = HASHFUNCTION()(node->_Key, new_num);
							_buckets_v[pos] = node->_Next;
							node->_Next = tmp[new_bucket_pos];
							tmp[new_bucket_pos] = node;
							node = _buckets_v[pos];
						}
					}
					_buckets_v.swap(tmp);
				}
			}
		}

		bool insert_unqiue(const K& key, const V& value)
		{
			bool ret = equal_with(key);

			if (!ret)
			{
				resize(_num_ele + 1);
				Node * node = new Node(key, value, nullptr);
				size_t pos = HASHFUNCTION()(key, _buckets_v.capacity());

				Node * head = _buckets_v[pos];
				while (head)
				{
					if (nullptr == head->_Next)
					{
						head->_Next = node;
						++_num_ele;
						return true;
					}
					head = head->_Next;
				}
				_buckets_v[pos] = node;
				++_num_ele;
				return true;
			}
			return false;
		}

		bool equal_with(const K& key)
		{
			if (!_buckets_v.empty())
			{
				size_t pos = HASHFUNCTION()(key, _buckets_v.capacity());

				Node * node = _buckets_v[pos];
				while (node)
				{
					if (node->_Key == key)
						return true;
					node = node->_Next;
				}

				return false;
			}
			else
			{
				return false;
			}
		}

	private:
		typedef vector<Node*> bucketsVector;
		bucketsVector _buckets_v;
		size_t _num_ele;
	};
	
template<typename K, typename V>
	class hashtable
	{
	public:
		hashtable() { _impl = new bucketImpl<K, V>(); }
		virtual ~hashtable() { delete _impl;_impl = nullptr; }

		inline bool		Insert(const K& key, const V& value) { return _impl->insert(key, value); }
		inline bool		Remove(const K& key)			     { return _impl->remove(key); }
		inline V		Find(const K& key) const             { return _impl->find(key)->_Value; }
		inline int		Size()								 { return _impl->size(); }
		inline string	to_String()							 { return _impl->to_string(); }

	private:
		typedef bucketImpl<K, V> _IMPL;
		_IMPL * _impl;
	};
}

//////////////////////////////////////////////////////////////////////////
/**
	note:
	对散列表查找效率的度量，用平均查找长度来衡量
	hash过程中冲突少，则比较次数少，查找效率高
	产生冲突多少取决于以下因素：
		1. 散列函数是否均匀
		2. 处理冲突方法是否合理
		3. 散列表的装填因子 (α = 填入表中的元素个数 / 散列表的长度)
		α越大，填入表中的元素较多，产生冲突的可能性就越大；α越小，填入表中的元素较少，产生冲突的可能性就越小
		散列表的平均查找长度是装填因子α的函数，只是不同处理冲突的方法有不同的函数
*/