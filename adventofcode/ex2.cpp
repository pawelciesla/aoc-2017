#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>

#include "ex2.h"

using namespace std;
const string fileName = "input2.txt";

namespace
{
	void readFile(vector<vector<int>>& wholeElements)
	{
		ifstream file(fileName);
		string line;
		int number;
		
		if (file.is_open())
		{
			while (getline(file, line))
			{
				vector<int> elements;
				stringstream stream(line);

				while (stream >> number)
				{
					elements.push_back(number);
				}
				wholeElements.push_back(elements);
			}
		}
	}
}

int ex2::Ex2::Run1()
{
	int minValue;
	int maxValue;
	int checksum = 0;

	vector<vector<int>> wholeElements;
	readFile(wholeElements);

	for (auto const& value : wholeElements) 
	{
		minValue = numeric_limits<int>::max();
		maxValue = numeric_limits<int>::min();
		for (auto const& val : value)
		{
			minValue = min(minValue, val);
			maxValue = max(maxValue, val);
		}
		checksum += maxValue - minValue;
	}
	return checksum;
}

int ex2::Ex2::Run2()
{
	int checksum = 0;

	vector<vector<int>> wholeElements;
	readFile(wholeElements);

	for (auto const& value : wholeElements)
	{
		for (auto it = value.begin(); it != value.end(); ++it) 
		{
			for (auto it2 = value.begin(); it2 != value.end(); ++it2)
			{
				if (*it % *it2 == 0 && *it != *it2)
				{
					checksum += *it / *it2;
					it = value.end() -1;
					it2 = value.end() -1;
				}
			}
		}
	}
	return checksum;
}
