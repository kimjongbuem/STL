#include <stdio.h>
#include<iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
using namespace std;
int main() {
	vector<double> data = { 32.5, 40.2, 36.1, 77.7, 68.8 };
	cout<< "���� �������� ���� �Է� �� ���� �� ctrl + z" << endl;
	copy(istream_iterator<double>(cin), istream_iterator<double>(), back_inserter(data));
	copy(begin(data), end(data), ostream_iterator<double>(cout, " "));
}