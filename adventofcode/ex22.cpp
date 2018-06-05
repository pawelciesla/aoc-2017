#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include "ex22.h"
using namespace std;

namespace
{
	enum states
	{
		Clean = 0,
		Weakened,
		Infected,
		Flagged
	};
	map<vector<int>, bool> objects;
	map<vector<int>, states> objects2;
	void readFile()
	{
		objects.clear();
		ifstream sstream("input22.txt");
		string line;
		getline(sstream, line);
		int size = line.size();
		int positionCorrection = (size - 1) / 2;
		int row = -positionCorrection;
		do
		{
			for (int i = 0; i < size; ++i)
			{
				if (line[i] == '#')
				{
					objects[{i - positionCorrection, row}] = true;
				}
			}
			++row;
		} while (getline(sstream, line));
	}

	void readFile2()
	{
		objects.clear();
		ifstream sstream("input22.txt");
		string line;
		getline(sstream, line);
		int size = line.size();
		int positionCorrection = (size - 1) / 2;
		int row = -positionCorrection;
		do
		{
			for (int i = 0; i < size; ++i)
			{
				if (line[i] == '#')
				{
					objects2[{i - positionCorrection, row}] = states::Infected;
				}
			}
			++row;
		} while (getline(sstream, line));
	}


	int doJob(int iterations)
	{
		int infected = 0;
		int x = 0, y = 0;
		int moveX = 0, moveY = -1;
		for (int iteration = 0; iteration < iterations; ++iteration)
		{
			auto it = objects.find({ x, y });
			if (it == objects.end())
			{
				objects[{x, y}] = true;
				++infected;
				if (moveX == 1)
				{
					moveY = -1;
					moveX = 0;
				}
				else if (moveX == -1)
				{
					moveY = 1;
					moveX = 0;
				}
				else if (moveY == 1)
				{
					moveX = 1;
					moveY = 0;
				}
				else if (moveY == -1)
				{
					moveX = -1;
					moveY = 0;
				}
			}
			else
			{
				objects.erase(it);
				if (moveX == 1)
				{
					moveY = 1;
					moveX = 0;
				}
				else if (moveX == -1)
				{
					moveY = -1;
					moveX = 0;
				}
				else if (moveY == 1)
				{
					moveX = -1;
					moveY = 0;
				}
				else if (moveY == -1)
				{
					moveX = 1;
					moveY = 0;
				}
			}
			x += moveX;
			y += moveY;
		}
 		return infected;
	}

	int doJob2(int iterations)
	{
		int infected = 0;
		int x = 0, y = 0;
		int moveX = 0, moveY = -1;
		for (int iteration = 0; iteration < iterations; ++iteration)
		{
			auto it = objects2.find({ x, y });
			if (it == objects2.end())
			{
				objects2[{x, y}] = states::Weakened;
				if (moveX == 1)
				{
					moveY = -1;
					moveX = 0;
				}
				else if (moveX == -1)
				{
					moveY = 1;
					moveX = 0;
				}
				else if (moveY == 1)
				{
					moveX = 1;
					moveY = 0;
				}
				else if (moveY == -1)
				{
					moveX = -1;
					moveY = 0;
				}
			}
			else
			{
				if (it->second == states::Flagged)
				{
					objects2.erase(it); 
					moveY *= -1;
					moveX *= -1;
				}
				else if (it->second == states::Weakened)
				{
					++infected;
					it->second = states::Infected;
					
				}
				else
				{
					it->second = states::Flagged; 
					if (moveX == 1)
					{
						moveY = 1;
						moveX = 0;
					}
					else if (moveX == -1)
					{
						moveY = -1;
						moveX = 0;
					}
					else if (moveY == 1)
					{
						moveX = -1;
						moveY = 0;
					}
					else if (moveY == -1)
					{
						moveX = 1;
						moveY = 0;
					}
				}
			}
			x += moveX;
			y += moveY;
		}
		return infected;
	}
}

int ex22::Ex22::Run1()
{
	readFile();

	return doJob(10000);
}

int ex22::Ex22::Run2()
{
	readFile2();

	return doJob2(10000000);
}

