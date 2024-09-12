#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<string>


using namespace std;
#include"SmartPtr.h"
#include"Shared_ptr.h"


void test_shared_ptr()
{
	// 创建一个整数指针并分配内存
    int* rawPtr = new int(10);

    // 使用rawPtr创建一个shared_ptr对象
 luow::shared_ptr<int> sp1(rawPtr);

    // 输出共享指针的原始值
    std::cout << "Value through sp1: " << *sp1 << std::endl;

    // 创建第二个shared_ptr对象，指向同一个对象
    luow::shared_ptr<int> sp2 = sp1;

    // 输出共享指针的原始值，应该和sp1相同
    std::cout << "Value through sp2: " << *sp2 << std::endl;

    // 释放其中一个shared_ptr，但是不会删除原始的int，因为引用计数不为零
    sp1.reset(); // 注意：reset()函数需要在你的类中实现，这里用作示例

    // 输出sp2的值，此时sp1已经reset为nullptr
    std::cout << "Value through sp2 after sp1 reset: " << *sp2 << std::endl;

    // 释放最后一个shared_ptr，这将真正删除原始的int
    sp2.reset();
}
void test_smart_ptr()
{
    SmartPtr<int> sptr(new int(10));

    // 使用解引用运算符访问和修改智能指针管理的对象
    *sptr = 20;
    cout << "修改后的值为: " << *sptr << endl; // 应输出20
}


int main()
{
	int* a = new int;
	SmartPtr<int> sptr1(a);
	//SmartPtr<make_pair(int,int)> sptr2(new make_pair(3, 4));
    test_shared_ptr();
    test_smart_ptr();

	return 0;
}