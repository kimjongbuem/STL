#include <iostream>
#include<vector>
#include<array>
#include<string>
#include<iterator>
#include<algorithm>
#include<list>
#include<deque>
using namespace std;

// vector, list , deque 
void print(deque<string>::iterator first, deque<string>::iterator last) {
	short cnt = 1;
	int longestData = 0;
	auto c = first;
	while (first != last) {
		if (first->size() > longestData) {
			longestData = first->size();
		}
		first++;
	}

	
	cout.width(longestData);
	while (c != last) {
		cout << *c<<"\t";
		if(cnt % 2 == 0) cout << endl;
		cout.width(longestData);
		cnt++;
		c++;
	}
	cout << endl;
}
int main() {
	// q1 피보나치 문제임//
	/*array<int, 50> fibonaciArray = { 0 };
	int curIndex = 0;
	transform(begin(fibonaciArray), end(fibonaciArray), ostream_iterator<int>(std::cout, " "), [&](int val) {
		if (curIndex == 0) { fibonaciArray[curIndex] = 0; curIndex++;  return 0; }
		else if (curIndex == 1) { fibonaciArray[curIndex] = 1; curIndex++; return 1; }
		else {
			fibonaciArray[curIndex] = fibonaciArray[curIndex - 1]+ fibonaciArray[curIndex - 2];
			return fibonaciArray[curIndex++];
		}
	});
	cout << curIndex << endl;*/
	// q2 키보드에 도시 이름을 원하는 만큼 읽어서 vector<t> string형태로 보여주어라.
	//vector<string> citys;
	//copy(istream_iterator<string>{cin}, istream_iterator<string>{}, back_inserter(citys));
	//auto c = citys.begin();
	//cout << "정렬을 시작합니다 !" << endl;
	//sort(citys.begin(), citys.end());
	//print(citys.begin(), citys.end(), citys.size());
	//getchar();        // 문자하나버리기

	//q3 list<T> 이용하기 //
	list<string> citys;
	string data;
	while (getline(cin, data, '\n'), !data.empty()) {
		citys.push_back(data);
	}
	/*citys.sort();
	print(citys.begin(), citys.end());*/
	/*
		getline메서드를 이용해 각문자를 받고 엔터 키를 제외한 모든 String데이터를 가져가 추가하는 형태임.
	*/
	getchar();

	//q4 deque
	deque<string>deques;
	copy(citys.begin(), citys.end(), front_inserter(deques));
	sort(deques.begin(), deques.end());
	print(deques.begin(), deques.end());

	int a;
	scanf_s("%d", &a, sizeof(a));
}