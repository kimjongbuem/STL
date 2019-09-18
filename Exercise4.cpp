#include<iostream>
#include<map>
#include<string>
#include<unordered_map>
#include<cctype>
using namespace std;
using course = string;
using student_name = string;

void showCoureAndSchoolList(const map<course,student_name>& map, const course key) {
	int count = map.count(key);
	auto finding = map.find(key);
	if (finding == end(map)) {
		cout << "�ش� �а�������"<<key <<"�� �����ϴ�." << endl;
		return;
	}
	int i = 0;
	cout << "Course : " << key<<": ";
	auto iter = map.find(key);
	cout << iter->second << " ";
}
void showCoureAndSchoolList(const multimap<student_name, course>& map, const student_name key) {
	auto finding = map.find(key);
	if (finding == end(map)) {
		cout << "�ش� �л�" <<key <<"�� �����ϴ�."  << endl;
		return;
	}
	int i = 0;
	cout << "Student Name : " << key << ": ";
	auto pr = map.equal_range(key);
	for(auto iter = pr.first; iter != pr.second; iter++) cout << iter->second << " ";
}
int main() {
	/*1. ������ ������ ����� �� �������� �л����� �̸��� �����Ҽ� �ִ� ���α׷��� map<k,t> �����̳ʸ� ����� �������� ���α׷���
	������ �߰��ϰų� �����Ҽ� �ְ� ��� ������ ����Ҽ� �־���Ѵ�.
	���ǿ� �ִ� �л����� ����� �����ü� �־���ϰ�, ���� �б��̸����� �˻��Ҽ� �־���Ѵ�.

	*/

	//map<course, student_name> sc;
	//
	//while (true) {
	//	int choice;
	//	string c, s;
	//	cout << "�а�/�л�Ȯ�� (2) �бް� �л� �߰��ϽǰŸ� (1) �ƴҰŸ� (0):   ";
	//	cin >> choice;

	//	if (choice == 1) {
	//		cout << "�а��� �ش� �а� �л��� �Է��ϼ���:";
	//		cin >> ws >> c >> s;
	//		if (sc.count(c)) sc.insert(sc.find(c),make_pair(c,s));
	//		else sc.emplace(make_pair(c, s));
	//	}
	//	else if (choice == 2) {
	//		cout << "�ҷ��� �л����� �а����� �Է����ּ���:";
	//		cin >> ws >> c;
	//		showCoureAndSchoolList(sc, c);
	//	}
	//	else break;
	//}

	/*2 �л��� ����� ���� ����� �����Ҽ� �ְ�, �л� �̸��� �ߺ��� ����ϴ� ���α׷��� multimap<k,t>�����̳ʸ� ����ؼ� �������� ���ҵ��� ������������ �����ϸ�
	�л����� �߰��ϰų� �����Ҽ� �־�� �ϰ� �л��� �л��� �����ϴ� ������ ����ؾ��ϸ�, �л��� ��� ������ �л��̸����� �˻��Ҽ� �־���Ѵ�.
	
	*/
	/*
	/**/
	system("pause");
}