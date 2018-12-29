#include <iostream>
#include <vector>
#include <iterator>
#include <istream>
#include <ostream>
#include <string>
#include <algorithm>

using namespace std;

template<typename RandomIter>
void BubbleSort(RandomIter start, RandomIter end)
{
	bool order = false;
	while (true)
	{
		for (auto first = start + 1; first != end; first++)
		{
			if (*(first - 1) > *first)
			{
				swap(*first, *(first - 1));
				order = true;
			}
		}
		if (!order)
		break;
	order = false;
	}
	
}
int main()
{
	vector<string>cityName(20);
	string input;
	int cnt = 0;
	int i = 0;
	while (cnt < 20 && cin >> input)
	{
		cityName.push_back(input);
		cnt++;
	}
	BubbleSort(cityName.begin(), cityName.end());
	for (auto iter = begin(cityName); iter != end(cityName); iter++)
	{
		if (i != 0 && i % 2 == 0)
			printf("%4s\t", (*iter).c_str());
		else
			cout << *iter << "\n\n";
		i++;
	}
}
