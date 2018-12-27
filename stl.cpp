#include <iostream>
#include <array>
using namespace std;

int main()
{
	//Q1
	int cnt = 0;
	array<unsigned int, 50> fido;
	auto func = [&fido, &cnt](int num) {
		if (cnt != 0 && cnt % 8 == 0)
			printf("\n");

		if (cnt < 2)
		{
			if (cnt == 0) return fido[cnt++] = 0;
			else return fido[cnt++] = 1;
		}
		else
		{
			return fido[cnt++] = (fido[cnt - 1] + fido[cnt - 2]);
		}
	};
	transform(begin(fido), end(fido), ostream_iterator<int>(cout," "), func);
}