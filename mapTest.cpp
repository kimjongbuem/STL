#include<ostream>
#include<istream>
#include <string>
#include<iostream>
#include <map>
#include<utility>
#include<cctype>
#include<iomanip>

using namespace std;

class Name {
private:
	string firstName; string secondName;
public:
	Name() { firstName = ""; secondName = ""; }
	Name(const string& first, const string& second) {
		firstName = first; secondName = second;
	}
	bool operator<(const Name& name) const {
		return secondName < name.secondName || ((secondName < name.secondName )&& (firstName < name.firstName));
	} 
	friend ostream& operator<<(ostream& os, const Name& name);
	friend istream& operator>>(istream& in, Name& name);
};
ostream& operator<<(ostream& os, const Name& name) {
	os << name.firstName + " " + name.secondName;
		return os;
}
istream& operator>>(istream& in, Name& name) {
	in >> name.firstName >> name.secondName;
	return in;
}

pair<const Name, size_t> get_entry() {
	cout << "Enter first and second names followed by the age";
	Name name{}; size_t age = 0;
	cin >> name >> age;
	return make_pair(name, age);
}

void list_entries(const map<const Name, size_t>& people) {
	for (auto& entry : people) {
		cout << left << setw(30) << entry.first <<
			right << setw(4) << entry.second << endl;
	}
}

int main() {
	map<const Name, size_t> people{ {{"Ann", "Dante"},25},{{"Bill", "Hook"},46},{{"Jim", "Jams"},32},{{"Mark", "Time"},32} };
	cout << "\nThe initial contents of the map is:\n";
	list_entries(people);
	char answer = 'Y';
	cout << "\nEnter a Name and age entry\n";
	while (toupper(answer) == 'Y') {
		pair<const Name, size_t> entry = get_entry();
		auto pr = people.insert(entry);
		if (!pr.second) {// 만약존재한다면{
			cout << "Key \"" << pr.first->first << "\" already present. Do want to update the age Y or N?";
			cin >> answer;
			if (toupper(answer) == 'Y') {
				pr.first->second = entry.second;
			}
		}
		// 입력할 항목이 더있는가?
		cout << "Do you want to enter another entry(Y or N)?";
		cin >> answer;
	}
	cout << "\nThe map now contains the following entries:\n";
	list_entries(people);
	system("pause");
}