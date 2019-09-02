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


//출처: https://skstormdummy.tistory.com/entry/우측-값-참조-RValue-Reference [성가비의 세계(임시)]