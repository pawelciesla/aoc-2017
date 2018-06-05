#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <deque>
#include <queue>
#include<iomanip>

#include "ex10.h"

#define queuelength 256
using namespace std;
const string input = "199,0,255,136,174,254,227,16,51,85,1,2,22,17,7,192";

namespace
{
	queue<short int> getInput()
	{
		string inputCopy = input;
		int inputLength = inputCopy.length();
		for (int i = 0; i < inputLength; ++i)
		{
			if (inputCopy[i] == ',')
			{
				inputCopy[i] = 32;
			}
		}

		queue<short int> numbers;
		stringstream sstream(inputCopy);
		int number;
		while (sstream >> number)
		{
			numbers.push(number);
		}
		return numbers;
	}

	vector<short int> getInput2()
	{
		vector<short int> numbers;
		int inputLength = input.length();
		for (int i = 0; i < inputLength; ++i)
		{
			numbers.push_back(input[i]);
		}
		numbers.push_back(17);
		numbers.push_back(31);
		numbers.push_back(73);
		numbers.push_back(47);
		numbers.push_back(23);
		return numbers;
	}

	void moveItemToBack(std::vector<short int>& v, size_t index, size_t count)
	{
		auto it = v.begin() + index;
		rotate(it, it + count, v.end());
	}

	void moveItemToFront(std::vector<short int>& v, size_t count)
	{
		auto it = v.begin();
		rotate(it, it + count, v.end());
	}

	void sort(vector<short int>& deq, short int length, short int startIndex)
	{
		
		short int endIndex = startIndex + length;
		if (endIndex < queuelength)
		{
			reverse(deq.begin() + startIndex, deq.begin() + startIndex + length);
		}
		else
		{
			int diff = endIndex - queuelength;
			
			moveItemToBack(deq, 0,diff);
			int star = startIndex - diff;
			int end = star + length;
			reverse(deq.begin() + star, deq.begin() + end);
			//deque<short int> tempDeq(deq.begin() + startIndex-diff, deq.begin() + startIndex + length-1-diff);
			moveItemToFront(deq, deq.size()-diff);
		}
	}
}

int ex10::Ex10::Run1()
{
	vector<short int> deq;
	for (int i = 0; i < queuelength; ++i)
	{
		deq.push_back(i);
	}
	queue<short int> lengths = getInput();
	int startIndex = 0;
	int skipSize = 0;
	int length = 0;
	while (!lengths.empty())
	{
		length = lengths.front();
		sort(deq, length, startIndex);
		startIndex += length+skipSize++;
		startIndex = startIndex%queuelength;
		lengths.pop();

	}
	return deq[0]*deq[1];
}

string ex10::Ex10::Run2()
{
	vector<short int> deq;
	for (int i = 0; i < queuelength; ++i)
	{
		deq.push_back(i);
	}
	vector<short int> lengths = getInput2();
	int startIndex = 0;
	int skipSize = 0;
	int length = 0;

	
	for (int i = 0; i < 64; ++i)
	{
		int lengthsSize = lengths.size();
		for (int j = 0; j < lengthsSize; ++j)
		{
			length = lengths[j];
			int tempStartIndex = startIndex;
			int tempSkipSize = skipSize;

			sort(deq, length, startIndex);
			

			startIndex += length + skipSize++;
			startIndex = startIndex%queuelength;

		}
	}
	string xorString;
	stringstream stream;
	vector<int> xors;
	for (int i = 0; i < queuelength; i+=16)
	{
		short int xor = deq[i];
		for (int j = 1; j < 16; ++j)
		{
			xor ^= deq[i+j];
		}
		xors.push_back(xor);
		stream << hex << xor;
	}

	string s = stream.str();
	return stream.str();
}
