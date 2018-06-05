#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <deque>
#include <queue>
#include<iomanip>
#include <bitset>

#include "ex15.h"

using namespace std;

namespace
{
	short int startA = 883;
	short int startB = 879;
	int multiplyA = 16807;
	int multiplyB = 48271;
	int mod = 2147483647;
	int mod2 = 65536;
	const int length = 40000000;
	const int length2 = 5000000;
}


int ex15::Ex15::Run1()
{
	int matches = 0;
	unsigned long long int valueA = startA;
	unsigned long long int valueB = startB;
	
	for (int i = 0; i < length; ++i)
	{
		valueA = valueA * multiplyA % mod;
		valueB = valueB * multiplyB % mod;
		if (valueA%mod2 == valueB%mod2)
		{
			++matches;
		}
	}
	return matches;
}

int ex15::Ex15::Run2()
{
	int matches = 0;
	unsigned long long int valueA = startA;
	unsigned long long int valueB = startB;

	for (int i = 0; i < length2; ++i)
	{
		while ((valueA = valueA * multiplyA % mod) % 4 != 0);
		while ((valueB = valueB * multiplyB % mod) % 8 != 0);

		if (valueA%mod2 == valueB%mod2)
		{
			++matches;
		}
	}
	return matches;
}

