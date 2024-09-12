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
			cout << "�������" << endl;
		}
	}
	T& operator*()//ģ��ԭ��ָ��
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
