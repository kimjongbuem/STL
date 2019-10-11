#include <iostream>
#include<string>
#include<set>
#include<map>
#include<vector>
#include<iterator>
#include<random>
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
using TRUMP = map<string, Card> ;

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
	//sort(begin(setcard), end(setcard), CardFuncter());

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