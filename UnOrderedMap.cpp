#include <iostream>
#include<iomanip> // 스트림조작자
#include<string>
#include<unordered_map>
#include<vector>
#include<algorithm> // max_element

using std::string;
using std::unordered_map;
using std::cout;
using std::endl;

void list_bucket_counts(const std::vector<size_t>& counts) {
	for (size_t i = 0; i < counts.size(); ++i) {
		cout << "Bucket[ " << std::setw(2) << i << "] = " << counts[i] << " ";
		if ((i + 1) % 6 == 0) cout << '\n';
	}
	cout << endl;


}

int main() {
	unordered_map<string, size_t> people;
	float mlf{ people.max_load_factor() }; // 현재 최대로드팩터
	size_t n_buckets{ people.bucket_count() }; // 컨테이너의 버킷개수
	std::vector<size_t> bucket_counts(n_buckets); // 버킷당 저장된 원소 기록하는 벡터
	string name{ "Name" }; // 키
	size_t value{};  // 원소
	size_t max_count = 8192; // 삽입할수 있는 원소 최대개수
	auto lf = people.load_factor(); // 현재 로드팩터

	bool rehash = false;
	while (mlf <= 1.5f) {
		cout << "\n\n************New Container**************" << "\nNumber of Buckets : " << n_buckets
			<< "Maximum load factor: " << mlf << endl;

		for (size_t n_elements{}; n_elements < max_count; ++n_elements) {
			lf = people.load_factor();
			people.emplace("name" + std::to_string(++value), value);
			auto new_count = people.bucket_count(); // 현재의 버킷 개수
			if (new_count > n_buckets) {
				cout << "\nBucket count increased to " << new_count << ". Load factor was " << lf << "and is now" << people.load_factor()
					<< "\nMaxinum elements in a bucket was " << *std::max_element(std::begin(bucket_counts), std::end(bucket_counts)) << endl;
			}
			if (n_buckets <= 64) {
				cout << "Bucket counts before increase were: " << endl;
				list_bucket_counts(bucket_counts);
			}

			n_buckets = new_count; //버킷 개수 업데ㅣ트
			bucket_counts = std::vector<size_t>(n_buckets);// 버켓카운트를 위한 새백터
			rehash = true;
		}
		for (size_t i = 0; i < n_buckets; i++) {
			bucket_counts[i] = people.bucket_size(i);
		}
		if (rehash)
		{
			rehash = false;
			cout << "\nRehashed Container. Buck count is " << n_buckets << ". Element count is " << people.size() << "\nMaxinum element count in a bucket is now"
				<< *std::max_element(begin(bucket_counts), end(bucket_counts)) << endl;
			if (n_buckets <= 64) {
				cout << "\nBucket counts after rehash are:\n";
				list_bucket_counts(bucket_counts);
			}
		}
		cout << "Final state for this container is:\n: " <<
			"Bucket Count: " << people.bucket_count() << "\t Element count: " << people.size()
			<< "\t Maximum element count in a bucket: " << *std::max_element(std::begin(bucket_counts), end(bucket_counts)) << endl;

		value = 1;
		people = unordered_map<string, size_t>();
		n_buckets = people.bucket_count();
		bucket_counts = std::vector<size_t>(n_buckets);
		mlf += 0.25f;
		people.max_load_factor(mlf);
	}
	system("pause");
}