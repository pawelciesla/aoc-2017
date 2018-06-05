#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

#include "ex9.h"

using namespace std;
const string fileName = "input9.txt";

namespace
{
	void readFile(string& str)
	{
		ifstream file(fileName);
		if (file.is_open())
		{
			file.seekg(0, ios::end);
			str.reserve(file.tellg());
			file.seekg(0, ios::beg);
			str.assign((istreambuf_iterator<char>(file)),
				std::istreambuf_iterator<char>());
		}
	}

	void ignoreChars(string& input)
	{
		for (int i = 0; i < input.length(); ++i)
		{
			if (input[i] == '!')
			{
				input[i++] = 32;
				input[i] = 32;
			}
		}
	}

	int ignoreComments(string& input)
	{
		int count = 0;
		bool removing = false;
		for (int i = 0; i < input.length(); ++i)
		{
			if (removing)
			{
				if (input[i] == '>')
				{
					removing = false;
				}
				else
				{
					++count;
				}
				input[i] = 32;
			}
			else if (input[i] == '<')
			{
				input[i] = 32;
				removing = true;
			}
		}
		return count;
	}

	void ignoreCommas(string& input)
	{
		for (int i = 0; i < input.length(); ++i)
		{
			if (input[i] == ',')
			{
				input[i] = 32;
			}
		}
		input.erase(remove_if(input.begin(), input.end(), isspace), input.end());
	}

	int getGroupWeight(const string& input)
	{
		int weight = 1;
		int opens = 0;
		int summmaryWeight = 0;
		for (int i = 0; i < input.length(); ++i)
		{
			if (input[i] == '{')
			{
				summmaryWeight += weight++;
			}
			else if (input[i] == '}')
			{
				weight--;
			}
		}
		return summmaryWeight;
	}
}

int ex9::Ex9::Run1()
{
	string input;
	readFile(input);
	ignoreChars(input);
	ignoreComments(input);
	ignoreCommas(input);

	return getGroupWeight(input);
}

int ex9::Ex9::Run2()
{
	string input;
	readFile(input);
	ignoreChars(input);
	input.erase(remove_if(input.begin(), input.end(), isspace), input.end());
	return ignoreComments(input);
}
