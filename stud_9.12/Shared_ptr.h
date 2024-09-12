#pragma once

//template<class T>
//class shared_ptr
//{
//public:
//	shared_ptr(T* ptr)
//		:_ptr(ptr)
//		, _pcount(new int(1))
//	{
//
//	}
//	shared_ptr(shared_ptr<T>&sp)
//		:_ptr(sp._ptr)
//		, _pcount(sp._pcount)
//	{
//		++(*_pcount);
//	}
//	T& operator*()
//	{
//		return *_ptr;
//	}
//	T* operator->()
//	{
//		return _ptr;
//	}
//	~shared_ptr()
//	{
//		if (--(*_pcount) == 0 && _ptr)
//		{
//			cout << "delete:" << _ptr << endl;
//			delete _ptr;
//			_ptr = nullptr;
//
//			delete _pcount;
//			_pcount = nullptr;
//
//		}
//	}
//	shared_ptr<T>& operator=(shared_ptr <T>& sp)
//	{
//		if (this != &sp)
//		{
//			if (--(*_pcount==0)
//			{
//				delete _pcount;
//				delete _ptr;
//			}
//			_ptr = sp._ptr;
//			_pcount = sp._pcount;
//			++(*_pcount);
//			return this;
//		}
//	}
//	
//private:
//	T* _ptr;
//	int* _pcount;
//};

namespace luow
{
template<class T>
class shared_ptr {
public:
    shared_ptr(T* ptr) : _ptr(ptr), _pcount(new int(1)) { }

    shared_ptr(const shared_ptr<T>& sp) : _ptr(sp._ptr), _pcount(sp._pcount) {
        ++(*_pcount);
    }

    shared_ptr& operator=(const shared_ptr<T>& sp) {
        if (this != &sp) {
            if (--(*_pcount) == 0) {
                delete _pcount;
                delete _ptr;
            }
            _ptr = sp._ptr;
            _pcount = sp._pcount;
            ++(*_pcount);
        }
        return *this;
    }

    T& operator*() {
        return *_ptr;
    }

    T* operator->() {
        return _ptr;
    }

    ~shared_ptr() {
        if (--(*_pcount) == 0) {
            delete _ptr;
            delete _pcount;
        }
    }

    // 在shared_ptr类中添加reset()成员函数
    void reset(T* ptr = nullptr) {
        shared_ptr<T> temp(ptr); // 使用传入的指针创建一个临时的shared_ptr
        std::swap(_ptr, temp._ptr); // 交换当前对象和临时对象的_ptr成员
        std::swap(_pcount, temp._pcount); // 交换当前对象和临时对象的_pcount成员
    }

private:
    T* _ptr;
    int* _pcount;
};

}


//注释版本：
namespace luow1{
    // 定义了一个模板类shared_ptr，用于管理动态分配的资源，并提供引用计数机制。
    template<class T>
    class shared_ptr {
    public:
        // 构造函数：接收一个T类型的指针，初始化shared_ptr对象。
        // 该构造函数接收一个T类型的指针，并用它来初始化shared_ptr的内部指针和引用计数。
        // 这个构造函数用于在创建shared_ptr对象时传入一个已经分配的资源。
        shared_ptr(T* ptr) : _ptr(ptr), _pcount(new int(1)) { }

        // 拷贝构造函数：从另一个shared_ptr对象拷贝资源和引用计数。
        // 这个构造函数在创建新的shared_ptr对象时，如果该对象需要与已存在的shared_ptr对象共享资源时被调用。
        // 它会增加资源的引用计数，以确保资源在多个shared_ptr对象之间被正确共享。
        shared_ptr(const shared_ptr<T>& sp) : _ptr(sp._ptr), _pcount(sp._pcount) {
            ++(*_pcount);
        }

        // 拷贝赋值运算符：从另一个shared_ptr对象拷贝资源和引用计数。
        // 当一个shared_ptr对象被赋值给另一个shared_ptr对象时，这个运算符被调用。
        // 它会减少当前对象的引用计数，如果引用计数降为0，资源和引用计数会被删除。
        // 然后，它将另一个shared_ptr对象的资源和引用计数复制到当前对象。
        shared_ptr& operator=(const shared_ptr<T>& sp) {
            if (this != &sp) { // 防止自赋值
                if (--(*_pcount) == 0) { // 减少引用计数，如果计数为0则删除资源
                    delete _pcount;
                    delete _ptr;
                }
                _ptr = sp._ptr;
                _pcount = sp._pcount;
                ++(*_pcount); // 增加新的引用计数
            }
            return *this;
        }

        // 解引用运算符：返回shared_ptr管理的资源的引用。
        // 这个运算符允许通过shared_ptr对象来访问它管理的资源，就像直接使用原始指针一样。
        T& operator*() {
            return *_ptr;
        }

        // 箭头运算符：返回shared_ptr管理的资源的指针。
        // 这个运算符允许通过shared_ptr对象来访问它管理的资源的成员，就像直接使用原始指针一样。
        T* operator->() {
            return _ptr;
        }

        // 析构函数：在shared_ptr对象销毁时释放资源。
        // 析构函数会减少资源的引用计数，如果引用计数降为0，资源和引用计数会被删除。
        ~shared_ptr() {
            if (--(*_pcount) == 0) {
                delete _ptr;
                delete _pcount;
            }
        }

        // reset成员函数：重置shared_ptr管理的资源。
        // 这个成员函数允许shared_ptr对象释放当前管理的资源，然后指向一个新的资源。
        // 如果没有参数传入，shared_ptr将被重置为nullptr。
        // 注意：当前的实现方式并不高效，因为它创建了一个临时的shared_ptr对象。
        // 更好的实现方式是在内部直接处理资源的释放和分配。
        //void reset(T* ptr = nullptr) {
        //    shared_ptr<T> temp(ptr); // 使用传入的指针创建一个临时的shared_ptr
        //    std::swap(_ptr, temp._ptr); // 交换当前对象和临时对象的_ptr成员
        //    std::swap(_pcount, temp._pcount); // 交换当前对象和临时对象的_pcount成员
        //}
        // 更优的reset实现
        void reset(T* ptr = nullptr) {
            if (ptr != _ptr) {
                if (--(*_pcount) == 0) { // 减少引用计数，如果计数为0则删除资源
                    delete _pcount;
                    delete _ptr;
                }
                _ptr = ptr;
                if (ptr) {
                    _pcount = new int(1);
                }
                else {
                    _pcount = nullptr;
                }
            }
        }

    private:
        // 管理的资源指针
        T* _ptr;
        // 资源的引用计数指针
        int* _pcount;
    };
}