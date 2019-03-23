#include <iostream>
#include <string>
#include<deque>
#include <iterator>
using namespace std;
int main() {

	// deque 선언//
	deque<int>dp1; // 1개의 원소만 ..
	deque<int>dp2(10);// 10개의 원소..
	deque<string>dp3 = { "fgfdgd","fgfdfdgfg","fhellod" };
	deque<string>dp4 = dp3; // 복사생성자.
	deque<string>dp5{ begin(dp3),end(dp3) };// 반복자를 이용한 초기화
	// size == capacity //
	// 원소접근 at(), [ ] //
	// 원소 추가와 제거 //
	// push_front, push_back pop_back,, pop_front, emplace , insert, erase , clear ...
	// 대체 //
	auto init_list = { string{"seven"}, string{"eight"} ,string{"nine"} }; // 단순히 리터럴로 받게되면 char* 템플릿인데 , string 템플릿으로 받아야함.. 그래서 에러
	dp3.assign(init_list);
	dp3.assign(8, "hello"); // 할당.
	for (auto& dequeList : dp3)
	{
		cout << dequeList << endl;
	}
	// 대입연산자와 재할당이 자유롭다 .
	/*deque<string>ex;
	ex = { "4546","fgfd" };
	for (auto& dequeList : ex)
	{
		cout << dequeList << endl;
	}*/
	deque<string>names;
	cout << "Enter first names separated by spaces. Enter Ctrl + Z on a new line to end:\n";
	copy(istream_iterator<string>{cin}, istream_iterator<string>{}, front_inserter(names));
	copy(begin(names),end(names),ostream_iterator<string>(cout," "));
}