#include "dynamic_array.h"
namespace tg
{
	template<typename T>
	inline dynamic_array<T>::dynamic_array()
	{
		m_size = 0;
		m_capacity = 1;
		m_enlarge_factor = 0.5;
		m_reduce_factor = 0.25;
	}

	template<typename T>
	inline dynamic_array<T>::~dynamic_array()
	{
		safe_delete_array(m_inner_array);

		delete m_inner_array;
	}

	template<typename T>
	inline __int32 dynamic_array<T>::size()
	{
		return m_size;
	}

	template<typename T>
	inline __int32 dynamic_array<T>::capacity()
	{
		return m_capacity;
	}

	template<typename T>
	inline __int32 dynamic_array<T>::push(T & value)
	{
		if (m_size + 1 > m_capacity)
		{
			__int32 size = get_after_enlarge_size();
			resize(size);
		}
		m_inner_array[m_size++] = value;
		return 0;
	}

	template<typename T>
	__int32 dynamic_array<T>::remove(T & value)
	{
		__int32 value_position = find(value);
		erase(value_position);
		
		return value_position;
	}

	template<typename T>
	inline __int32 dynamic_array<T>::insert(__int32 index, T & value)
	{
		// TODO
		return 0;
	}

	template<typename T>
	inline bool dynamic_array<T>::is_empty()
	{
		return m_size > 0 ? false : true;
	}

	template<typename T>
	inline T * dynamic_array<T>::at(__int32 index)
	{
		return m_inner_array[index];
	}

	template<typename T>
	inline void dynamic_array<T>::pop()
	{
		m_inner_array[m_size] = NULL;
		m_size--;

		if (m_size < m_capacity * m_reduce_factor)
		{
			__int32 size = get_after_reduce_size();
			resize(size);
		}

		return true;
	}

	template<typename T>
	void dynamic_array<T>::erase(__int32 index)
	{
		m_inner_array[index] = NULL;
		copy(index + 1, m_size, index, m_inner_array, m_inner_array);

		m_size--;
		if (m_size < m_capacity * m_reduce_factor)
		{
			__int32 size = get_after_reduce_size();
			resize(size);
		}
	}

	template<typename T>
	__int32 dynamic_array<T>::find(T & value)
	{
		for (int index = 0; index < m_size; index++)
		{
			if (m_inner_array[index] == value)
			{
				return index;
			}
		}

		return -1;
	}

	template<typename T>
	bool dynamic_array<T>::resize(__int32 size)
	{
		m_capacity = size;
		// create a new array 
		T* new_array[size];
		// copy the current array to new array
		copy(0, m_size, 0, size,  m_inner_array, new_array);
		// safe delete the current array
		safe_delete_array(m_inner_array);
		// move pointer to new array pointer
		m_inner_array = new_array;

		return true;
	}

	template<typename T>
	bool dynamic_array<T>::copy(__int32 source_begin_position, __int32 source_end_position, 
		__int32 des_begin_position, T * source_array, T * destination_array)
	{
		for (int index = source_begin_position; index < source_end_position; index++)
		{
			if (destination_array == source_array)
			{
				//TODO
			}
			else
			{
				destination_array[index] = source_array[index];
			}
		}

		return true;
	}

	template<typename T>
	__int32 dynamic_array<T>::get_after_enlarge_size()
	{
		return m_enlarge_factor * m_capacity;
	}

	template<typename T>
	__int32 dynamic_array<T>::get_after_reduce_size()
	{
		return m_reduce_factor * m_capacity;
	}

	template<typename T>
	bool dynamic_array<T>::safe_delete_array(T * array)
	{
		__int32 current_position = m_size;
		while (current_position-- < 0)
		{
			delete m_inner_array[current_position];
			m_inner_array[current_position] = NULL;
		}
		return false;
	}
} // namespace tg