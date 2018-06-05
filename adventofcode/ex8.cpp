#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <set>

#include "ex8.h"

using namespace std;
const string fileName = "input8.txt";

namespace
{
	int maximum = 0;
	struct Element
	{
		string Name;
		int Value;

		Element(string _name, int _value)
		{
			Name = _name;
			Value = _value;
		}

		Element(string _name)
		{
			Name = _name;
			Value = 0;
		}

		bool operator()(const Element & element) 
		{
			return element.Name == Name;
		}
	};

	bool compareElements(const Element& left, const Element& right)
	{
		return left.Name < right.Name;
	}

	bool checkLogic(string comparer, int value, int secondValue)
	{
		if (comparer == "==")
		{
			return value == secondValue;
		}
		else if (comparer == "!=")
		{
			return value != secondValue;
		}
		else if (comparer == ">")
		{
			return value > secondValue;
		}
		else if (comparer == ">=")
		{
			return value >= secondValue;
		}
		else if (comparer == "<=")
		{
			return value <= secondValue;
		}
		else if (comparer == "<")
		{
			return value < secondValue;
		}
		return false;
	}

	int increment(string inc, int value)
	{
		if (inc == "inc")
		{
			return value;
		}
		else 
		{
			return 0 - value;
		}
	}

	void analyzeLine(set<Element, bool(*)(const Element&, const Element&)>& wholeElements, vector<string>& strings)
	{
		auto it = wholeElements.insert(Element(strings[4])).first;
		if (checkLogic(strings[5], it->Value, stoi(strings[6])))
		{
			it = wholeElements.insert(Element(strings[0])).first;
			int value = it->Value;
			if (value > maximum)
			{
				maximum = value;
			}
			wholeElements.erase(it);
			wholeElements.insert(Element(strings[0], value + increment(strings[1], stoi(strings[2]))));
		}
	}

	void readFile(set<Element, bool(*)(const Element&, const Element&)>& wholeElements)
	{
		ifstream file(fileName);
		string line;
		string number;

		if (file.is_open())
		{
			while (getline(file, line))
			{
				vector<string> elements;
				stringstream stream(line);

				while (stream >> number)
				{
					elements.push_back(number);
				}
				analyzeLine(wholeElements, elements);
			}
		}
	}
}

int ex8::Ex8::Run1()
{
	int checksum = 0;

	set<Element, bool(*)(const Element&, const Element&)> wholeElements(compareElements);
	readFile(wholeElements);

	return max_element(wholeElements.begin(), wholeElements.end(), [](const Element &a, const Element &b)
	{
		return a.Value < b.Value;
	})->Value;
}

int ex8::Ex8::Run2()
{
	return maximum;
}
