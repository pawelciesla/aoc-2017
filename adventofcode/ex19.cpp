#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <deque>
#include "ex19.h"
using namespace std;

namespace
{
	vector<string> strings;
	string output;
	int columns = 0;
	int rows = 0;
	bool movingUpDown = true;
	int iterations = 0;
	void readFile()
	{
		strings.clear();
		output.clear();
		ifstream sstream("input19.txt");
		string line;
		while (getline(sstream, line))
		{
			strings.push_back(line);	
		}
		columns = strings[0].size();
		rows = strings.size();
	}
	void run()
	{
		int x = 0, y = 0;
		int xChange = 1, yChange = 0;
		for (int i = 0; i < columns; ++i)
		{
			if (strings[0][i] == '|')
			{
				y = i;
				i = columns;
			}
		}

		bool notEnd = true;
		while (notEnd)
		{

			x += xChange;
			y += yChange;
			if (movingUpDown)
			{
				if (strings[x][y] == '+')
				{
					if (y > 0)
					{
						if (strings[x][y - 1] != ' ')
						{
							yChange = -1;
							xChange = 0;
						}
						else if (y < columns - 1)
						{
							if (strings[x][y + 1] != ' ')
							{
								yChange = 1;
								xChange = 0;
							}
						}
					}
					
					movingUpDown = false;
				}
				else if (strings[x][y] == ' ')
				{
					notEnd = false;
				}
				else if (strings[x][y] != '|' && strings[x][y] != ' ' && strings[x][y] != '-')
				{
					output += strings[x][y];
				}

			}
			else
			{
				if (strings[x][y] == '+')
				{
					if (x > 0)
					{
						if (strings[x - 1][y] != ' ')
						{
							yChange = 0;
							xChange = -1;
						}
						else if (x < rows - 1)
						{
							if (strings[x + 1][y] != ' ')
							{
								yChange = 0;
								xChange = 1;
							}
						}
					}

					movingUpDown = true;
				}
				else if (strings[x][y] == ' ')
				{
					notEnd = false;
				}
				else if (strings[x][y] != '|' && strings[x][y] != ' ' && strings[x][y] != '-')
				{
					output += strings[x][y];
				}
			}
			++iterations;
		}
	}
}

string ex19::Ex19::Run1()
{
	readFile();
	run();
	return output;
}

int ex19::Ex19::Run2()
{
	return iterations;
}

