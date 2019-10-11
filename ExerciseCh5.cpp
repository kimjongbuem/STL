#include <iostream>
#include<string>
#include<set>
#include<vector>
#include<iterator>
#include<unordered_set>
#include<random>
#include<iomanip>
#include<sstream>
#include<algorithm>
#include<math.h>
#include<map>
using namespace std;

class Card {
private:
	int number;
	string pattern;
public:
	Card(int number, string pattern) {
		this->number = number;
		this->pattern = pattern;
	}
	Card() {

	}
	friend ostream& operator<<(ostream& os, const Card card);
	bool operator<(const Card card) const {
		return (card.pattern < pattern) || ((card.pattern == pattern) && card.number< number);
	}
	string getPattern() const{
		return pattern;
	}
	int getNumber() const {
		return number;
	}
	bool operator()(const Card card) {
		return (pattern < card.pattern) || number < card.number;
	}
};

class CardFuncter {
public:
	bool operator()(const Card& card1, const Card& card2) {
		return (card1.getPattern()< card2.getPattern()) || card1.getNumber()< card2.getNumber();
	}
};

inline ostream& operator<<(ostream& os, const Card card) {
	os << card.number << " " << card.pattern << endl;
	return os;
}


void getRandomCard(vector<Card>& cards, set<Card>& sets) {
	random_device rn;
	mt19937_64 rnd((rn()));
	size_t size = cards.size();
	uniform_int_distribution<int> range(0, size - 1);
	int idx = range(rnd);

	sets.emplace(cards[idx]);
	
	cards.erase(cards.begin() + idx);
	cards.reserve(size - 1);	
}
 //1¹ø
int main() {
	vector<Card> setcard;
	set<Card> North, South, East, West;
	for (int i = 1; i <= 13; i++) {
		setcard.emplace_back(Card(i,"Diamond"));
	}
	for (int i = 1; i <= 13; i++) {
		setcard.emplace_back(Card(i, "Clover"));
	}
	for (int i = 1; i <= 13; i++) {
		setcard.emplace_back(Card(i, "Heart"));
	}
	for (int i = 1; i <= 13; i++) {
		setcard.emplace_back(Card(i, "Space"));
	}

	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 13; i++) {
			switch (j)
			{
			case 0:
				getRandomCard(setcard, North);
				break;
			case 1:
				getRandomCard(setcard, South);
				break;
			case 2:
				getRandomCard(setcard, West);
				break;
			case 3:
				getRandomCard(setcard, East);
				break;
			}
		}
	}

	for (int j = 0; j < 4; j++) {
			switch (j)
			{
			case 0:
				printf("North : \n");
				copy(begin(North), end(North), ostream_iterator<Card>(cout," "));
				break;
			case 1:
				printf("South : \n");
				copy(begin(South), end(South), ostream_iterator<Card>(cout, " "));
				break;
			case 2:
				printf("West : \n");
				copy(begin(West), end(West), ostream_iterator<Card>(cout, " "));
				break;
			case 3:
				printf("East : \n");
				copy(begin(East), end(East), ostream_iterator<Card>(cout, " "));
				break;
			}
	}
	system("pause");
}

//2¹ø

class HashWord {
public:
	size_t operator()(const string& word) {
		return hash<string>()(word);
	}
};
int main()
{
	cout << "Enter some text and Enter * to end: \n";
	string text_in{};
	getline(cin, text_in, '*');

	replace_if(begin(text_in), end(text_in), [](const char& ch) {return !isalpha(ch); }, ' ');
	istringstream text{ text_in };
	istream_iterator<string> begin(text), end;
	unordered_multiset<string> words;
	size_t max_len = 0;
	for_each(begin, end, [&max_len, &words](const string& word) {
		words.emplace(word);
		max_len = std::max(max_len, word.length());
	});

	size_t per_line = 4;
	size_t count = 0;

	for (auto iter = words.begin(); iter != words.end(); iter++) {
		cout << left << setw(max_len + 1) << *iter << setw(3) << right << words.count(*iter) << " ";
		if (++count % per_line == 0) cout << endl;
	}
	system("pause");
}

//3¹ø

void getRandomNumber(multiset<int>& mulSet) {
	random_device rn;
	mt19937_64 rnd((rn()));;
	uniform_int_distribution<int> range(1, 6);
	int n1 = range(rnd);
	int n2 = range(rnd);
	mulSet.insert(n1 + n2);
}

int main() {
	multiset<int> mulSet;
	for (int i = 0; i < 1000; i++) {
		getRandomNumber(mulSet);
	}
	for (auto iter = begin(mulSet); iter != end(mulSet);) {
		auto e = mulSet.equal_range(*iter);

		cout << left << setw(2) << *iter << setw(3) << right << mulSet.count(*iter) << " ";

		iter = e.second;
		cout << endl;
	}
		system("pause");
}

