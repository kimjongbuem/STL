//#include<vector>
//#include<algorithm>
//#include<iostream>
//using namespace std;
//int main() {
//	// is_heap_until ex //
//	vector<double> numbers = { 2.5,10,3.5,6.5,8.0,12.0,1.5,6.0 };
//	make_heap(begin(numbers), end(numbers), greater<>());
//	pop_heap(begin(numbers), end(numbers), greater<>());
//	vector<double>::iterator iter = is_heap_until(begin(numbers), end(numbers), greater<>());
//	if (iter != end(numbers))
//		cout << *iter << endl;
//
//	system("pause");
//}

#include <iostream>
#include<string>
#include<iomanip>
#include<algorithm>
#include<deque>
using namespace std;

template<class T>
void show(deque<T> words, size_t count = 5) {
	if (words.empty()) return;
	// 가장 긴문자열을 찾기
	size_t max_len = max_element(begin(words), end(words), [](const string& s1, const string& s2) {return s1.size() < s2.size(); })->size();
	size_t n = count;
	for (const auto& word : words) {
		cout << setw(max_len + 1) << word << " ";
		if (--n) continue;
		cout << endl;
		n = count;
	}
	cout << endl;
	/*
		해당람다식은 bool comp(t1, t2) 비교함수
	*/
}
//noexcept
int main() {
	deque<string> words;
	string word;
	cout << "Enter words seperated by spaces enter ctrl+z on a separate line to end: \n";
	while (true) {
		if ((cin >> word).eof()) {
			cin.clear();
			break;
		}
		words.push_back(word);
	}
	cout << "you entered " << words.size() << " words" << endl;
	show(words);

	make_heap(begin(words), end(words));
	cout << "\nAfter making a heap the words in the list are: " << endl;
	show(words);

	cout << "\nYou Entered " << words.size() << " words. Enter some more: " << endl;
	while (true) {
		if ((cin >> word).eof()) {
			cin.clear();
			break;
		}
		words.push_back(word);
		push_heap(begin(words), end(words));
	}
	cout << "\nThe Words in the list are now:" << endl;
	show(words);
	system("pause");
}