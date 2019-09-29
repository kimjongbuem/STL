#pragma once
#include<string>
#include<ostream>
#include<istream>

using namespace std;

class Name {
private:
	string first, second;
public:
	Name(const string& name1, const string& name2) : first(name1), second(name2) {}
	Name() = default;

	const string& get_first() const { return first; }
	const string& get_second() const { return second; }

	size_t get_length()const { return first.length() + second.length() + 1; }

	bool operator<(const Name& name) const {
		return second < name.second || (second == name.second && first < name.first);
	}
	bool operator==(const Name& name) const {
		return first == name.first && second == name.second;
	}
	size_t hashs() const { return std::hash<string>()(first + second); }

	friend istream& operator >> (istream& is, Name& name);
	friend ostream& operator << (ostream& is, const Name& name);
};

inline istream& operator >> (istream& is, Name& name) {
	is >> ws >> name.first >> name.second;
	return is;
}
inline ostream& operator << (ostream& os, const Name& name) {
	os << name.first << " " <<  name.second << endl;
	return os;
}

class Name_Hash {
public:
	size_t operator()(const Name& name) const {
		return name.hashs();
	}
};