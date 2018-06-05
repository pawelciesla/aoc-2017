#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <set>
#include "ex7.h"

using namespace std;
const string fileName = "input7.txt";

namespace
{
	struct disc
	{
		int size;
		string name;
		disc* parent;
		vector<disc*> discs;
		int childsSize;
		int totalSize;
		disc(string _name, int _size)
		{
			name = _name;
			size = _size;
			parent = nullptr;
			childsSize = 0;
			totalSize = 0;
		}
	};

	struct discStrings
	{
		int size;
		string name;
		vector<string> discs;
		discStrings(string _name, int _size)
		{
			name = _name;
			size = _size;
		}
	};

	bool compareDiscs(disc& left, disc& right)
	{
		return left.name < right.name;
	}

	discStrings readLine(string line)
	{
		int index1 = line.find(" ");
		int index2 = line.find("(")+1;
		int index3 = line.find(")");

		discStrings disc(line.substr(0, index1), stoi(line.substr(index2, index3-index2)));
		int index = line.find("->");
		if (index > -1)
		{
			index += 3;
			disc.discs.push_back(line.substr(index, line.find(",", index+1)-index));
			while ((index = line.find(',', index + 1)) > -1)
			{
				index += 2;
				disc.discs.push_back(line.substr(index, line.find(",", index+1) - index));
			}
		}
		return disc;
		
	}

	string readFile(vector<disc>& wholeElements)
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
			wholeElements.push_back(disc(element.name, element.size));
		}
		for (auto& element : stringElements)
		{
			if (element.discs.size() > 0)
			{
				for (int i = 0; i < element.discs.size(); ++i)
				{
					for (auto& value : wholeElements)
					{
						if (value.name == element.discs.at(i))
						{
							for (auto& valueFather : wholeElements)
							{
								if (valueFather.name == element.name)
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
		for (auto& value : wholeElements)
		{
			if (!value.parent)
			{
				return value.name;
			}
		}
		return "";
	}

	int balanceTower(disc& element, int& neededSize)
	{
		if (element.discs.size() == 0)
		{
			return element.size;
		}
		else
		{
			int size = balanceTower(*element.discs.at(0),neededSize);
			int ChildsSize = size;
			for (int i = 1; i < element.discs.size();++i)
			{
				int sizeOfTower = balanceTower(*element.discs.at(i), neededSize);
				if (size != sizeOfTower)
				{
					neededSize = size - element.discs[i]->childsSize;
				}
				ChildsSize += size;
			}
			element.childsSize = ChildsSize;
			element.totalSize = element.size + ChildsSize;
			return element.size + size*element.discs.size();
		}
	}

	void balanceTowers(vector<disc>& wholeElements, int& neededSize)
	{
		for (auto& value : wholeElements)
		{
			if (!value.parent)
			{
				balanceTower(value, neededSize);
			}
		}
	}
}

string ex7::Ex7::Run1()
{
	vector<disc> wholeElements;
	return readFile(wholeElements);
}

int ex7::Ex7::Run2()
{
	vector<disc> wholeElements;
	readFile(wholeElements);
	int neededSize;
	balanceTowers(wholeElements, neededSize);
	return neededSize;
	
}