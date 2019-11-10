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

	//�ŷ��� ù ��° ��Ʈ�� �о�´� //
	std::copy(std::istream_iterator<Transaction>{std::cin}, std::istream_iterator<Transaction>{}, std::back_inserter(transactions));
	std::cin.clear();

	//ù ��° ��Ʈ�� ���� ��ȣ ������������ �����Ѵ�,
	std::stable_sort(std::begin(transactions), std::end(transactions), std::greater<>());

	//�ŷ� ���//
	std::cout << "First set of transactions after sorting...\n";
	std::copy(std::begin(transactions), std::end(transactions), std::ostream_iterator<Transaction>{std::cout, "\n"});
	
	//�� ��° ��Ʈ�� �о�´�,
	std::cout << "\nEnter more transaction:\n";
	std::copy(std::istream_iterator<Transaction>{std::cin}, std::istream_iterator<Transaction>{}, std::back_inserter(transactions));
	std::cin.clear();

	//�ŷ� ���//
	std::cout << "\nSoted first set of transactions with second set appended...\n";
	std::copy(std::begin(transactions), std::end(transactions), std::ostream_iterator<Transaction>{std::cout, "\n"});

	// ���� // 
	auto iter = std::is_sorted_until(std::begin(transactions), std::end(transactions), std::greater<>());
	std::stable_sort(iter, std::end(transactions), std::greater<>());

	// �ŷ� ���//
	std::cout << "\nSoted first set of transactions with second set appended...\n";
	std::copy(std::begin(transactions), std::end(transactions), std::ostream_iterator<Transaction>{std::cout, "\n"});

	//���ο��� �ŷ��� ����
	std::inplace_merge(std::begin(transactions), iter, std::end(transactions), std::greater<>());

	// �ŷ� ���//
	std::cout << "\nMerged Transactions...\n";
	std::copy(std::begin(transactions), std::end(transactions), std::ostream_iterator<Transaction>{std::cout, "\n"});

	//�ʿ��Ҷ� Account ��ü�� �����ϸ鼭 �ŷ��� ó���Ѵ�.
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

	//���¸� ���� �����̳ʷ� �����Ѵ�//
	std::vector<Account> accs;
	for (const auto& pr : accounts) accs.push_back(pr.second);

	//�̸� ������ ������ �Ŀ� ���µ��� ����Ѵ�.
	std::stable_sort(std::begin(accs), std::end(accs), Compare_Name());
	std::copy(std::begin(accs), std::end(accs), std::ostream_iterator<Account>{std::cout, "\n"});
	system("pause");
}