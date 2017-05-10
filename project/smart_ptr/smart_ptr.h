#pragma once
#include "stdio.h"

namespace tg
{
	class element
	{
	public:
		explicit element(int value) :_value(value)
		{
			//..
		}
		~element()
		{
			printf("invoke element destruction.. value [%d]\r\n", _value);
		}
		int _value;
		//smart_ptr<element> _ptr;
	};

	template<class T>
	class calc_ptr
	{
		template<class T>
		friend class smart_ptr;
	private:
		explicit calc_ptr(T* p = 0)
			:_ptr(p),_use(1) {}
		~calc_ptr(void)
		{
			printf("# invoke calc ptr destruction.. current use calc [%d]\r\n", _use);
			if (_ptr != NULL)
			{
				delete _ptr;
				_ptr = NULL;
			}
		}
	private:
		T * _ptr;
		size_t _use;
	};

	template<class T>
	class smart_ptr
	{
	public:
		explicit smart_ptr(T* ptr = 0)
			:_ptr(new calc_ptr<T>(ptr))
		{
			printf("instance build.. ptr val [%d] ptr use :[%d]\r\n", _ptr->_ptr, _ptr->_use);
		}

		~smart_ptr()
		{
			printf("invoke smart pointer instance destroy.. \r\n");
			release();
		}

		// øΩ±¥ππ‘Ï
		smart_ptr(const smart_ptr<T>& sp)
			:_ptr(sp._ptr)
		{
			++_ptr->_use;
		}

		smart_ptr<T>& operator = (const smart_ptr<T>& rhs)
		{
			++rhs._ptr->_use;
			release();
			_ptr = rhs._ptr;
			return *this;
		}

		void reset(T* ptr)
		{
			if (ptr != nullptr)
			{
				release();
				_ptr = new calc_ptr<T>(ptr);
				return;
			}
		}
		void reset()
		{
			release();
		}

		T& operator * () const
		{
			return *_ptr->_ptr
		}

		T* operator -> () const
		{
			return _ptr->_ptr;
		}

		T* get()
		{
			return _ptr->_ptr;
		}

	private:
		void release()
		{
			if (_ptr != nullptr)
			{
				printf("decrease use reference .. use :[%d] reference : [%d]\r\n", _ptr->_use, _ptr->_ptr);
				if (--_ptr->_use == 0)
				{
					delete _ptr;
					_ptr = NULL;
				}
			}
		}

	private:
		calc_ptr<T> * _ptr;
	};
}