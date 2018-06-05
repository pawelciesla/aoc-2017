#include <string>
#include <vector>
#include <fstream>
#include "ex13.h"

using namespace std;
const string fileName = "input13.txt";

namespace
{
	struct layer
	{
		int max, index;
		layer(int index, int max)
		{
			this->index = index;
			this->max = max;
		}
	};

	void readFile(vector<layer>& wholeElements)
	{
		wholeElements.clear();
		ifstream file(fileName);

		string line;
		int it = 0;
		if (file.is_open())
		{
			while (getline(file, line))
			{
				int position = line.find(':');
				int index = stoi(line.substr(0, position));
				int max = stoi(line.substr(position + 1));
				
				wholeElements.push_back(layer(index, max));
				++it;
			}
		}
	}
}

int ex13::Ex13::Run1()
{
	vector<layer> wholeElements;
	readFile(wholeElements);
	int sum = 0;

	int size = wholeElements.size();
	for (int i = 0; i < size; ++i)
	{
		auto it = wholeElements.begin() + i;
		if (it->index% (2*(it->max-1))==0)
		{
			sum += it->index* it->max;
		}
	}

	return sum;
}

int ex13::Ex13::Run2()
{
	vector<layer> wholeElements;
	bool caught = false;
	int iteration = -1;
	readFile(wholeElements);
	int size = wholeElements.size();
	do
	{
		++iteration;
		caught = false;
		for (int i = 0; i < size; ++i)
		{
			auto it = wholeElements.begin() + i;
			if ((it->index+iteration) % (2 * (it->max - 1)) == 0)
			{
				caught = true;
			}
		}
	}
	while (caught);

	return iteration;
}