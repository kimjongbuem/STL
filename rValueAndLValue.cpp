#include <iostream>
struct X {};
void func(X&& t)
{
	std::cout << "RValue" << std::endl;
}
void func(X& t)
{
	std::cout << "LValue" << std::endl;
}
template<typename T>
void foo(T&& t)
{
	func(std::forward<T>(t));
}

int main()
{
	X x;
	foo(x);
	foo(X());
	system("pause");
	return 0;
}


//��ó: https://skstormdummy.tistory.com/entry/����-��-����-RValue-Reference [�������� ����(�ӽ�)]