#include<iostream>
#include<iomanip> // 스트림조작자?
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
	// 최소최대 체크아웃 시간 설정 분단위 //
	int service_t_min = 2, service_t_max = 15;
	uniform_int_distribution<int> service_t_d{ service_t_min, service_t_max };
	// 마트 개점 시에 고객의 최소, 최대 숫자 설정 //
	int min_customers = 15, max_customers = 20;
	uniform_int_distribution<int> n_1st_customer_d{ min_customers, max_customers };
	//고객이 도착하는 시간 간격의 최소, 최대 설정
	int min_arr_interval = 1, max_arr_interval = 5;
	uniform_int_distribution<int> arrival_interval_d{ min_arr_interval, max_arr_interval };

	size_t n_checkOuts = 0;
	cout << "마트 계산대 개수 입력"; cin >> n_checkOuts;
	if (!n_checkOuts) {
		cout << "계산대 개수는 1이상이여야 하니 1로 설정함" << endl;
		n_checkOuts = 1;
	}

	vector<CheckOut> checkOuts{ n_checkOuts };
	vector<int> service_times(service_t_max - service_t_min + 1);

	//마트 개점할 때 기다리는 고객을 추가 함 //
	int count = n_1st_customer_d(random_n);
	cout << "마트 개점시에 대기 고객 수: " << count << endl;
	int added = 0;
	int service_t = 0;
	while (added++ < count) {
		service_t = service_t_d(random_n);
		min_element(begin(checkOuts), end(checkOuts))->add(Customer(service_t));
		++service_times[service_t - service_t_min];
	}
	//cout << "\n서비스 시간 막대 그래프\n";
	//histogram(service_times, service_t_min);
	size_t time = 0;
	const size_t total_time = 600; size_t longest_q = 0;
	int new_cust_interval = arrival_interval_d(random_n);
	// 다음 고객이 도착할 때 까지의 시간 간격 //
	while (time < total_time) {
		++time;
		// 도착 간격이 0일때 새 고객이 도착함
		if (--new_cust_interval == 0) {
			service_t = service_t_d(random_n); // 고객 서비스 시간을 무작위로 설정
			min_element(begin(checkOuts), end(checkOuts))->add(Customer(service_t));
			++service_times[service_t - service_t_min];
		}
	

	// 가장 긴 대기열의 기록을 업데이트 //
	for (auto& checkout : checkOuts) {
		longest_q = max(longest_q, checkout.glength());
		new_cust_interval = arrival_interval_d(random_n);
	}

	// 계산대에서의 시간 업데이트 - 각 큐에 첫번째 고객을 처리함 //
	for (auto& checkout : checkOuts) {
		checkout.time_increment();
	}
	}

	cout << "최대 대기열의 길이 = " << longest_q << endl;
	cout << "\n서비스 시간 막대 그래프\n";
	histogram(service_times, service_t_min);
	cout << "오늘 총 고객 수 : " << accumulate(begin(service_times), end(service_times), 0) << endl;
	int val;
	cin >> val;
}