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
	if (!count) {
		cout << "해당 학과에대한 학생이 없습니다." << endl;
		return;
	}
	int i = 0;
	cout << "Course : " << key<<": ";
	auto iter = map.find(key);
	cout << iter->second << " ";
}
int main() {
	/*1. 임의의 수업을 만들고 각 수업에는 학생들의 이름을 저장할수 있는 프로그램을 map<k,t> 컨테이너를 사용해 구현하자 프로그램은
	수업을 추가하거나 삭제할수 있고 모든 수업을 출력할수 있어야한다.
	교실에 있는 학생들의 명단을 가져올수 있어야하고, 같은 학급이름으로 검색할수 있어야한다.

	*/

	map<course, student_name> sc;
	
	while (true) {
		int choice;
		string c, s;
		cout << "학과/학생확인 (2) 학급과 학생 추가하실거면 (1) 아닐거면 (0):   ";
		cin >> choice;

		if (choice == 1) {
			cout << "학과와 해당 학과 학생을 입력하세요:";
			cin >> ws >> c >> s;
			if (sc.count(c)) sc.insert(sc.find(c),make_pair(c,s));
			else sc.emplace(make_pair(c, s));
		}
		else if (choice == 2) {
			cout << "불러올 학생들의 학과명을 입력해주세요:";
			cin >> ws >> c;
			showCoureAndSchoolList(sc, c);
		}
		else break;
	}
	system("pause");
}