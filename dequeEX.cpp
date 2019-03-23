#include <iostream>
#include <string>
#include<deque>
#include <iterator>
using namespace std;
int main() {

	// deque ����//
	deque<int>dp1; // 1���� ���Ҹ� ..
	deque<int>dp2(10);// 10���� ����..
	deque<string>dp3 = { "fgfdgd","fgfdfdgfg","fhellod" };
	deque<string>dp4 = dp3; // ���������.
	deque<string>dp5{ begin(dp3),end(dp3) };// �ݺ��ڸ� �̿��� �ʱ�ȭ
	// size == capacity //
	// �������� at(), [ ] //
	// ���� �߰��� ���� //
	// push_front, push_back pop_back,, pop_front, emplace , insert, erase , clear ...
	// ��ü //
	auto init_list = { string{"seven"}, string{"eight"} ,string{"nine"} }; // �ܼ��� ���ͷ��� �ްԵǸ� char* ���ø��ε� , string ���ø����� �޾ƾ���.. �׷��� ����
	dp3.assign(init_list);
	dp3.assign(8, "hello"); // �Ҵ�.
	for (auto& dequeList : dp3)
	{
		cout << dequeList << endl;
	}
	// ���Կ����ڿ� ���Ҵ��� �����Ӵ� .
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