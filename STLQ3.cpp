#include <iostream>
#include <list>
#include <iterator>
#include <istream>
#include <ostream>
#include <string>
#include <algorithm>
#include <deque>
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
	list<string>cityName(20);
	deque<string>cityCheck(20);
	string input;
	int cnt = 0;
	int i = 0;
	printf("도시입력\n");
	while (cnt < 20 && getline(cin, input, '\n'))
	{
		cityName.push_back(input);
		cnt++;
	}
	// cityName.sort();
	copy(cityName.begin(), cityName.end(), front_inserter(cityCheck));
	BubbleSort(cityCheck.begin(), cityCheck.end());
	for (auto iter = begin(cityCheck); iter != end(cityCheck); iter++)
	{
		if (i != 0 && i % 2 == 0)
			printf("%4s\t", (*iter).c_str());
		else
			cout << *iter << "\n\n";
		i++;
	}
}