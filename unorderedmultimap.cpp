#include<string>
#include<iostream>
#include<unordered_map>
#include<istream>
#include<ostream>
#include<utility>
#include<tuple>
#include<cctype>

using namespace std;
//int main() {
//	std::unordered_multimap<string, size_t> people = { {"jim",33},{"joe",64} };
//	unordered_map<string, size_t>::iterator iter = people.emplace("jan", 45);
//	people.insert({ "jan",76 });
//	people.emplace_hint(iter, "jan",56 );
//	string key = "jan";
//	auto n = people.count(key);
//		cout << "first value : " << people.find(key)->first<< key << " is " << people.find(key)->second << endl;
//	if (n > 1) {
//		auto pr = people.equal_range(key);
//		while (pr.first != pr.second) {
//			cout << key << " is " << pr.first->second << endl;
//			++pr.first;
//		}
//	}
//	system("pause");
//}

using Name = pair<string, string>;
using Phone = tuple<string, string, string>;

istream& operator >> (istream& in, Name& name) {
	in >> std::ws >> name.first >> name.second;
	name = make_pair(name.first, name.second);
	return in;
}
ostream&operator<<(ostream& os, const Name& name){
	os << name.first << " " << name.second << endl;
	return os;
}

istream& operator >> (istream& in, Phone& p) {
	string area_code, exchange, number;

	in >> std::ws >> area_code >> exchange >> number;
	p = make_tuple(area_code, exchange, number);
	return in;
}
ostream&operator<<(ostream& os, const Phone p) {
	string area_code, exchange, number;
	tie(area_code, exchange, number) = p;
	os << area_code << " " << exchange<<" "<<" "<<number<< endl;
	return os;
}


class NameHash {
public:
	size_t operator()(const Name& name) const {
		return hash<string>()(name.first + name.second);
	}
};
class PhoneHash {
public:
	size_t operator()(const Phone& phone) const {
		return hash<string>()(get<0>(phone) + get<1>(phone) + get<2>(phone));
	}
};

void show_operations() {
	cout << "Operations:\n"
		<< "A: Add an element.\n" <<
		"D: Delete elements.\n" <<
		"F: Find elements" <<
		"L: List all elements" <<
		"Q: Quit the progr.\n\n";
}
template<typename Container>
/*
	�� ���ø��� �Լ��� ȣ��� �� ���� �̼����� �����̳� Ÿ���� �߷��Ұ��̴�. �ش� �� �����̳��� ���Ҵ� pair��ü��.
	byname �����̳ʿ����� ���Ҵ� pair<Name,Phone> , bynumber�� ���Ҵ� pair<Phone,Name>
*/
void list_elements(const Container& container) {
	for (const auto& element : container) {
		cout << element.first << " " << element.second << endl;
	}
}

//template<typename Container>
//auto find_elements(const Container& container)->pair<typename Container::const_iterator, typename Container::const_iterator> {
//	typename Container::key_type key{};
//	cin >> key;
//	auto pr = container.equal_range(key);
//	return pr;
//}
/*
	c++ 11 
	��ȯŸ���� �����̳� Ÿ�Կ� �������� pair<>���ø�Ÿ������ �����Ѵ�.
	pair��ü�� ĸ��ȭ�� �ݺ����� Ÿ���� �����̳� Ÿ�Կ� ���̱� �����̴�.(�����Ϸ��� ��ȯ Ÿ�� ���� ó�� �Ұ���)
	�����ȯŸ��
	�׷��� �̸� �������ִµ� 14���ʹ� �Լ��� ��ȯ Ÿ�� �߷б���� ������ �Ǿ Ÿ�������� ���ص��ȴ�.
*/
template<typename Container>
auto find_elements(const Container& container){
	typename Container::key_type key{};
	cin >> key;
	auto pr = container.equal_range(key);
	return pr;
}

template<typename T>
void list_range(const T& pr) {
	if (pr.first != pr.second) {
		for (auto iter = pr.first; pr.first != pr.second; ++iter) {
			cout << " " << iter->first << " " << iter->second << endl;
		}
	}
	else
		cout << "No recoreds Found!";
}

int main() {
	unordered_multimap<Name, Phone, NameHash> by_name{ 8,NameHash() };
	unordered_multimap<Phone, Name, PhoneHash> by_number{ 8,PhoneHash() };
	char choice{};
	Phone number{};
	Name name{ };
	while (toupper(choice) != 'Q') {
		cout << "Enter a command: ";
		cin >> choice;

		switch (toupper(choice)) {
		case'A':
			cout << "Enter first & second names, area_code, exchange, and number separated by spaces:\n";
			cin >> name >> number;
			by_name.emplace(name,number);
			by_number.emplace(number, name);
			break;
		case 'D':
			cout << "Enter a name: ";
			auto pr = find_elements(by_name);
			auto count = distance(pr.first, pr.second);
			if (count == 1) {
				by_number.erase(pr.first->second);
				by_name.erase(pr.first);
			}
			else if (count > 1) {
				cout << "There are " << count << "record for " << pr.first->first << ". Delete all(Y or N)? ";
				cin >> choice;
				if (toupper(choice) == 'Y') {
					for (auto iter = pr.first; iter != pr.second; ++iter) {
						by_number.erase(iter->second);
					}
					by_name.erase(pr.first->first);
				}
			}
			break;

		case 'F':
			cout << "Find by Name(Y or N)? :";
			cin >> choice;
			if (toupper(choice) == 'Y') {
				cout << "Enter first name and second name: ";
				list_range(find_elements(by_name));
			}
			else {
				cout << "Enter area code, exchange, and number separated by spaces: ";
				list_range(by_number);
			}
			break;
		
		case 'L':
			cout << "List by name(Y or N)? :";
			cin >> choice;
			if (toupper(choice) == 'Y') {
				list_elements(by_name);
			}
			else
				list_elements(by_number);
			break;

		case 'Q':
			break;
		defalut:
			cout << "Invalid command - try again\n";
			break;
		}
	}
	show_operations();

	system("pause");
}