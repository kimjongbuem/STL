// Ex5_01.cpp
// 과목에 학생들을 등록하기
#include <iostream>                              // 표준 스트림
#include <string>                                // string 클래스
#include <map>                                   // map 컨테이너
#include <set>                                   // set 컨테이너
#include <vector>                                // vector 컨테이너
#include <random>                                // 랜덤 숫자 생성
#include <algorithm>                             // for_each(), count_if()
#include "Student.h"
#include "ListCourse.h"

using std::string;
using Distribution = std::uniform_int_distribution<size_t>;
using Subject = string;
using Subjects = std::vector<Subject>;
using Group = std::set<Student>;
using Students = std::vector<Student>;
using Course = std::pair<Subject, Group>;
using Courses = std::map<Subject, Group>;

static std::default_random_engine gen_value;

Group make_group(const Students& students, size_t group_size, const Distribution& choose_student) {
	Group group;
	while (group.size() < group_size) {
		group.insert(students[choose_student(gen_value)]);
	}
	return group;
}

int main() {
	Students students = create_students();
	Subjects subjects{ "Biology", "Physics", "Chemistry", "Mathematics", "Astronomy",
					   "Drama", "Politics", "Philosophy", "Economics" };
	Courses courses;                                         // 과목 키를 갖는 전체 코스

	size_t min_subjects{ 4 };                                 // 학생당 최소 과목 수
	size_t min_group{ min_subjects };                         // 코스당 최소 학생 수

	// 코스당 최대 학생 수
	size_t max_group{ (students.size()*min_subjects) / subjects.size() };
	// 각 과목을 선택한 학생들의 그룹을 생성한다
	Distribution group_size{ min_group, max_group };          // 코스당 학생들을 위한 분포
	Distribution choose_student{ 0, students.size() - 1 };    // 랜덤 학생 선택기

	for (const auto& subject : subjects)
		courses.emplace(subject, make_group(students, group_size(gen_value), choose_student));

	Distribution choose_course{ 0, subjects.size() - 1 };     // 랜덤 코스 선택기
	
	for (const auto& student : students)
	{ // 최소 수강 과목을 만족하는지 검증한다

	  // 학생이 등록한 과목 수를 카운트
		size_t course_count = std::count_if(std::begin(courses), std::end(courses),
			[&student](const Course& course) { return course.second.count(student); });
		if (course_count >= min_subjects) continue;             // 최소 수강을 만족하면 다음 학생으로

		// 최소 수강을 미달한 과목 수
		size_t additional{ min_subjects - course_count };       // 등록이 필요한 과목 수
		if (!course_count)                                      // 선택한 과목이 없다면...
			std::cout << student << " is work-shy, having signed up for NO Subjects!\n";
		else                                                   // 일부 과목만 등록했다면...
			std::cout << student << " is only signed up for " << course_count << " Subjects!\n";

		std::cout << "Registering " << student << " for " << additional
			<< " more course" << (additional > 1 ? "s" : "") << ".\n\n";

		// 최소 수강 요건을 맞추기 위해 과목을 추가로 등록
		while (course_count < min_subjects)
			if ((courses.find(subjects[choose_course(gen_value)])->second.insert(student)).second) ++course_count;
	}

	// 각 코스에 참여하는 학생들을 출력
	std::for_each(std::begin(courses), std::end(courses), List_Course());
	std::cout << std::endl;
	system("pause");
}