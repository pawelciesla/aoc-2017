#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <set>

#include "ex4.h"

using namespace std;
const string fileName = "input4.txt";

namespace
{
	void readFile(vector<vector<string>>& wholeElements)
	{
		ifstream file(fileName);
		string line;
		string word;

		int numberOfLines = 0;

		if (file.is_open())
		{
			while (getline(file, line))
			{
				++numberOfLines;
			}
			file.clear();
			file.seekg(0, ios::beg);
			wholeElements.reserve(numberOfLines);

			while (getline(file, line))
			{
				vector<string> elements;
				stringstream stream(line);

				while (stream >> word)
				{
					elements.push_back(word);
				}
				wholeElements.push_back(elements);
			}
		}
	}
}

int ex4::Ex4::Run1()
{
	int validCounts = 0;

	vector<vector<string>> wholeElements;
	readFile(wholeElements);
	set<string> tempSets;

	for (auto const& value : wholeElements)
	{
		tempSets.clear();
		for (auto const& val : value)
		{
			tempSets.insert(val);
		}

		if (value.size() == tempSets.size())
		{
			++validCounts;
		}
		else 
		{
			int l = 0;
		}
	}
	return validCounts;
}

int ex4::Ex4::Run2()
{
	int validCounts = 0;

	vector<vector<string>> wholeElements;
	readFile(wholeElements);
	set<string> tempSets;

	for (auto const& value : wholeElements)
	{
		tempSets.clear();
		for (auto const& val : value)
		{
			string sortedWord = val;
			sort(sortedWord.begin(), sortedWord.end());
			tempSets.insert(sortedWord);
		}

		if (value.size() == tempSets.size())
		{
			++validCounts;
		}
		else
		{
			int l = 0;
		}
	}
	return validCounts;
}
