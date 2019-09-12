#include<iostream>
#include<string>
#include<map>
#include<tuple>
#include<iomanip>
#include<vector>
#include <cctype>
#include<algorithm>
using namespace std;

using Name = pair<string, string>;
using DOB = tuple<size_t, size_t, size_t>;
using Details = tuple<DOB, size_t, string>;
using Element_Type = map<Name, Details>::value_type;

using People = map<Name, Details>;

// 맵 원소를 입력하는 과정//
void get_people(People& people) {
	string first, second;
	size_t month, day, year;
	size_t height;
	string occupation;
	char answer = 'Y';

	while (answer == 'Y') {
		cout << "Enter a first name and a second name: ";
		cin >> ws >> first >> second;

		cout << "Enter height: ";
		cin >> height;


		cout << "Enter date of birth as month day year (integer ): ";
		cin >> month >> day >> year;
		DOB dob{ month, day ,year };

		cout << "Enter occupation: ";
		getline(cin >> ws, occupation, '\n');

		//Name pair와 tuple을 담는 pair를 맵 원소로 내부에서 생성
		people.emplace(make_pair(Name{ first,second }, make_tuple(dob, height, occupation)));

		cout << "Do you want to enter another?(Y or N)";
		cin >> answer;
		answer = toupper(answer);
	}
}

void list_DOB_Job(const People& people) {
	DOB dob;
	string occupation = {};
	cout << '\n';
	for (auto iter = begin(people); iter != end(people); ++iter) {
		tie(dob, ignore, occupation) = iter->second;
		cout << setw(20) << left << (iter->first.first + " " + iter->first.second) << "DOB : " << right << setw(2) <<
			get<0>(dob) << "-" << setw(2) << setfill('0') << get<1>(dob) << "-" << setw(4) <<
			get<2>(dob) << setfill(' ') << " Occupation: " << occupation << endl;
	}
}

template<typename Compare>
void list_sorted_people(const People& people, Compare comp) {
	vector<const Element_Type*> folks;
	for (const auto&pr : people) {
		folks.push_back(&pr);
	}
	// 포인터로 원소들을 비교하는 람다 
	auto ptr_comp = [&comp](const Element_Type* pr1, const Element_Type* pr2)->bool {return comp(*pr1, *pr2); };
	DOB dob; int height; string occupation;
	sort(begon(people), end(people), ptr_comp);
	for (auto& p : folks) {
		tie(dob, height, occupation) = p->second;
		cout << setw(20) << left << (p->first.first+ " " + p->first.second) << "DOB : " << right << setw(2) <<
			get<0>(dob) << "-" << setw(2) << setfill('0') << get<1>(dob) << "-" << setw(4) <<
			get<2>(dob) << setfill(' ')<<"Height : "<< height << " Occupation: " << occupation << endl;
	}
}


int main() {
	map<Name, Details> people;
	get_people(people);
	
	cout << "\nThe DOB & jobs are:\n";
	list_DOB_Job(people);

	// 사람들을 키로 비교하는것으로 정의하자
	 bool(*comp)(const Element_Type& pr1, const Element_Type& pr2) = [](const Element_Type& pr1, const Element_Type& pr2)-> bool {
		return get<1>(pr1.second) < get<1>(pr2.second);
	};

	 cout << "\nThe Peolle in height order are : \n";
	 list_sorted_people(people,comp);
	 system("pause");
}