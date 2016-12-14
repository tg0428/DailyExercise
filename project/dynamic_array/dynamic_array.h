#pragma once

namespace tg
{
	template <typename T> class dynamic_array
	{
	public:
		dynamic_array();
		~dynamic_array();

	public:
		__int32 size();          // get array's size
		__int32 capacity();      // array's capacity
		__int32 find(T& value);  // find index where item is at
		__int32 push(T& value);  // push item at tail of the array 
		__int32 remove(T& value);// remove item
		__int32 insert(__int32 index, T& value);  // insert item at the position where item asks to be inserted
		void pop();                // pop item at the tail of the array
		bool is_empty();         // judge the array is empty or not
		void erase(__int32 index);  //  erase item at the position where it be asked 
		T* at(__int32 index);    // get item's value where it's position is index

	private:
		bool resize(__int32 size);// private method : resize array if necessary
		bool copy(__int32 source_begin_position, __int32 source_end_position, 
			__int32 des_begin_position, T* source_array, T* destination_array);  // copy source array to destination array from begin postion to end position
		__int32 get_after_enlarge_size();// get after enlarge size
		__int32 get_after_reduce_size(); // get after reduce size

		bool safe_delete_array(T* array); // delete array

	private:
		__int32 m_size;           // the size of the current array 
		__int32 m_capacity;       // the capacity of the current array
		T m_inner_array[1];       // inner array, the size is 1

		double m_enlarge_factor; // enlarge_factor
		double m_reduce_factor;  // reduce factor
	};
	
} // namespace tg