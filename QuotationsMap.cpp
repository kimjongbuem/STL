#include<vector>
#include<string>
#include<exception>
#include<map>
#include<iostream>
#include<ostream>
#include<istream>
#include<utility>
#include<cctype>
#include<iomanip>
using std::string;

class Name {
private:
	string firstName; string secondName;
public:
	Name() { firstName = ""; secondName = ""; }
	Name(const string& first, const string& second) {
		firstName = first; secondName = second;
	}
	bool operator<(const Name& name) const {
		return secondName < name.secondName || ((secondName < name.secondName) && (firstName < name.firstName));
	}
	friend std::ostream& operator<<(std::ostream& os, const Name& name);
	friend std::istream& operator>>(std::istream& in, Name& name);
};
std::ostream& operator<<(std::ostream& os, const Name& name) {
	os << name.firstName + " " + name.secondName;
	return os;
}
std::istream& operator>>(std::istream& in, Name& name) {
	in >> name.firstName >> name.secondName;
	return in;
}

std::pair<const Name, size_t> get_entry() {
	std::cout << "Enter first and second names followed by the age";
	Name name{}; size_t age = 0;
	std::cin >> name >> age;
	return std::make_pair(name, age);
}

void list_entries(const std::map<const Name, size_t>& people) {
	for (auto& entry : people) {
		std::cout << std::left << std::setw(30) << entry.first <<
			std::right << std::setw(4) << entry.second << std::endl;
	}
}
Name get_Name() {
	Name name{};
	std::cout << "Enter first name and second name: ";
	std::cin >> std::ws >> name; // ws는 공백을제거한다.
	return name;
}
string get_quote(const Name& name) {
	std::cout << "Enter the quotation for " << name <<
		". Enter * to end:\n";
	string quote;
	std::getline(std::cin >> std::ws, quote, '*');
	return quote;
}
class Quoations {
private:
	std::vector<string> qutoes;
public:
	Quoations& operator<<(const char* quote) {
		qutoes.emplace_back(quote);
		return *this;
	}
	// string 객체에서 벡터로 새 명언을 복제한다.
	Quoations& operator<<(string& quote) {
		qutoes.push_back(quote);
		return *this;
	}
	// 이동연산
	Quoations& operator<<(string&& quote) {
		qutoes.push_back(move(quote));
		return *this;
	}
	string& operator[](size_t index) {
		if (index < qutoes.size()) return qutoes[index];
		throw std::out_of_range("Invaild index to quoations");
	}
	string operator[](size_t index) const{
		if (index < qutoes.size()) return qutoes[index];
		throw std::out_of_range("Invaild index to quoations");
	}
	size_t size() const {
		return qutoes.size();
	}
	//명언의 시작반복자 반환
	std::vector<string>::iterator begin() {
		return std::begin(qutoes);
	}
	std::vector<string>::const_iterator begin() const {
		return std::begin(qutoes);
	}
	//명언의 끝 반복자 반환
	std::vector<string>::iterator end() {
		return std::end(qutoes);
	}
	std::vector<string>::const_iterator end() const {
		return std::end(qutoes);
	}
};

int main() {
	std::map<Name, Quoations> quotations;
	std::cout << "Enter 'A to add a quote" <<
		"\nEnter 'L' to list all quotes" <<
		"\nEnter 'G' tp get a quote." <<
		"\nEnter 'Q' to end.\n";

	Name name{};
	string quote{};
	char command{};
	while (command != 'Q') {
		std::cout << "\nEnter Command";
		std::cin >> command;
		command = static_cast<char>(toupper(command));
		switch (command) {
		case 'Q':
			break;

		case 'A':
			name = get_Name();
			quote = get_quote(name);
			quotations[name] << quote;
			break;

		case 'G':
			name = get_Name();
			const auto& quotes = quotations[name];
			size_t count = quotes.size();
			if (!count) {
				std::cout << "There are no quotes recorded for " << name << std::endl;
				continue;
			}
			size_t index{};
			if (count > 1) {
				std::cout << "There are" << count << " quotes for" << name << ". \n" << "Enter an index from 0 to" << count - 1 << ": ";
				std::cin >> index;
			}
			std::cout << quotations[name][index] << std::endl;
			break;

		case 'L':
			if (quotations.empty()) {
				std::cout << "\nNo quotations recored for anyone." << std::endl;
			}
			
			// list all quotations
			for (const auto& pr : quotations) {
				std::cout << '\n' << pr.first << std::endl;
				for (const auto& quote : pr.second) {
					std::cout << " " << quote << std::endl;
				}
			}	
			break;
		default:
			std::cout << " Command must be 'A', 'G', 'L', or 'Q'. Try again.\n";
			continue;
			break;
		}
	}
}