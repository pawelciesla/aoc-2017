#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <deque>
#include <queue>
#include<iomanip>
#include <bitset>

#include "ex14.h"

#define queuelength 256
using namespace std;
const string input = "xlqgujun";

namespace
{
	vector<short int> getInput(int index)
	{
		string inputTemp = input + "-" + to_string(index);
		vector<short int> numbers;
		//17, 31, 73, 47, 23
		//vector<short int> addingNumbers;
		int inputLength = inputTemp.length();
		for (int i = 0; i < inputLength; ++i)
		{
			numbers.push_back(inputTemp[i]);
		}

		numbers.insert(numbers.end(), { 17, 31, 73, 47, 23 });

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

			moveItemToBack(deq, 0, diff);
			int star = startIndex - diff;
			int end = star + length;
			reverse(deq.begin() + star, deq.begin() + end);
			//deque<short int> tempDeq(deq.begin() + startIndex-diff, deq.begin() + startIndex + length-1-diff);
			moveItemToFront(deq, deq.size() - diff);
		}
	}

	const int matrixSize = 128;

	vector<int> getCalculatedRow(int index)
	{
		vector<int> bits;
		bits.reserve(matrixSize);
		vector<short int> deq;
		for (int i = 0; i < queuelength; ++i)
		{
			deq.push_back(i);
		}
		vector<short int> lengths = getInput(index);
		
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
				startIndex = startIndex % queuelength;

			}
		}
		string xorString;
		stringstream stream;
		vector<int> xors;
		for (int i = 0; i < queuelength; i += 16)
		{
			short int xor = deq[i];
			for (int j = 1; j < 16; ++j)
			{
				xor ^= deq[i + j];
			}
			xors.push_back(xor);
			//unsigned s = setw(2) << setfill('0') << xor << xor;
			stream << bitset<8>(xor);
		}
		string bit=stream.str();
		for (auto var : bit)
		{
			if (var == '0')
			{
				bits.push_back(0);
			}
			else
			{
				bits.push_back(-1);
			}
		}
		

		return bits;
	}

	bool doSingleGroup(vector<vector<int>>& matrix, int i, int j, int value)
	{
		if (i < 0 || i == matrixSize || j < 0 || j == matrixSize)
		{
			return false;
		}
		else if (matrix[i][j] == -1)
		{
			matrix[i][j] = value;
			doSingleGroup(matrix, i - 1, j, value);
			doSingleGroup(matrix, i + 1, j, value);
			doSingleGroup(matrix, i, j + 1, value);
			doSingleGroup(matrix, i, j - 1, value);
			return true;
		}
		return false;
	}
	int DoGroups(vector<vector<int>>& matrix)
	{
		int group = 1;
		for (int i = 0; i < matrixSize; ++i)
		{
			for (int j = 0; j < matrixSize; ++j)
			{
				if (doSingleGroup(matrix, i, j, group))
				{
					++group;
				}
			}
		}
		return --group;
	}

}

int ex14::Ex14::Run1()
{
	int used=0;
	for (int i = 0; i < matrixSize; ++i)
	{
		vector<int> s = getCalculatedRow(i);
		for (auto var : s)
		{
			if (var == -1)
			{
				++used;
			}
		}
	}
	
	return used;
}

int ex14::Ex14::Run2()
{
	vector<vector<int>> wholeLines;
	int used = 0;
	for (int i = 0; i < matrixSize; ++i)
	{
		wholeLines.push_back(getCalculatedRow(i));
	}

	return DoGroups(wholeLines);
}
