#include <iostream>                              // 표준 스트림
#include <string>                                // string 클래스
#include <algorithm>                             // copy() 알고리즘
#include <iterator>                              // ostream_iterator
#include <map>                                   // map 컨테이너
#include <set>                                   // multiset 컨테이너
#include <memory>                                // 스마트 포인터
#include <cctype>                                // toupper()
#include"PetClass.h"

using std::string;
using Name = string;
using Pet_ptr = std::shared_ptr<Pet>;
using Pets = std::multiset<Pet_ptr>;

inline bool operator<(const Pet_ptr& p1, const Pet_ptr& p2)
{
	return *p1 < *p2; // operator< 해당 클래스가 정의.
}

// Pet에 대한 포인터를 위한 스트림 삽입 연산자
inline std::ostream& operator<<(std::ostream& out, const Pet_ptr& pet_ptr)
{
	return out << " " << *pet_ptr;
}

Pets get_pets(const Name& person) {
	Pets pets;
	std::cout << "Enter " << person << " 's pest:\n";
	char ch{};
	Name name{};
	while (true) {
		std::cin >> ch;
		if (toupper(ch) == 'Q') break;
		std::cin >> name;
		switch (toupper(ch)) {
		case 'C':
			pets.insert(std::make_shared<Cat>(name));
			break;
		case 'D':
			pets.insert(std::make_shared<Dog>(name));
			break;
		case 'M':
			pets.insert(std::make_shared<Mouse>(name));
			break;
		default:
			std::cout << "Invalid pet ID - try again.\n";
		}
	}
	return pets;
}

void list_pets(const std::pair<Name, Pets>& pr) {
	std::cout << "\n" << pr.first << ":\n";
	std::copy(std::begin(pr.second), std::end(pr.second), std::ostream_iterator<Pet_ptr>(std::cout, "\n"
		));
}

int main() {
	std::map<Name, Pets> peoples_pets; // 사람과 애완동물 
	char answer{ 'Y' };
	string name{};
	std::cout << "You'll enter a person's name followed by their pets.\n"
		<< "Pets can be identified by C for cat, D for dog, or M for mouse.\n"
		<< "Enter the character to identify each pet type followed by the pet's name.\n"
		<< "Enter Q to end pet input for a person.\n";

	while (std::toupper(answer) == 'Y') {
		std::cout << "Enter a name: ";
		std::cin >> name;
		peoples_pets.emplace(name, get_pets(name));
		std::cout << "Another person(Y or N)? ";
		std::cin >> answer;
	}
	for (const auto& pr : peoples_pets) {
		list_pets(pr);
	}
	system("pause");
}