#include<string>
#include<iostream>
#include<iomanip> //스트림 조작자
#include<map> 
#include<sstream> // istringstream
#include<algorithm> // replace_of. for_each()
#include<iterator> // istream_iterator
#include<cctype> // isalpha : 영문자인가?

using namespace std;

int main() {
	cout << "Enter some text and enter * to end:\n";
	string text_in{};
	getline(cin, text_in, '*');
	replace_if(begin(text_in), end(text_in), [](const char& ch) {return !isalpha(ch); }, ' ');
	istringstream text(text_in); // 텍스트 입력 문자열을 스트림으로...
	istream_iterator<string> begin(text); istream_iterator<string> end; // 스트림반복자
	map<string, size_t> words; size_t max_len{};
	// 단어를 가져와 맵에 저장하고 최대 길이를 찾는다 //
	for_each(begin, end, [&max_len, &words](const string&word) {
		words[word]++;
		max_len = max(max_len, word.length());
	});
	// 단어와 단어 빈도를 출력한다 //
	size_t per_line = 4; size_t count = 0;
	for (const auto& w : words) {
		cout << left << setw(max_len + 1) << w.first << setw(3) << right << w.second<<" ";
		if (++count % per_line == 0) cout << endl;
	}
	
	cout << endl;
	system("pause");
}