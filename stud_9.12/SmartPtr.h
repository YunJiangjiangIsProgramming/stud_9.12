#pragma once

template<class T >
class SmartPtr
{
public:
	SmartPtr(T* ptr)
		:_ptr(ptr)
	{}
	~SmartPtr()
	{
		if (_ptr)
		{
			delete _ptr;
			cout << "析构完成" << endl;
		}
	}
	T& operator*()//模拟原生指针
	{
		return *_ptr;
	}
	T* operator->()
	{
		return _ptr;
	}
private:
	T* _ptr;

};
