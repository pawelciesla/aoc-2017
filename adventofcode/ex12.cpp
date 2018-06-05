#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>
#include "ex12.h"

using namespace std;
const string fileName = "input12.txt";

namespace
{
	struct program
	{
		int size;
		int name;
		program* parent;
		vector<program*> discs;
		program(int _name)
		{
			name = _name;
			size = 1;
			parent = nullptr;
		}
		bool operator()(program const &nation) const
		{
			return nation.name == name;
		}
	};

	struct discStrings
	{
		string name;
		vector<string> discs;
		discStrings(string _name)
		{
			name = _name;
		}
	};

	bool compareDiscs(program& left, program& right)
	{
		return left.name < right.name;
	}

	discStrings readLine(string line)
	{
		int index1 = line.find(" ");
		int index2 = line.find("(") + 1;
		int index3 = line.find(")");

		discStrings disc(line.substr(0, index1));
		int index = line.find("<->");
		if (index > -1)
		{
			index += 3;
			disc.discs.push_back(line.substr(index, line.find(",", index + 1) - index));
			while ((index = line.find(',', index + 1)) > -1)
			{
				index += 2;
				disc.discs.push_back(line.substr(index, line.find(",", index + 1) - index));
			}
		}
		return disc;

	}

	//returning number of lines
	void readFile(vector<program>& wholeElements)
	{
		ifstream file(fileName);

		string line;
		int number;

		vector<discStrings> stringElements;

		int numberOfLines = 0;

		if (file.is_open())
		{
			while (getline(file, line))
			{
				stringElements.push_back(readLine(line));
			}
		}
		for (auto& element : stringElements)
		{
			wholeElements.push_back(program(stoi(element.name)));
		}
		for (auto& element : stringElements)
		{
			if (element.discs.size() > 0)
			{
				for (int i = 0; i < element.discs.size(); ++i)
				{
					for (auto& value : wholeElements)
					{
						if (value.name == stoi(element.discs.at(i)))
						{
							for (auto& valueFather : wholeElements)
							{
								if (valueFather.name == stoi(element.name))
								{
									valueFather.discs.push_back(&value);
									value.parent = &valueFather;
								}
							}
						}
					}
				}
			}
		}
	}

	vector<program> visitedElements;
	void balanceTower(program& element)
	{
		int size = visitedElements.size();
		for (int i = 0; i < size; ++i)
		{
			if (visitedElements[i].name == element.name)
				return;
		}
		visitedElements.push_back(element);
		
		if (element.discs.size() == 0)
			return;
		
		for (int i = 0; i < element.discs.size(); ++i)
		{
			balanceTower(*element.discs.at(i));
		}
		return;
	}
	
}

int ex12::Ex12::Run1()
{
	vector<program> wholeElements;
	readFile(wholeElements);
	balanceTower(wholeElements[0]);

	return  visitedElements.size();
	return 0;
}

int ex12::Ex12::Run2()
{
	vector<program> wholeElements;
	readFile(wholeElements);
	int countOfGroups = 1;

	auto it = wholeElements.begin();
	while (it != wholeElements.end())
	{
		auto find_iter = find_if(visitedElements.begin(), visitedElements.end(),
			program(*it));

		if (find_iter == visitedElements.end())
		{
			balanceTower(*it);
			++countOfGroups;
		}
		++it;
	}


	return  countOfGroups;

}