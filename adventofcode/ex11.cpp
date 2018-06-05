#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "ex11.h"

#define queuelength 256
using namespace std;
const string input = "input11.txt";

namespace
{
	int se, sw, nw, ne, n, s;
	void getInput()
	{
		se = 0;
		sw = 0;
		nw = 0;
		ne = 0;
		n = 0;
		s = 0;

		ifstream fstream(input);

		//stringstream sstream(input);
		string direction;
		while (getline(fstream, direction, ','))
		{
			if (direction == "se")
			{
				++se;
			}
			else if (direction == "sw")
			{
				++sw;
			}
			else if (direction == "nw")
			{
				++nw;
			}
			else if (direction == "ne")
			{
				++ne;
			}
			else if (direction == "s")
			{
				++s;
			}
			else if (direction == "n")
			{
				++n;
			}
		}
	}
	
	void calculate()
	{
		while (n > 0 && s>0)
		{
			--n;
			--s;
		}
		while (ne > 0 && sw>0)
		{
			--ne;
			--sw;
		}
		while (nw > 0 && se>0)
		{
			--nw;
			--se;
		}
		while (ne > 0 && s>0)
		{
			--ne;
			--s;
			++se;
		}
		while (nw > 0 && s>0)
		{
			--nw;
			--s;
			++sw;
		}
		while (se > 0 && n>0)
		{
			--se;
			--n;
			++ne;
		}
		while (sw > 0 && n>0)
		{
			--sw;
			--n;
			++nw;
		}
		while (sw > 0 && se>0)
		{
			--sw;
			--se;
			++s;
		}
		while (nw > 0 && ne>0)
		{
			--nw;
			--ne;
			++n;
		}
	}

	int get_input2()
	{
		int max = 0;
		se = 0;
		sw = 0;
		nw = 0;
		ne = 0;
		n = 0;
		s = 0;

		ifstream fstream(input);

		//stringstream sstream(input);
		string direction;
		while (getline(fstream, direction, ','))
		{
			if (direction == "se")
			{
				++se;
			}
			else if (direction == "sw")
			{
				++sw;
			}
			else if (direction == "nw")
			{
				++nw;
			}
			else if (direction == "ne")
			{
				++ne;
			}
			else if (direction == "s")
			{
				++s;
			}
			else if (direction == "n")
			{
				++n;
			}
			calculate();
			int sum = se + n + sw + s + nw + ne;
			if (sum > max)
			{
				max = sum;
			}
		}
		return max;
	}
}

int ex11::Ex11::Run1()
{
	getInput();
	calculate();
	return se+n+sw+s+nw+ne;
}

int ex11::Ex11::Run2()
{
	return get_input2();
}
