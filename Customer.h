#pragma once
class Customer {
private:
	size_t service_t = 0; // ������� ���� �ð�
public:
	explicit Customer(size_t time = 10) :service_t(time) {}
	Customer& time_decrement() {
		if (service_t > 0) {
			--service_t;
			return *this;
		}
	}
	bool done() const {
		return service_t == 0;
	}
};