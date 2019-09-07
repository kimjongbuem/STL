#include <iostream>
#include<list>
#include<deque>
#include<algorithm>
#include <string>
#include<stack>
#include<queue>
using namespace std;

bool compare1(const shared_ptr<string>& p1, const shared_ptr<string>& p2) {
	if (*p1 < *p2) return true;
	return false;
}
int main() {
	//1. deque 컨테이너에 원하는만큼 단어를 저장하고 이것을 list에 복제, 리스트의 내용을 오름차순하여라
	/*deque<shared_ptr<string>> words;
	list < shared_ptr<string>> wordList;
	string word;
	cout << "Ctrl + z 입력하면 입력 종료합니당!" << endl;
	while (true) {
		if ((cin >> word).eof()) {
			cin.clear();
			break;
		}
		words.push_back(make_shared<string>(word));
	}
	cout << "deque data :" << " ";
	for (deque<shared_ptr<string>>::iterator iter = begin(words); iter != end(words); iter++) {
		cout << **iter << " ";
		wordList.emplace_back(*iter);
	}
	cout << endl;

	wordList.sort(compare1);
	cout << "list data :" << " ";
	for (list<shared_ptr<string>>::iterator iter = begin(wordList); iter != end(wordList); iter++) {
		cout << **iter << " ";
	}
	cout << endl;*/
	// 2. stack<T> 컨테이너 어댑터 인스턴스를 사용해서 키보드에서 입력한 한줄 문장에 있는 문자들의 순서를 뒤바꾸는 프로그램 뒤바꾼 문장과 회문여부를 출력한다. 공백, 문장부호 무시.

	//1.string을 char[]로 변환

	//	2.char[]를 strtok으로 잘라냄

	//	3.잘라낸 char[]를 다시 string으로 변환

	//	4.string배열에 적재

	//string data;
	//getline(cin, data, '\n');
	//data.erase(remove(begin(data), end(data), '\n'), data.end());
	//char* tok_buff = new char[256];

	//strcpy_s(tok_buff, 256, data.c_str());

	//char* context = NULL;
	//char* tok = strtok_s(tok_buff, " ,\"-?", &context);
	//stack<char> stack1;

	//while (tok != nullptr) {
	//	int cnt = 0;
	//	while (tok[cnt] != NULL) {
	//		stack1.push(tok[cnt++]);
	//	}
	//	tok = strtok_s(nullptr, " ,\"-?!", &context);
	//}

	//stack<char> stack2 = stack1;
	//stack<char> stack3;
	//while (!stack1.empty()) {
	//	cout << stack1.top();
	//	stack3.push(stack1.top());
	//	stack1.pop();
	//}
	//cout << endl;
	//bool check = false;
	//while (!stack2.empty()) {
	//	if (stack2.top() != stack3.top())
	//	{
	//		check = false;
	//		break;
	//	}
	//	stack2.pop();
	//	stack3.pop();
	//	check = true;
	//}
	//if (check) cout << "회문입니다" << endl;
	//else cout << "회문이 아닙니다" << endl;

	// 3번 priority_queue 컨테이너 어댑터 인스턴스를 이용하여 키보드에 입력된 단어들을 알파벳 역순으로 출력하라.
	priority_queue<char,deque<char>,less<char>> pq;
	char c;
	while (true) {
		if ((cin >> c).eof()){
			cin.clear();
			break;
		}
		pq.push(c);
	}
	while (!pq.empty()) {
		cout << pq.top() << " ";
		pq.pop();
	}
	
	system("pause");
	
}