#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "ex24.h"

using namespace std;

namespace
{
	struct member
	{
		int first, second;
		bool f, s;
		member(int _first, int _second) : first(_first), second(_second), f(true), s(true)
		{
		}
		bool operator != (const member& _member)
		{
			return !(first == _member.first && second == _member.second);
		}
	};
	vector<member> members;

	int maximum = 0;
	int maxLength = 0;
	int maxWithLength = 0;

	void readFile()
	{
		ifstream sstream("input24.txt");
		string line;
		while (getline(sstream, line))
		{
			int index = line.find('/');
			int first = stoi(line.substr(0, index));
			int second = stoi(line.substr(++index));
			if (first<second)
				members.push_back(member(first, second));
			else
				members.push_back(member(second, first));
		}
	}

	void findRoute(vector<member> tmpMembers, const int lastValue, vector<member> members)
	{
		int length = 0;
		for (auto it : tmpMembers)
		{
			length += it.first + it.second;
		}
		if (length > maximum)
		{
			maximum = length;
		}
		int size = tmpMembers.size();
		if (size >= maxLength)
		{
			if (size > maxLength)
			{
				maxWithLength = 0;
				maxLength = size;
			}
			if (length > maxWithLength)
			{
				maxWithLength = length;
			}
		}

		const auto last = tmpMembers.back();
		auto it = members.begin();
		while (it != members.end())
		{
			if (*it != last)
			{
				if (it->f && it->first == lastValue)
				{
					it->f = false;
					it->s = false;
					tmpMembers.push_back(*it);
					findRoute(tmpMembers, it->second, members);
					it->f = true;
					it->s = true;
					tmpMembers.pop_back();
				}
				else if (it->s && it->second == lastValue)
				{
					it->f = false;
					it->s = false;
					tmpMembers.push_back(*it);
					findRoute(tmpMembers, it->first, members);
					it->f = true;
					it->s = true;
					tmpMembers.pop_back();
				}
			}
			++it;
		}
	}

	void cleanMembers()
	{
		auto it = members.begin();
		while (it != members.end())
		{
			it->f = true;
			it->s = true;
			++it;
		}
	}

	void findWholeRoutes()
	{
		auto it = members.begin();
		int size = 0;
		while (it != members.end())
		{
			if (it->first == 0)
			{
				vector<member> tmpMembers;
				it->f = false;
				it->s = false;
				tmpMembers.push_back(*it);
				findRoute(tmpMembers, it->second,members);
				cleanMembers();
			}
			++it;
		}
	}
};

int ex24::Ex24::Run1()
{
	readFile();
	findWholeRoutes();
	return maximum;
}

int ex24::Ex24::Run2()
{
	return maxWithLength;
}

