#include<iostream>
#include<string>
#include<algorithm>
#include<functional>
#include<vector>
#include<utility>
#include<map>
#include<iterator>
#include"Account.h"
#include"Transaction.h"

using std::string;
using first_name = string;
using second_name = string;
using Name = std::pair<first_name, second_name>;
using Account_number = size_t;

Name get_holder_name(Account_number number) {
	std::cout << "Enter the holder's first and second names for account number " << number << ":";
	string first{}; string second{};
	std::cin >> first >> second;
	return std::make_pair(first, second);
}

int main() {
	std::vector<Transaction> transactions;

	std::cout << "Enter each Transaction as:\n" << " 5 digit account number	amount	credit(true or false).\n"
		<< "Enter Ctrl + Z to end.\n";

	//거래의 첫 번째 세트를 읽어온다 //
	std::copy(std::istream_iterator<Transaction>{std::cin}, std::istream_iterator<Transaction>{}, std::back_inserter(transactions));
	std::cin.clear();

	//첫 번째 세트를 계좌 번호 내림차순으로 정렬한다,
	std::stable_sort(std::begin(transactions), std::end(transactions), std::greater<>());

	//거래 출력//
	std::cout << "First set of transactions after sorting...\n";
	std::copy(std::begin(transactions), std::end(transactions), std::ostream_iterator<Transaction>{std::cout, "\n"});
	
	//두 번째 세트를 읽어온다,
	std::cout << "\nEnter more transaction:\n";
	std::copy(std::istream_iterator<Transaction>{std::cin}, std::istream_iterator<Transaction>{}, std::back_inserter(transactions));
	std::cin.clear();

	//거래 출력//
	std::cout << "\nSoted first set of transactions with second set appended...\n";
	std::copy(std::begin(transactions), std::end(transactions), std::ostream_iterator<Transaction>{std::cout, "\n"});

	// 정렬 // 
	auto iter = std::is_sorted_until(std::begin(transactions), std::end(transactions), std::greater<>());
	std::stable_sort(iter, std::end(transactions), std::greater<>());

	// 거래 출력//
	std::cout << "\nSoted first set of transactions with second set appended...\n";
	std::copy(std::begin(transactions), std::end(transactions), std::ostream_iterator<Transaction>{std::cout, "\n"});

	//내부에서 거래를 병합
	std::inplace_merge(std::begin(transactions), iter, std::end(transactions), std::greater<>());

	// 거래 출력//
	std::cout << "\nMerged Transactions...\n";
	std::copy(std::begin(transactions), std::end(transactions), std::ostream_iterator<Transaction>{std::cout, "\n"});

	//필요할때 Account 객체를 생성하면서 거래를 처리한다.
	std::map<Account_number, Account> accounts;
	for (const auto& tr : transactions) {
		Account_number number = tr.get_acc_number();
		auto iter = accounts.find(number);
		if (iter == std::end(accounts)) iter = accounts.emplace(number, Account{ number, get_holder_name(number) }).first;

		if (iter->second.apply_transaction(tr)) {
			auto name = iter->second.get_name();
			std::cout << "\nAccount number" << number << " for " << name.first << " " << name.second << " is overdawn\n" <<
				"The concept is that you bank with us - not the other way roundm so fix it!\n" << std::endl;
		}
	}

	//계좌를 벡터 컨테이너로 복제한다//
	std::vector<Account> accs;
	for (const auto& pr : accounts) accs.push_back(pr.second);

	//이름 순으로 정렬한 후에 계좌들을 출력한다.
	std::stable_sort(std::begin(accs), std::end(accs), Compare_Name());
	std::copy(std::begin(accs), std::end(accs), std::ostream_iterator<Account>{std::cout, "\n"});
	system("pause");
}