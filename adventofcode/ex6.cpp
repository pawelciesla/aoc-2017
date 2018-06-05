#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <set>
#include "ex6.h"

using namespace std;

namespace
{
	const string input = "14	0	15	12	11	11	3	5	1	6	8	4	9	1	8	4";

	void readInput(vector<int>& elements, string input)
	{
		string line;
		stringstream stream(input);
		int number;

		while (stream >> number)
		{
			elements.push_back(number);
		}
	}
	int CalculateSteps(vector<int>& elements)
	{
		set<vector<int>> history;
		history.insert(elements);
		const int elementsMaxIndex = elements.size()-1;
		int insertCounts = 1;
		
		while (insertCounts == history.size())
		{
			auto it = distance(elements.begin(), max_element(elements.begin(), elements.end()));
			int moves = elements[it];
			elements[it] = 0;
			while (moves > 0)
			{
				it++;
				if (it>elementsMaxIndex)
				{
					it = 0;
				}
				++elements[it];
				moves--;
			}
			history.insert(elements);
			++insertCounts;
		}
		return --insertCounts;
	}
	int CalculateSteps2(vector<int>& elements)
	{
		set<vector<int>> history;
		history.insert(elements);
		const int elementsMaxIndex = elements.size() - 1;
		int insertCounts = 1;

		while (insertCounts == history.size())
		{
			auto it = distance(elements.begin(), max_element(elements.begin(), elements.end()));
			int moves = elements[it];
			elements[it] = 0;
			while (moves > 0)
			{
				it++;
				if (it>elementsMaxIndex)
				{
					it = 0;
				}
				++elements[it];
				moves--;
			}
			history.insert(elements);
			++insertCounts;
		}

		history.clear();
		history.insert(elements);
		insertCounts = 1;
		while (insertCounts == history.size())
		{
			auto it = distance(elements.begin(), max_element(elements.begin(), elements.end()));
			int moves = elements[it];
			elements[it] = 0;
			while (moves > 0)
			{
				it++;
				if (it>elementsMaxIndex)
				{
					it = 0;
				}
				++elements[it];
				moves--;
			}
			history.insert(elements);
			++insertCounts;
		}
		return --insertCounts;
	}
}
int ex6::Ex6::Run1()
{
	vector<int> elements;
	readInput(elements, input);
	return CalculateSteps(elements);
}

int ex6::Ex6::Run2()
{
	vector<int> elements;
	readInput(elements, input);
	return CalculateSteps2(elements);
}