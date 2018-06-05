#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <set>

#include "ex5.h"

using namespace std;
const string fileName = "input5.txt";

namespace
{
	int readFile(vector<int>& wholeElements)
	{
		ifstream file(fileName);
		string line;
		int number;

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
				stringstream stream(line);

				while (stream >> number)
				{
					wholeElements.push_back(number);
				}
			}
		}
		return numberOfLines;
	}

	int GoToExit(vector<int>& elements, int index, const int linesCount)
	{
		int moves = 0;
		while (index < linesCount)
		{
			index += elements[index]++;
			moves++;
		}
		return moves;
	}

	int GoToExit2(vector<int>& elements, int index, const int linesCount)
	{
		int moves = 0;
		while (index < linesCount)
		{
			if (elements[index] >2)
			{
				index += elements[index]--;
			}
			else
			{
				index += elements[index]++;
			}
			moves++;
		}
		return moves;
	}
}

int ex5::Ex5::Run1()
{
	vector<int> wholeElements;
	int numberOfLines = readFile(wholeElements);

	return GoToExit(wholeElements, 0, numberOfLines);
}

int ex5::Ex5::Run2()
{
	vector<int> wholeElements;
	int numberOfLines = readFile(wholeElements);

	return GoToExit2(wholeElements, 0, numberOfLines);
}
