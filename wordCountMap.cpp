#include<string>
#include<iostream>
#include<iomanip> //��Ʈ�� ������
#include<map> 
#include<sstream> // istringstream
#include<algorithm> // replace_of. for_each()
#include<iterator> // istream_iterator
#include<cctype> // isalpha : �������ΰ�?

using namespace std;

int main() {
	cout << "Enter some text and enter * to end:\n";
	string text_in{};
	getline(cin, text_in, '*');
	replace_if(begin(text_in), end(text_in), [](const char& ch) {return !isalpha(ch); }, ' ');
	istringstream text(text_in); // �ؽ�Ʈ �Է� ���ڿ��� ��Ʈ������...
	istream_iterator<string> begin(text); istream_iterator<string> end; // ��Ʈ���ݺ���
	map<string, size_t> words; size_t max_len{};
	// �ܾ ������ �ʿ� �����ϰ� �ִ� ���̸� ã�´� //
	for_each(begin, end, [&max_len, &words](const string&word) {
		words[word]++;
		max_len = max(max_len, word.length());
	});
	// �ܾ�� �ܾ� �󵵸� ����Ѵ� //
	size_t per_line = 4; size_t count = 0;
	for (const auto& w : words) {
		cout << left << setw(max_len + 1) << w.first << setw(3) << right << w.second<<" ";
		if (++count % per_line == 0) cout << endl;
	}
	
	cout << endl;
	system("pause");
}