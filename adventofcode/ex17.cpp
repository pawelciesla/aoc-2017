#include <algorithm>
#include "ex17.h"
#include <vector>

using namespace std;

namespace
{
	vector<int> numbers;
	const short stepLength = 377;
	void prepareVector(const int iterations)
	{
		numbers.clear();
		numbers.push_back(0);
		numbers.reserve(iterations);
		int position = 0;
		int size = 1;
		for (int i = 1; i <= iterations; ++i)
		{
			position = (position + stepLength) % size++ + 1;
			numbers.insert(numbers.begin() + position, i);
		}
	}
	int calculateSecondValue(const int iterations)
	{
		int secondValue = 0;
		int position = 0;
		int size = 1;
		for (int i = 1; i <= iterations; ++i)
		{
			position = (position + stepLength) % size++ + 1;
			if (position == 1)
			{
				secondValue = i;
			}
		}
		return secondValue;
	}
}

int ex17::Ex17::Run1()
{
	prepareVector(2017);
	auto it = find(numbers.begin(), numbers.end(), 2017);
	return *++it;
}

int ex17::Ex17::Run2()
{
	return calculateSecondValue(50000000);
}

