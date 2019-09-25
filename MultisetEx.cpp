#include<iostream>
#include<cctype>
#include<iomanip>
#include<string>
#include<sstream>
#include<algorithm>
#include<set>
#include<iterator>

using std::string;


int main() {
	std::cout << "Enter some text and enter * to end:\n";
	string text_in{};
	std::getline(std::cin, text_in, '*');

	// 알파벳을 제외한 문자를 공백으로 체인지 //
	std::replace_if(std::begin(text_in), std::end(text_in), [](const char& ch) {
		return!isalpha(ch);
	},' ');
	std::istringstream text(text_in);
	std::istream_iterator<string> begin(text); std::istream_iterator<string> end;

	std::multiset<string> words;
	size_t max_len = 0;

	// 단어를 가져와 컨테이너에 저장하고 최대 길이를 찾는다 //

	std::for_each(begin, end, [&max_len, &words](const string& word) {
		words.emplace(word);
		
		max_len = std::max(max_len, word.length());
	});

	size_t per_line = 4;
	size_t count = 0 , word_count = 0;
	for (auto iter = std::begin(words); iter != std::end(words);) {
		word_count = words.count(*iter);
		std::cout << std::left << std::setw(max_len + 1) << *iter << std::setw(3) << std::right << word_count << " ";
		if (++count % per_line == 0) std::cout << std::endl;
		std::advance(iter, word_count);
	}
	std::cout << std::endl;
	system("pause");
}