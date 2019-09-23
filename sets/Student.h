#pragma once
#include<string>
#include<ostream>
#include<vector>
class Student {
private:
	std::string first{};
	std::string second{};
public:
	Student(const std::string& name1, const std::string& name2) :first(name1), second(name2) {};
	Student(Student& student) : first((student.first)), second((student.second)) {}
	Student(Student&& student): first(std::move(student.first)), second(std::move(student.second)) {}
	Student() {}
	bool operator<(const Student& student) const {
		return second < student.second || (second == student.second && first < student.first);
	}
	friend std::ostream& operator<<(std::ostream& out, const Student& studnet);
};

inline std::ostream& operator<<(std::ostream& out, const Student& studnet) {
	out << studnet.first + " " << studnet.second;
	return out;
}
using Students = std::vector<Student>;
Students create_students() {
	Students students;
	std::string first_name[]{ "Ann", " Jim", "Eve","Dan","Ted" };
	std::string second_name[]{ "Smith", " Jones", "Howe","Watt","Beck" };

	for (const auto& first : first_name) {
		for (const auto& second : second_name) {
			students.emplace_back(first, second);
		}
	}
	return students;
}