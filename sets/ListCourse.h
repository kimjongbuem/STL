#pragma once
#include<iostream>
#include<string>
#include<set>
#include<algorithm>
#include<iterator>
#include"Student.h"

using Subject = std::string;
using Group = std::set<Student>;
using Course = std::pair<Subject, Group>;

class List_Course {
public:
	void operator()(const Course& course) {
		std::cout << "\n\n" << course.first << course.second.size() << std::endl;
		std::copy(std::begin(course.second), std::end(course.second), std::ostream_iterator<Student>(std::cout, "  "));
	}
};