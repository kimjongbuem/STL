#include<iostream>
#include<map>
#include<string>
#include<unordered_map>
#include<cctype>
#include<random>
#include<queue>
#include<iomanip> // 스트림조작자?
#include<algorithm>
#include<numeric>
using namespace std;
using course = string;
using student_name = string;
using Address = string;
using Phone = string;

/*3 키보드에서 계산대 개수를 입력받아 슈퍼마켓을 시뮬레이션하는 프로그램.
	각 계산대는 map 컨테이너를 원소로 표현, 계산대 아이디를 키로사용, 계산대의 대기열은 키와 연관된 객체로 사용하라
	그리고 고객이 도착하는 간격이나 계산대의 점유하는 시간은 일정하지 않고 랜덤. 키보드에서 입력받은 시간이 지나면
	각 계산대의 최대 대기열길이와 평균 대기시간을 출력하라.

*/
class Name {
	string name;
public:
	Name(string name) : name(name) {};
	bool operator==(const Name& names) const { return name == names.name; }
	string getName() const { return name; }
};
class NameHash {
	size_t operator()(const Name& name) const {
		return hash<string>()(name.getName());
	}
};
using Person = tuple<Name, Address, Phone>;
void histogram(const vector<int>& v, int min)
{
	string bar(60, '*');
	for (size_t i = 0; i < v.size(); i++) {
		cout << setw(3) << i + min << " "
			<< setw(4) << v[i] << " "
			<< bar.substr(0, v[i]) <<
			(v[i] > static_cast<int>(bar.size()) ? "..." : "") << endl;
	}
}
class Customer
{
private:
	size_t service_t = 0;
public:
	explicit Customer(size_t time = 10) : service_t(time){}
	Customer& time_decrement() {
		if (service_t > 0) --service_t;
		return *this;
	}
	bool done() const {
		return service_t == 0;
	}
};
class Counter {
private:
	queue<Customer> customers;
public:
	void add(const Customer& customer) {
		customers.push(customer);
	}
	size_t getLength() const { return customers.size(); }
	void time_increment() {
		if (!customers.empty()) {
			if (customers.front().time_decrement().done())
				customers.pop();
		}
	}
	bool operator<(const Counter& other) const { return getLength() < other.getLength(); }
	bool operator>(const Counter& other) const { return getLength() > other.getLength(); }
};
//less<>::operator()() const {
//
//}
void showCoureAndSchoolList(const map<course,student_name ,less<>>& map, const course key) {
	int count = map.count(key);
	auto finding = map.find(key);
	if (finding == end(map)) {
		cout << "해당 학과에대한"<<key <<"이 없습니다." << endl;
		return;
	}
	int i = 0;
	cout << "Course : " << key<<": ";
	auto iter = map.find(key);
	cout << iter->second << " ";
}
void showCoureAndSchoolList(const multimap<student_name, course ,less<>>& map, const student_name key) {
	auto finding = map.find(key);
	if (finding == end(map)) {
		cout << "해당 학생" <<key <<"이 없습니다."  << endl;
		return;
	}
	int i = 0;
	cout << "Student Name : " << key << ": ";
	auto pr = map.equal_range(key);
	for(auto iter = pr.first; iter != pr.second; iter++) cout << iter->second << " ";
}
int main() {
	/*1. 임의의 수업을 만들고 각 수업에는 학생들의 이름을 저장할수 있는 프로그램을 map<k,t> 컨테이너를 사용해 구현하자 프로그램은
	수업을 추가하거나 삭제할수 있고 모든 수업을 출력할수 있어야한다.
	교실에 있는 학생들의 명단을 가져올수 있어야하고, 같은 학급이름으로 검색할수 있어야한다.

	*/

	//map<course, student_name> sc;
	//
	//while (true) {
	//	int choice;
	//	string c, s;
	//	cout << "학과/학생확인 (2) 학급과 학생 추가하실거면 (1) 아닐거면 (0):   ";
	//	cin >> choice;

	//	if (choice == 1) {
	//		cout << "학과와 해당 학과 학생을 입력하세요:";
	//		cin >> ws >> c >> s;
	//		if (sc.count(c)) sc.insert(sc.find(c),make_pair(c,s));
	//		else sc.emplace(make_pair(c, s));
	//	}
	//	else if (choice == 2) {
	//		cout << "불러올 학생들의 학과명을 입력해주세요:";
	//		cin >> ws >> c;
	//		showCoureAndSchoolList(sc, c);
	//	}
	//	else break;
	//}

	/*2 학생이 등록한 수업 목록을 저장할수 있고, 학생 이름의 중복을 허용하는 프로그램을 multimap<k,t>컨테이너를 사용해서 구현하자 원소들은 내림차순으로 진행하며
	학생들을 추가하거나 삭제할수 있어야 하고 학생과 학생이 수강하는 수업을 출력해야하며, 학생이 듣는 수업을 학생이름으로 검색할수 있어야한다.

	*/
	/*multimap<student_name, course, less<>> mm;
	while (true) {
		int choice;
		string c, s;
		cout << "학과/학생확인 (2) 학급과 학생 추가하실거면 (1) 아닐거면 (0) 학생 삭제(3):   ";
		cin >> choice;

		if (choice == 1) {
			cout << "학과와 해당 학과 학생을 입력하세요:";
			cin >> ws >> c >> s;
			if (mm.count(c)) mm.insert(mm.find(c),make_pair(c,s));
			else mm.emplace(make_pair(c, s));
		}
		else if (choice == 2) {
			cout << "불러올 학생들의 학과명을 입력해주세요:";
			cin >> ws >> c;
			showCoureAndSchoolList(mm, c);
		}
		else if (choice == 3) {
			cout << "삭제할 학생 이름을 입력해주세요:";
			cin >> ws >> s;
			mm.erase(s);
			showCoureAndSchoolList(mm, s);
		}
		else break;
	}*/
	/*3 키보드에서 계산대 개수를 입력받아 슈퍼마켓을 시뮬레이션하는 프로그램.
		각 계산대는 map 컨테이너를 원소로 표현, 계산대 아이디를 키로사용, 계산대의 대기열은 키와 연관된 객체로 사용하라
		그리고 고객이 도착하는 간격이나 계산대의 점유하는 시간은 일정하지 않고 랜덤. 키보드에서 입력받은 시간이 지나면
		각 계산대의 최대 대기열길이와 평균 대기시간을 출력하라.

	*/
	//map<size_t, Counter> counters;
	//random_device random_n;
	//// 최소최대 체크아웃 시간 설정 분단위 //
	//int service_t_min = 2, service_t_max = 15;
	//uniform_int_distribution<int> service_t_d{ service_t_min, service_t_max };
	//// 마트 개점 시에 고객의 최소, 최대 숫자 설정 //
	//int min_customers = 15, max_customers = 20;
	//uniform_int_distribution<int> n_1st_customer_d{ min_customers, max_customers };
	////고객이 도착하는 시간 간격의 최소, 최대 설정
	//int min_arr_interval = 1, max_arr_interval = 5;
	//uniform_int_distribution<int> arrival_interval_d{ min_arr_interval, max_arr_interval };

	//size_t cnt;
	//cout << "마트 계산대 개수 입력 : ";
	//cin >> cnt;
	//if (!cnt) {
	//	cout << "해당 계산대 개수는 최소 1이니 1로 설정함." << endl;
	//	cnt = 1;
	//}
	//vector<int> service_times(service_t_max - service_t_min + 1);

	////마트 개점할 때 기다리는 고객을 추가 함 //
	//int count = n_1st_customer_d(random_n);
	//cout << "마트 개점시에 대기 고객 수: " << count << endl;
	//int added = 0;
	//int service_t = 0;
	//while (added++ < cnt) {
	//	counters.emplace(pair<size_t, Counter>(added, Counter()));
	//}
	//added = 0;
	//while (added++ < count) {
	//	service_t = service_t_d(random_n);
	//	int val = 1;
	//	for (int i = 2; i <= cnt; i++)
	//	{
	//		if (counters.find(val)->second.getLength() > counters.find(i)->second.getLength())
	//			val = i;
	//	}
	//	counters.find(val)->second.add(Customer(service_t));
	//
	//	++service_times[service_t - service_t_min];
	//}

	//size_t time = 0;
	//const size_t total_time = 600; size_t longest_q = 0;
	//int new_cust_interval = arrival_interval_d(random_n);
	//// 다음 고객이 도착할 때 까지의 시간 간격 //
	//while (time < total_time) {
	//	++time;
	//	// 도착 간격이 0일때 새 고객이 도착함
	//	if (--new_cust_interval == 0) {
	//		int val = 1;
	//		for (int i = 2; i <= cnt; i++)
	//		{
	//			if (counters.find(val)->second.getLength() > counters.find(i)->second.getLength())
	//				val = i;
	//		}
	//		counters.find(val)->second.add(Customer(service_t));
	//		++service_times[service_t - service_t_min];
	//	}


	//	// 가장 긴 대기열의 기록을 업데이트 //
	//	for (auto& checkout : counters) {
	//		longest_q = max(longest_q, checkout.second.getLength());
	//		new_cust_interval = arrival_interval_d(random_n);
	//	}

	//	// 계산대에서의 시간 업데이트 - 각 큐에 첫번째 고객을 처리함 //
	//	for (auto& checkout : counters) {
	//		checkout.second.time_increment();
	//	}
	//}

	//cout << "최대 대기열의 길이 = " << longest_q << endl;
	//cout << "\n서비스 시간 막대 그래프\n";
	//histogram(service_times, service_t_min);
	//cout << "오늘 총 고객 수 : " << accumulate(begin(service_times), end(service_times), 0) << endl;
	/*
	4....
		이름 주소 전화번호를 저장하는 Person객체에 대한 클래스를 정의해라 이름을 키로 사용해서 Person객체를 저장하는 용도
		unordered_multimap 컨테이너를 사용하라 주소, 전화번호, 이름 검색하는 기능과 아ㅣ름을 오름차순으로 Person객체를 모두 출력하는 기능
	*/

	//unordered_multimap<Name, Person,NameHash>persons{8, NameHash()}; // name address, phone
	unordered_multimap<string, Person>persons;// { 8, NameHash() };
	while (true) {
		int choice;
		string name, address, phone;
		cout << "1. 사람 추가하기 2. 추가한 사람들 전체 보기 3. 종료  ";
		cin >> choice;
		if (choice == 1) {
			cout << "이름, 주소 , 폰번호 입력해주세요! : ";
			cin >> ws >> name >> address >> phone;
			/*if (persons.count(name)) persons.insert(make_tuple(name, address, phone));
			else*/ persons.emplace(name, make_tuple(name, address, phone));
		}
		else if (choice == 2) {
			auto func = [&persons]() {
				for (auto iter = begin(persons); iter != end(persons); iter++) {
					cout << "name : " << iter->first << " address: " << get<1>(iter->second) << " phone" << get<2>(iter->second) << endl;
				}
			};
			func();
		}
		else if (choice == 3) break;
	}
	
	
	system("pause");
}