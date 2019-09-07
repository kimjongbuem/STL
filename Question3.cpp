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
bool compare2(const shared_ptr<char>& p1, const shared_ptr<char>& p2) {
	if (*p1 < *p2) return true;
	return false;
}
int main() {
	//1. deque �����̳ʿ� ���ϴ¸�ŭ �ܾ �����ϰ� �̰��� list�� ����, ����Ʈ�� ������ ���������Ͽ���
	/*deque<shared_ptr<string>> words;
	list < shared_ptr<string>> wordList;
	string word;
	cout << "Ctrl + z �Է��ϸ� �Է� �����մϴ�!" << endl;
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
	// 2. stack<T> �����̳� ����� �ν��Ͻ��� ����ؼ� Ű���忡�� �Է��� ���� ���忡 �ִ� ���ڵ��� ������ �ڹٲٴ� ���α׷� �ڹٲ� ����� ȸ�����θ� ����Ѵ�. ����, �����ȣ ����.

	//1.string�� char[]�� ��ȯ

	//	2.char[]�� strtok���� �߶�

	//	3.�߶� char[]�� �ٽ� string���� ��ȯ

	//	4.string�迭�� ����

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
	//if (check) cout << "ȸ���Դϴ�" << endl;
	//else cout << "ȸ���� �ƴմϴ�" << endl;

	// 3�� priority_queue �����̳� ����� �ν��Ͻ��� �̿��Ͽ� Ű���忡 �Էµ� �ܾ���� ���ĺ� �������� ����϶�.
	/*priority_queue<char,deque<char>,less<char>> pq;
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
	}*/
	// 4�� �������� 1�� �̹��� ����Ʈ �����͸� �Ẹ��!
	// 5�� �������� 3�� �̹��� ����Ʈ �����͸� �Ẹ��!
	
	//auto comp2 = [](const shared_ptr<char>& c1, const shared_ptr<char>& c2) {
	//	return *c1 < *c2;
	//};

	//priority_queue<shared_ptr<char>, deque<shared_ptr<char>>,decltype(comp2)> pq(comp2);
	//char c;
	//while (true) {
	//	if ((cin >> c).eof()) {
	//		cin.clear();
	//		break;
	//	}
	//	pq.push(make_shared<char>(c));
	//}
	//while (!pq.empty()) {
	//	cout << *pq.top() << " ";
	//	pq.pop();
	//}
	// 6�� Ű���忡�� �Է��� �ܾ���� ���ĺ� �������� ����ϰ� ���� �� �ܾ���� ����Ʈ �����͸� ���Ϳ� �����ϰ� ��������.	
	string s;
	vector<shared_ptr<string>> words;
	while (true) {
		if ((cin >> s).eof()){
			cin.clear();
			break;
		}
		words.emplace_back(make_shared<string>(s));
	}
	make_heap(begin(words), end(words), [](const shared_ptr<string>& p1, const shared_ptr<string>& p2) {
		return *p1 > *p2;
	});
	sort_heap(begin(words), end(words), [](const shared_ptr<string>& p1, const shared_ptr<string>& p2) {
		return *p1 > *p2;
	});
	for (vector<shared_ptr<string>>::iterator iter = words.begin(); iter != words.end(); iter++) {
		cout << **iter << endl;
	}
	system("pause");
	
}