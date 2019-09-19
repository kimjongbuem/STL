#include<iostream>
#include<map>
#include<string>
#include<unordered_map>
#include<cctype>
#include<random>
#include<queue>
#include<iomanip> // ��Ʈ��������?
#include<algorithm>
#include<numeric>
using namespace std;
using course = string;
using student_name = string;

/*3 Ű���忡�� ���� ������ �Է¹޾� ���۸����� �ùķ��̼��ϴ� ���α׷�.
	�� ����� map �����̳ʸ� ���ҷ� ǥ��, ���� ���̵� Ű�λ��, ������ ��⿭�� Ű�� ������ ��ü�� ����϶�
	�׸��� ���� �����ϴ� �����̳� ������ �����ϴ� �ð��� �������� �ʰ� ����. Ű���忡�� �Է¹��� �ð��� ������
	�� ������ �ִ� ��⿭���̿� ��� ���ð��� ����϶�.

*/

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
void showCoureAndSchoolList(const map<course,student_name ,less<>>& map, const course key) {
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
void showCoureAndSchoolList(const multimap<student_name, course ,less<>>& map, const student_name key) {
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
	/*multimap<student_name, course, less<>> mm;
	while (true) {
		int choice;
		string c, s;
		cout << "�а�/�л�Ȯ�� (2) �бް� �л� �߰��ϽǰŸ� (1) �ƴҰŸ� (0) �л� ����(3):   ";
		cin >> choice;

		if (choice == 1) {
			cout << "�а��� �ش� �а� �л��� �Է��ϼ���:";
			cin >> ws >> c >> s;
			if (mm.count(c)) mm.insert(mm.find(c),make_pair(c,s));
			else mm.emplace(make_pair(c, s));
		}
		else if (choice == 2) {
			cout << "�ҷ��� �л����� �а����� �Է����ּ���:";
			cin >> ws >> c;
			showCoureAndSchoolList(mm, c);
		}
		else if (choice == 3) {
			cout << "������ �л� �̸��� �Է����ּ���:";
			cin >> ws >> s;
			mm.erase(s);
			showCoureAndSchoolList(mm, s);
		}
		else break;
	}*/
	/*3 Ű���忡�� ���� ������ �Է¹޾� ���۸����� �ùķ��̼��ϴ� ���α׷�.
		�� ����� map �����̳ʸ� ���ҷ� ǥ��, ���� ���̵� Ű�λ��, ������ ��⿭�� Ű�� ������ ��ü�� ����϶�
		�׸��� ���� �����ϴ� �����̳� ������ �����ϴ� �ð��� �������� �ʰ� ����. Ű���忡�� �Է¹��� �ð��� ������
		�� ������ �ִ� ��⿭���̿� ��� ���ð��� ����϶�.

	*/
	//map<size_t, Counter> counters;
	//random_device random_n;
	//// �ּ��ִ� üũ�ƿ� �ð� ���� �д��� //
	//int service_t_min = 2, service_t_max = 15;
	//uniform_int_distribution<int> service_t_d{ service_t_min, service_t_max };
	//// ��Ʈ ���� �ÿ� ���� �ּ�, �ִ� ���� ���� //
	//int min_customers = 15, max_customers = 20;
	//uniform_int_distribution<int> n_1st_customer_d{ min_customers, max_customers };
	////���� �����ϴ� �ð� ������ �ּ�, �ִ� ����
	//int min_arr_interval = 1, max_arr_interval = 5;
	//uniform_int_distribution<int> arrival_interval_d{ min_arr_interval, max_arr_interval };

	//size_t cnt;
	//cout << "��Ʈ ���� ���� �Է� : ";
	//cin >> cnt;
	//if (!cnt) {
	//	cout << "�ش� ���� ������ �ּ� 1�̴� 1�� ������." << endl;
	//	cnt = 1;
	//}
	//vector<int> service_times(service_t_max - service_t_min + 1);

	////��Ʈ ������ �� ��ٸ��� ���� �߰� �� //
	//int count = n_1st_customer_d(random_n);
	//cout << "��Ʈ �����ÿ� ��� �� ��: " << count << endl;
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
	//// ���� ���� ������ �� ������ �ð� ���� //
	//while (time < total_time) {
	//	++time;
	//	// ���� ������ 0�϶� �� ���� ������
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


	//	// ���� �� ��⿭�� ����� ������Ʈ //
	//	for (auto& checkout : counters) {
	//		longest_q = max(longest_q, checkout.second.getLength());
	//		new_cust_interval = arrival_interval_d(random_n);
	//	}

	//	// ���뿡���� �ð� ������Ʈ - �� ť�� ù��° ���� ó���� //
	//	for (auto& checkout : counters) {
	//		checkout.second.time_increment();
	//	}
	//}

	//cout << "�ִ� ��⿭�� ���� = " << longest_q << endl;
	//cout << "\n���� �ð� ���� �׷���\n";
	//histogram(service_times, service_t_min);
	//cout << "���� �� �� �� : " << accumulate(begin(service_times), end(service_times), 0) << endl;
	system("pause");
}