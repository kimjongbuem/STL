#include<iostream>
#include<iomanip> // ��Ʈ��������?
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<random>

#include"Customer.h"
#include"CheckOut.h"

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

int main() {
	random_device random_n;
	// �ּ��ִ� üũ�ƿ� �ð� ���� �д��� //
	int service_t_min = 2, service_t_max = 15;
	uniform_int_distribution<int> service_t_d{ service_t_min, service_t_max };
	// ��Ʈ ���� �ÿ� ���� �ּ�, �ִ� ���� ���� //
	int min_customers = 15, max_customers = 20;
	uniform_int_distribution<int> n_1st_customer_d{ min_customers, max_customers };
	//���� �����ϴ� �ð� ������ �ּ�, �ִ� ����
	int min_arr_interval = 1, max_arr_interval = 5;
	uniform_int_distribution<int> arrival_interval_d{ min_arr_interval, max_arr_interval };

	size_t n_checkOuts = 0;
	cout << "��Ʈ ���� ���� �Է�"; cin >> n_checkOuts;
	if (!n_checkOuts) {
		cout << "���� ������ 1�̻��̿��� �ϴ� 1�� ������" << endl;
		n_checkOuts = 1;
	}

	vector<CheckOut> checkOuts{ n_checkOuts };
	vector<int> service_times(service_t_max - service_t_min + 1);

	//��Ʈ ������ �� ��ٸ��� ���� �߰� �� //
	int count = n_1st_customer_d(random_n);
	cout << "��Ʈ �����ÿ� ��� �� ��: " << count << endl;
	int added = 0;
	int service_t = 0;
	while (added++ < count) {
		service_t = service_t_d(random_n);
		min_element(begin(checkOuts), end(checkOuts))->add(Customer(service_t));
		++service_times[service_t - service_t_min];
	}
	//cout << "\n���� �ð� ���� �׷���\n";
	//histogram(service_times, service_t_min);
	size_t time = 0;
	const size_t total_time = 600; size_t longest_q = 0;
	int new_cust_interval = arrival_interval_d(random_n);
	// ���� ���� ������ �� ������ �ð� ���� //
	while (time < total_time) {
		++time;
		// ���� ������ 0�϶� �� ���� ������
		if (--new_cust_interval == 0) {
			service_t = service_t_d(random_n); // �� ���� �ð��� �������� ����
			min_element(begin(checkOuts), end(checkOuts))->add(Customer(service_t));
			++service_times[service_t - service_t_min];
		}
	

	// ���� �� ��⿭�� ����� ������Ʈ //
	for (auto& checkout : checkOuts) {
		longest_q = max(longest_q, checkout.glength());
		new_cust_interval = arrival_interval_d(random_n);
	}

	// ���뿡���� �ð� ������Ʈ - �� ť�� ù��° ���� ó���� //
	for (auto& checkout : checkOuts) {
		checkout.time_increment();
	}
	}

	cout << "�ִ� ��⿭�� ���� = " << longest_q << endl;
	cout << "\n���� �ð� ���� �׷���\n";
	histogram(service_times, service_t_min);
	cout << "���� �� �� �� : " << accumulate(begin(service_times), end(service_times), 0) << endl;
	int val;
	cin >> val;
}