#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <deque>
#include <queue>
#include<iomanip>
#include <bitset>
#include <numeric>

#include "ex16.h"

using namespace std;

namespace
{
	//const string input = "s1,x3/4,pe/b";
	const int vectorSize = 16;
	vector<char> chars (vectorSize);

	void prepareChars()
	{
		char start = 'a';
		iota(begin(chars), end(chars), start);
	}

	void moveItemToBack(size_t index)
	{
		auto it = chars.begin();
		rotate(it, it + index, chars.end());
	}

	void readLine(string& line)
	{
		switch (line[0])
		{
		case 's':
		{
					int count = stoi(line.substr(1));
					moveItemToBack(vectorSize - count);
					break;
		}
		case 'x':
		{
					int position = line.find('/');
					auto it = chars.begin();
					auto swap1 = it + stoi(line.substr(1, position == 3 ? 2 : 1)) ;
					auto swap2 = it + stoi(line.substr(position + 1));
					iter_swap(swap1, swap2);
					break;
		}
		case 'p':
		{
					auto it1 = find(chars.begin(), chars.end(), line[1]);
					auto it2 = find(chars.begin(), chars.end(), line[3]);
					iter_swap(it1, it2);
					break;
		}
		}
	}
	
	vector<string> strings;
	vector<string> UsedStrings;

	void readInput()
	{
		ifstream sstream("input16.txt");
		string line;
		while (getline(sstream, line, ','))
		{
			strings.push_back(line);
		}
	}
	void analyzeInput()
	{
		auto it = strings.begin();
		while (it!=strings.end())
		{
			readLine(*it++);
		}
	}
}


string ex16::Ex16::Run1()
{
	prepareChars();
	readInput();
	analyzeInput();
	string s;
	for (const auto& var : chars)
	{
		s += var;
	}
	return s;
}

string ex16::Ex16::Run2()
{
	int length = 1000000000;
	prepareChars();
	for (int i = 0; i < length; ++i)
	{
		analyzeInput();
		string s;
		for (const auto& var : chars)
		{
			s += var;
		}
		auto it = find(UsedStrings.begin(), UsedStrings.end(), s);
		if (it == UsedStrings.end())
		{
			UsedStrings.push_back(s);
		}
		else
		{
			int circleLength = UsedStrings.end() - it;
			int startPosition = it - UsedStrings.begin();
			int returned = (length - startPosition) % circleLength;
			return UsedStrings[returned-1];
		}
	}
	return "";
}

