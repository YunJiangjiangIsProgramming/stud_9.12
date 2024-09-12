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

    // ��shared_ptr�������reset()��Ա����
    void reset(T* ptr = nullptr) {
        shared_ptr<T> temp(ptr); // ʹ�ô����ָ�봴��һ����ʱ��shared_ptr
        std::swap(_ptr, temp._ptr); // ������ǰ�������ʱ�����_ptr��Ա
        std::swap(_pcount, temp._pcount); // ������ǰ�������ʱ�����_pcount��Ա
    }

private:
    T* _ptr;
    int* _pcount;
};

}


//ע�Ͱ汾��
namespace luow1{
    // ������һ��ģ����shared_ptr�����ڹ���̬�������Դ�����ṩ���ü������ơ�
    template<class T>
    class shared_ptr {
    public:
        // ���캯��������һ��T���͵�ָ�룬��ʼ��shared_ptr����
        // �ù��캯������һ��T���͵�ָ�룬����������ʼ��shared_ptr���ڲ�ָ������ü�����
        // ������캯�������ڴ���shared_ptr����ʱ����һ���Ѿ��������Դ��
        shared_ptr(T* ptr) : _ptr(ptr), _pcount(new int(1)) { }

        // �������캯��������һ��shared_ptr���󿽱���Դ�����ü�����
        // ������캯���ڴ����µ�shared_ptr����ʱ������ö�����Ҫ���Ѵ��ڵ�shared_ptr��������Դʱ�����á�
        // ����������Դ�����ü�������ȷ����Դ�ڶ��shared_ptr����֮�䱻��ȷ����
        shared_ptr(const shared_ptr<T>& sp) : _ptr(sp._ptr), _pcount(sp._pcount) {
            ++(*_pcount);
        }

        // ������ֵ�����������һ��shared_ptr���󿽱���Դ�����ü�����
        // ��һ��shared_ptr���󱻸�ֵ����һ��shared_ptr����ʱ���������������á�
        // ������ٵ�ǰ��������ü�����������ü�����Ϊ0����Դ�����ü����ᱻɾ����
        // Ȼ��������һ��shared_ptr�������Դ�����ü������Ƶ���ǰ����
        shared_ptr& operator=(const shared_ptr<T>& sp) {
            if (this != &sp) { // ��ֹ�Ը�ֵ
                if (--(*_pcount) == 0) { // �������ü������������Ϊ0��ɾ����Դ
                    delete _pcount;
                    delete _ptr;
                }
                _ptr = sp._ptr;
                _pcount = sp._pcount;
                ++(*_pcount); // �����µ����ü���
            }
            return *this;
        }

        // �����������������shared_ptr�������Դ�����á�
        // ������������ͨ��shared_ptr�������������������Դ������ֱ��ʹ��ԭʼָ��һ����
        T& operator*() {
            return *_ptr;
        }

        // ��ͷ�����������shared_ptr�������Դ��ָ�롣
        // ������������ͨ��shared_ptr�������������������Դ�ĳ�Ա������ֱ��ʹ��ԭʼָ��һ����
        T* operator->() {
            return _ptr;
        }

        // ������������shared_ptr��������ʱ�ͷ���Դ��
        // ���������������Դ�����ü�����������ü�����Ϊ0����Դ�����ü����ᱻɾ����
        ~shared_ptr() {
            if (--(*_pcount) == 0) {
                delete _ptr;
                delete _pcount;
            }
        }

        // reset��Ա����������shared_ptr�������Դ��
        // �����Ա��������shared_ptr�����ͷŵ�ǰ�������Դ��Ȼ��ָ��һ���µ���Դ��
        // ���û�в������룬shared_ptr��������Ϊnullptr��
        // ע�⣺��ǰ��ʵ�ַ�ʽ������Ч����Ϊ��������һ����ʱ��shared_ptr����
        // ���õ�ʵ�ַ�ʽ�����ڲ�ֱ�Ӵ�����Դ���ͷźͷ��䡣
        //void reset(T* ptr = nullptr) {
        //    shared_ptr<T> temp(ptr); // ʹ�ô����ָ�봴��һ����ʱ��shared_ptr
        //    std::swap(_ptr, temp._ptr); // ������ǰ�������ʱ�����_ptr��Ա
        //    std::swap(_pcount, temp._pcount); // ������ǰ�������ʱ�����_pcount��Ա
        //}
        // ���ŵ�resetʵ��
        void reset(T* ptr = nullptr) {
            if (ptr != _ptr) {
                if (--(*_pcount) == 0) { // �������ü������������Ϊ0��ɾ����Դ
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
        // �������Դָ��
        T* _ptr;
        // ��Դ�����ü���ָ��
        int* _pcount;
    };
}