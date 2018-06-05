#include <algorithm>
#include "ex18.h"
#include <vector>
#include <string>
#include <functional>
#include <iostream>
#include <fstream>
#include <sstream>
#include <deque>

using namespace std;

namespace
{
	bool isInt(const string& s)
	{
		return !s.empty() && find_if(s.begin(), s.end(), [](char c) { return !isdigit(c) && c!='-' ; }) == s.end();
	}

	int LastPlayed;
	int recovered;
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
		//	void(*foo)();
		char Name;
		char SecondName;
		int Value;
		Operation(string& operationType, string& input1, string& input2, bool secondOption, bool firstProgram)
		{
			if (operationType == "snd")
			{
				if (secondOption)
				{
					if (isInt(input2))
					{
						Name = input1[0];
						Value = stoi(input2);
						foo = bind(&Operation::Send, this, Value, firstProgram);
					}
					else
					{
						Name = input1[0];
						SecondName = input2[0];
						foo = bind(&Operation::SendChar, this, Name, firstProgram);
					}
				}
				else
				{
					Name = input1[0];
					foo = bind(&Operation::Play, this, Name, firstProgram);
				}
			}
			else if (operationType == "set")
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
			else if (operationType == "add")
			{
				if (isInt(input2))
				{
					Name = input1[0];
					Value = stoi(input2);
					foo = bind(&Operation::Add, this, Name, Value, firstProgram);
				}
				else
				{
					Name = input1[0];
					SecondName = input2[0];
					foo = bind(&Operation::AddChar, this, Name, SecondName, firstProgram);
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
			else if (operationType == "mod")
			{
				if (isInt(input2))
				{
					Name = input1[0];
					Value = stoi(input2);
					foo = bind(&Operation::Mod, this, Name, Value, firstProgram);
				}
				else
				{
					Name = input1[0];
					SecondName = input2[0];
					foo = bind(&Operation::ModChar, this, Name, SecondName, firstProgram);
				}
			}
			else if (operationType == "rcv")
			{
				if (secondOption)
				{
					Name = input1[0];
					foo = bind(&Operation::ReceiveChar, this, Name, firstProgram);
				}
				else
				{
					Name = input1[0];
					foo = bind(&Operation::Recover, this, Name, firstProgram);
				}
			}
			else if (operationType == "jgz")
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

		bool Play(char name, bool firstProgram)
		{
			LastPlayed = FindMember(name, firstProgram)->Value;
			return true;
		}

		bool Send(int value, bool firstProgram)
		{
			if (!firstProgram)
				++sended;
			(firstProgram ? inbox2 : inbox1).push_back(value);
			return true;
		};

		bool SendChar(char name, bool firstProgram)
		{
			if (!firstProgram)
				++sended;
			(firstProgram ? inbox2 : inbox1).push_back(FindMember(name, firstProgram)->Value);
			return true;
		};	
		
		bool ReceiveChar(char name, bool firstProgram)
		{
			auto messages = (firstProgram ? &inbox1 : &inbox2);
			if (messages->size() > 0)
			{
				auto it = messages->begin();
				FindMember(name, firstProgram)->Value = messages->front();
				messages->pop_front();
				return true;
			}
			if (firstProgram)
				--position1;
			else
				--position2;
			return false;
		};

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

		bool Add(char name, int value, bool firstProgram)
		{
			FindMember(name, firstProgram)->Value += value;
			return true;
		}

		bool AddChar(char name, char secondName, bool firstProgram)
		{
			FindMember(name, firstProgram)->Value += FindMember(secondName, firstProgram)->Value;
			return true;
		};

		bool Multiply(char name, int value, bool firstProgram)
		{
			FindMember(name, firstProgram)->Value *= value;
			return true;
		}

		bool MultiplyChar(char name, char secondName, bool firstProgram)
		{
			FindMember(name, firstProgram)->Value *= FindMember(secondName, firstProgram)->Value;
			return true;
		};

		bool Mod(char name, int value, bool firstProgram)
		{
			FindMember(name, firstProgram)->Value %= value;
			return true;
		}

		bool ModChar(char name, char secondName, bool firstProgram)
		{
			FindMember(name, firstProgram)->Value %= FindMember(secondName, firstProgram)->Value;
			return true;
		};
		
		bool Recover(char name, bool firstProgram)
		{
			if (FindMember(name, firstProgram)->Value != 0)
			{
				recovered = LastPlayed;
				(firstProgram ? position1 : position2) = 100000000000;
			}
			return true;
		}

		bool Jump(char name, int value, bool firstProgram)
		{
			if (FindMember(name, firstProgram)->Value > 0)
			{
				(firstProgram? position1: position2) += value -1;
			}
			return true;
		}

		bool JumpInts(int value1, int value, bool firstProgram)
		{
			if (value1 > 0)
			{
				(firstProgram ? position1 : position2) += value - 1;
			}
			return true;
		}

		bool JumpChar(char name, char secondName, bool firstProgram)
		{
			if (FindMember(name, firstProgram)->Value > 0)
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
		if (firstProgram)
		{
			Operations1.clear();
			Members1.clear();
			if (secondOption)
				Members2.push_back(Member(0, 'p'));
			ifstream sstream("input18.txt");
			string line;
			while (getline(sstream, line))
			{
				vector<string> ssline = splitString(line);
				if (ssline.size() == 2)
					ssline.push_back("");

				auto it = find_if(Members1.begin(), Members1.end(),
					[ssline](Member const& item)
				{
					return item.Name == ssline[1][0];
				});

				if (it == Members1.end())
				{
					Members1.push_back(Member(0, ssline[1][0]));
				}
				Operations1.push_back(Operation(ssline[0], ssline[1], ssline[2], secondOption, firstProgram));
			}
		}	
		else
		{
			Operations2.clear();
			Members2.clear();
			if (secondOption)
				Members2.push_back(Member(1, 'p'));
			ifstream sstream("input18.txt");
			string line;
			while (getline(sstream, line))
			{
				vector<string> ssline = splitString(line);
				if (ssline.size() == 2)
					ssline.push_back("");

				auto it = find_if(Members2.begin(), Members2.end(),
					[ssline](Member const& item)
				{
					return item.Name == ssline[1][0];
				});

				if (it == Members2.end())
				{
					Members2.push_back(Member(0, ssline[1][0]));
				}
				Operations2.push_back(Operation(ssline[0], ssline[1], ssline[2], secondOption, firstProgram));
			}
		}
	}

	void Run()
	{
		int size = Operations1.size();
		while (position1 < size)
		{
			bool s =Operations1[position1++].foo();
		}
	}
	void RunB()
	{
		bool get1 = true, get2 = true;
		int size = Operations1.size();
		while (get1 || get2)
		{
			get1 = Operations1[position1++].foo();
			get2 = Operations2[position2++].foo();
		}
	}
}

int ex18::Ex18::Run1()
{
	prepareVectors(false, true);
	Run();
	return recovered;
}

int ex18::Ex18::Run2()
{
	position1 = 0;
	position2 = 0;
	sended = 0;
	prepareVectors(true, true); 
	prepareVectors(true, false);
	RunB();
	return sended;
}

