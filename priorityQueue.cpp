#include <iostream>
#include<queue>
#include<string>
using namespace std;

template<class T>
void list_pq(priority_queue<T> pq, size_t count = 5) {
	size_t n = count;
	while (!pq.empty()) {
		cout << pq.top() << " ";
		pq.pop();
		if (--n) continue;
		cout << endl;
		n = count;
	}
	cout << endl;
}
//noexcept
int main() {
	priority_queue<string> words;
	string word;
	cout << "Enter words seperated by spaces enter ctrl+z on a separate line to end: \n";
	while (true) {
		if ((cin >> word).eof()) {
			break;
		}
		words.push(word);
	}
	cout << "you entered " << words.size() << " words" << endl;
	list_pq(words);
	int n;
	scanf_s("%d", &n);
}