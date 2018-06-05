#include <algorithm>
#include "ex23.h"
#include <vector>
#include <string>
#include <functional>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iostream>
#include <deque>

using namespace std;

namespace
{
	bool isInt(const string& s)
	{
		return !s.empty() && find_if(s.begin(), s.end(), [](char c) { return !isdigit(c) && c != '-'; }) == s.end();
	}

	int LastPlayed;
	int recovered = 0;
	int sended = 0;
	int position1 = 0, position2 = 0;
	struct Member
	{
		long long int Value;
		char Name;
		Member(int Value, char Name)
		{
			this->Value = Value;
			this->Name = Name;
		}
	};

	vector<Member> Members1, Members2;
	deque<int> inbox1, inbox2;

	struct Operation
	{
		function<bool()> foo;
		char Name;
		char SecondName;
		int Value;
		Operation(string& operationType, string& input1, string& input2, bool secondOption, bool firstProgram)
		{

			if (operationType == "set")
			{
				if (isInt(input2))
				{
					Name = input1[0];
					Value = stoi(input2);
					foo = bind(&Operation::Set, this, Name, Value, firstProgram);
				}
				else
				{
					Name = input1[0];
					SecondName = input2[0];
					foo = bind(&Operation::SetChar, this, Name, SecondName, firstProgram);
				}
			}
			else if (operationType == "mul")
			{
				if (isInt(input2))
				{
					Name = input1[0];
					Value = stoi(input2);
					foo = bind(&Operation::Multiply, this, Name, Value, firstProgram);
				}
				else
				{
					Name = input1[0];
					SecondName = input2[0];
					foo = bind(&Operation::MultiplyChar, this, Name, SecondName, firstProgram);
				}
			}
			else if (operationType == "sub")
			{
				if (isInt(input2))
				{
					Name = input1[0];
					Value = stoi(input2);
					foo = bind(&Operation::Decrease, this, Name, Value, firstProgram);
				}
				else
				{
					Name = input1[0];
					SecondName = input2[0];
					foo = bind(&Operation::DecreaseChar, this, Name, SecondName, firstProgram);
				}
			}
			else if (operationType == "jnz")
			{
				if (isInt(input2))
				{
					if (isInt(input1))
					{
						int value1 = stoi(input1);
						Value = stoi(input2);
						foo = bind(&Operation::JumpInts, this, value1, Value, firstProgram);
					}
					else
					{
						Name = input1[0];
						Value = stoi(input2);
						foo = bind(&Operation::Jump, this, Name, Value, firstProgram);
					}
				}
				else
				{
					Name = input1[0];
					SecondName = input2[0];
					foo = bind(&Operation::JumpChar, this, Name, SecondName, firstProgram);
				}
			}
		}

		vector<Member>::iterator FindMember(char name, bool firstProgram)
		{
			auto it = find_if(firstProgram ? Members1.begin() : Members2.begin(), firstProgram ? Members1.end() : Members2.end(),
				[name](Member const& item)
			{
				return item.Name == name;
			});
			return it;
		}

		bool Set(char name, int value, bool firstProgram)
		{
			FindMember(name, firstProgram)->Value = value;
			return true;
		};

		bool SetChar(char name, char secondName, bool firstProgram)
		{
			FindMember(name, firstProgram)->Value = FindMember(secondName, firstProgram)->Value;
			return true;
		};

		bool Decrease(char name, int value, bool firstProgram)
		{
			FindMember(name, firstProgram)->Value -= value;
			return true;
		};

		bool DecreaseChar(char name, char secondName, bool firstProgram)
		{
			FindMember(name, firstProgram)->Value -= FindMember(secondName, firstProgram)->Value;
			return true;
		};

		bool Multiply(char name, int value, bool firstProgram)
		{
			++recovered;
			FindMember(name, firstProgram)->Value *= value;
			return true;
		}

		bool MultiplyChar(char name, char secondName, bool firstProgram)
		{
			++recovered;
			FindMember(name, firstProgram)->Value *= FindMember(secondName, firstProgram)->Value;
			return true;
		};


		bool Jump(char name, int value, bool firstProgram)
		{
			if (FindMember(name, firstProgram)->Value != 0)
			{
				(firstProgram ? position1 : position2) += value - 1;
			}
			return true;
		}

		bool JumpInts(int value1, int value, bool firstProgram)
		{
			if (value1 != 0)
			{
				(firstProgram ? position1 : position2) += value - 1;
			}
			return true;
		}

		bool JumpChar(char name, char secondName, bool firstProgram)
		{
			if (FindMember(name, firstProgram)->Value != 0)
			{
				(firstProgram ? position1 : position2) += FindMember(secondName, firstProgram)->Value - 1;
			}
			return true;
		}

	};
	vector<Operation> Operations1, Operations2;

	vector<string> splitString(string& input)
	{
		vector<string> output;
		size_t pos = 0, found;
		while ((found = input.find_first_of(' ', pos)) != std::string::npos) {
			output.push_back(input.substr(pos, found - pos));
			pos = found + 1;
		}
		output.push_back(input.substr(pos));
		return output;
	}

	void prepareVectors(bool secondOption, bool firstProgram)
	{
		Operations1.clear();
		Members1.clear();
		if (secondOption)
			Members2.push_back(Member(0, 'p'));
		ifstream sstream("input23.txt");
		string line;

		for (int i = 'a'; i < 'i'; ++i)
		{
			Members1.push_back(Member(0, i));
		}
		while (getline(sstream, line))
		{
			vector<string> ssline = splitString(line);
			if (ssline.size() == 2)
				ssline.push_back("");

			Operations1.push_back(Operation(ssline[0], ssline[1], ssline[2], secondOption, firstProgram));
		}
	}

	void Run()
	{
		int size = Operations1.size();
		int it = 0;
		while (position1 < size)
		{
			if (++it % 100000000 == 0)
				cout << it;
			bool s = Operations1[position1++].foo();
		}
		it++;
	}
}

int ex23::Ex23::Run1()
{
	prepareVectors(false, true);
	Run();
	return recovered;
}

long long int ex23::Ex23::Run2()
{

	long long int b = 0, c = 0, d = 0, e = 0, f = 0, h = 0;

	b = 81 * 100 + 100000;
	c = b + 17000;

	while (true) {
		f = 1;
		for (e = 2; e < b / 2; ++e)
		{
			if (b%e == 0)
			{
				f = 0;
				e = b;
			}
		}

		if (f == 0)
		{
			h++;
		}

		if (b == c)
		{
			return h;
		}
		b += 17;
	}

	return h;
}

