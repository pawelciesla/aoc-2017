#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "ex21.h"
using namespace std;

namespace
{
	map<vector<vector<bool>>, vector<vector<bool>>> translations;
	vector<vector<bool>> finalOutput;

	void AddTranslationsFor2(const vector<vector<bool>>& output, const vector<vector<bool>>& input)
	{
		vector<vector<bool>> tempVector = input;
		for (int i = 0; i < 4; ++i)
		{
			translations[tempVector] = output; 
			{
				vector<vector<bool>> tempVector2 = tempVector;
				tempVector2[0][0] = tempVector[1][0];
				tempVector2[0][1] = tempVector[1][1];
				tempVector2[1][0] = tempVector[0][0];
				tempVector2[1][1] = tempVector[0][1];
				translations[tempVector2] = output;
			}
			{
				vector<vector<bool>> tempVector2 = tempVector;
				tempVector[0][0] = tempVector2[1][0];
				tempVector[0][1] = tempVector2[0][0];
				tempVector[1][0] = tempVector2[1][1];
				tempVector[1][1] = tempVector2[0][1];
			}
		}
	}

	void AddTranslationsFor3(const vector<vector<bool>>& output, const vector<vector<bool>>& input)
	{
		vector<vector<bool>> tempVector = input;
		for (int i = 0; i < 4; ++i)
		{
			translations[tempVector] = output;
			{
				vector<vector<bool>> tempVector2 = tempVector;
				tempVector2[0][0] = tempVector[2][0];
				tempVector2[0][1] = tempVector[2][1];
				tempVector2[0][2] = tempVector[2][2];

				tempVector2[2][0] = tempVector[0][0];
				tempVector2[2][1] = tempVector[0][1];
				tempVector2[2][2] = tempVector[0][2];

				translations[tempVector2] = output;
			}
			translations[tempVector] = output;
			{
				vector<vector<bool>> tempVector2 = tempVector;
				tempVector2[0][0] = tempVector[0][2];
				tempVector2[1][0] = tempVector[1][2];
				tempVector2[2][0] = tempVector[2][2];

				tempVector2[0][2] = tempVector[0][0];
				tempVector2[1][2] = tempVector[1][0];
				tempVector2[2][2] = tempVector[2][0];

				translations[tempVector2] = output;
			}
			{
				vector<vector<bool>> tempVector2 = tempVector;
				tempVector[0][0] = tempVector2[2][0];
				tempVector[0][1] = tempVector2[1][0];
				tempVector[0][2] = tempVector2[0][0];

				tempVector[1][0] = tempVector2[2][1];
				tempVector[1][2] = tempVector2[0][1];

				tempVector[2][0] = tempVector2[2][2];
				tempVector[2][1] = tempVector2[1][2];
				tempVector[2][2] = tempVector2[0][2];
			}
		}
	}

	void readFile()
	{
		ifstream sstream("input21.txt");
		string line;
		while (getline(sstream, line))
		{
			vector<vector<bool>> output;
			vector<vector<bool>> inputs;
			auto index = line.find('=') - 1;
			string tempString = line.substr(0, index);
			int row = 0;
			inputs.push_back(vector<bool>());
			for (int i = 0; i < index; ++i)
			{
				if (tempString[i] == '.')
				{
					inputs[row].push_back(false);
				}
				else if (tempString[i] == '#')
				{
					inputs[row].push_back(true);
				}
				else if (tempString[i] == '/')
				{
					++row;
					inputs.push_back(vector<bool>());
				}
			}
			tempString = line.substr(index + 2);
			index = tempString.length();
			row = 0;
			output.push_back(vector<bool>());
			for (int i = 0; i < index; ++i)
			{
				if (tempString[i] == '.')
				{
					output[row].push_back(false);
				}
				else if (tempString[i] == '#')
				{
					output[row].push_back(true);
				}
				else if (tempString[i] == '/')
				{
					++row;
					output.push_back(vector<bool>());
				}
			}
			if (inputs.size() == 2)
				AddTranslationsFor2(output, inputs);
			if (inputs.size() == 3)
				AddTranslationsFor3(output, inputs);
		}
	}
	void doIterations(const int count)
	{
		int k = 0;
		while (k++ < count)
		{
			int finalOutputSize = finalOutput.size();
			int squareSize = (finalOutputSize % 2 == 0) ? 2 : 3;
			int incrementedSquareSize = 1 + squareSize;
			int groupsCount = finalOutputSize / squareSize;
			int finalSize = groupsCount*incrementedSquareSize;
			int finalOutputRow = -incrementedSquareSize;

			vector<vector<bool>> tempOutput(finalSize,vector<bool>());

			for (int i = 0; i < finalOutputSize; i += squareSize)
			{
				for (int j = 0; j < finalOutputSize; j += squareSize)
				{
					if (j == 0)
					{
						finalOutputRow += incrementedSquareSize;
					}
					vector<vector<bool>> tempVector(squareSize, vector<bool>());
					for (int l = 0; l < squareSize; ++l)
					{
						auto it = finalOutput[l+i].begin()+j;
						tempVector[l].insert(tempVector[l].begin(), it, it + squareSize);
					}
					auto translation = translations.find(tempVector);
					if (translation != translations.end())
					{
						auto it = translation->second.begin();
						auto itEnd = translation->second.end();
						int position = finalOutputRow;
						while (it != itEnd)
						{
							tempOutput[position].insert(tempOutput[position].end(), it->begin(), it->end());
							++it;
							++position;
						}
					}
					else
					{
						throw invalid_argument("there is no translation");
					}
				}
			}
			finalOutput = tempOutput;
		}
	}
	int doJob(int iterations)
	{
		finalOutput.clear();
		finalOutput.push_back({ false, true, false });
		finalOutput.push_back({ false, false, true });
		finalOutput.push_back({ true, true, true });
		doIterations(iterations);
		int on = 0;
		int off = 0;
		const int size = finalOutput.size();
		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				if (finalOutput[i][j] == true)
				{
					++on;
				}
				else
					++off;
			}
		}

		return on;
	}
}

int ex21::Ex21::Run1()
{
	readFile();

	return doJob(5);
}

int ex21::Ex21::Run2()
{
	return doJob(18);
}

