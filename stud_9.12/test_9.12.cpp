#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<string>


using namespace std;
#include"SmartPtr.h"
#include"Shared_ptr.h"


void test_shared_ptr()
{
	// ����һ������ָ�벢�����ڴ�
    int* rawPtr = new int(10);

    // ʹ��rawPtr����һ��shared_ptr����
 luow::shared_ptr<int> sp1(rawPtr);

    // �������ָ���ԭʼֵ
    std::cout << "Value through sp1: " << *sp1 << std::endl;

    // �����ڶ���shared_ptr����ָ��ͬһ������
    luow::shared_ptr<int> sp2 = sp1;

    // �������ָ���ԭʼֵ��Ӧ�ú�sp1��ͬ
    std::cout << "Value through sp2: " << *sp2 << std::endl;

    // �ͷ�����һ��shared_ptr�����ǲ���ɾ��ԭʼ��int����Ϊ���ü�����Ϊ��
    sp1.reset(); // ע�⣺reset()������Ҫ���������ʵ�֣���������ʾ��

    // ���sp2��ֵ����ʱsp1�Ѿ�resetΪnullptr
    std::cout << "Value through sp2 after sp1 reset: " << *sp2 << std::endl;

    // �ͷ����һ��shared_ptr���⽫����ɾ��ԭʼ��int
    sp2.reset();
}
void test_smart_ptr()
{
    SmartPtr<int> sptr(new int(10));

    // ʹ�ý�������������ʺ��޸�����ָ�����Ķ���
    *sptr = 20;
    cout << "�޸ĺ��ֵΪ: " << *sptr << endl; // Ӧ���20
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