#pragma once

namespace tg
{
	template<class T>
	class Singleton
	{
	public:
		static T* create_instance()
		{
			if (_Instance == nullptr)
			{
				_Instance = new T();
			}
			return _Instance;
		}
	public:
		static T* _Instance;
	};

	template<class T>
	T* Singleton<T>::_Instance = nullptr;
}