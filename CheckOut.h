#pragma once
#include <queue>
#include "Customer.h"
using namespace std;
class CheckOut {
private:
	queue<Customer> customers;
public:
	void add(const Customer& customer) {
		customers.push(customer);
	}
	size_t glength() const { return customers.size(); }
	void time_increment() {
		if (customers.empty()) {
			if (customers.front().time_decrement().done()) {
				customers.pop();
			}
		}
	}
	bool operator<(const CheckOut& other) const { return glength() < other.glength(); }
	bool operator>(const CheckOut& other) const { return glength() > other.glength(); }
};