#include <iostream>
#include<string>
#include<iomanip> // stream 
#include<string>
#include<unordered_set>
#include<algorithm> // copy, max, find_if(), for_each
#include<iterator> // ostream_iterator
#include "Name.h"
using Names = std::unordered_multiset<Name, Name_Hash>;
using namespace std;

void make_friends(Names& names) {
	vector<string> first_name = { "john","john","john","jhan","jhan" ,"jim","jim" ,"jean" };
	vector<string> second_name = { "Smith", "jones", "jones","Hackenbush","Szcygiel" };

	for (const auto& name1 : first_name) {
		for (const auto& name2 : second_name) {
			names.emplace(name1, name2);
		}
	}
}

void list_buckets(const Names& names) {
	for (size_t n_buckets = 0; n_buckets < names.bucket_count(); ++n_buckets) {
		cout << "Bucket " << n_buckets << " :\n";
		copy(names.begin(n_buckets), names.end(n_buckets), std::ostream_iterator<Name>(cout, " "));
		cout << endl;
	}
}

int main() {
	Names pals{ 8 };
	pals.max_load_factor(8.0); // 버킷당 최대 원소의 개수 평균
	make_friends(pals);
	list_buckets(pals);

	// jhon smith의 친구 출력 //
	Name js{ "john","Smith" };
	cout << "\nThere are " << pals.count(js) << js << "'s.\n" << endl;

	pals.erase(js);

	while (true) {
		auto iter = std::find_if(begin(pals), end(pals), [](const Name& name) {
			return name.get_second() == "Hackenbush";});
		if (iter == end(pals)) break;
		pals.erase(iter);
	}
	size_t max_length = 0;
	std::for_each(begin(pals), end(pals), [&max_length](const Name name) {
		max_length = std::max(max_length, name.get_length());
	});

	size_t count = 0;
	size_t per_line = 6;
	for (const auto& pal :pals)
	{
		cout << setw(max_length + 2) << left << pal;
		if ((++count % per_line) == 0)cout << "\n";
	}
	cout << endl;
	system("pause");
}