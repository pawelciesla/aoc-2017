#include <set>
#include "ex25.h"

using namespace std;

namespace
{
	enum State
	{
	A=0,
	B,
	C,
	D,
	E,
	F
	};

};

const int iterations = 12861455;

int ex25::Ex25::Run1()
{
	set<int> positions;
	int position = 0;
	State state = State::A;
	for (int i = 0; i < iterations; ++i)
	{
		switch (state)
		{
		case State::A:
		{
						 if (positions.insert(position).second)
						 {
							 ++position;
						 }
						 else
						 {
							 positions.erase(position);
							 --position;
						 }
						 state = State::B;
						 break;
		}
		case State::B:
		{
						 if (positions.insert(position).second)
						 {
							 --position;
							 state = State::C;
						 }
						 else
						 {
							 positions.erase(position);
							 ++position;
							 state = State::E;
						 }
						 break;
		}
		case State::C:
		{
						 if (positions.insert(position).second)
						 {
							 ++position;
							 state = State::E;
						 }
						 else
						 {
							 positions.erase(position);
							 --position;
							 state = State::D;
						 }
						 break;
		}
		case State::D:
		{
						 positions.insert(position);
						 --position;
						 state = State::A;
						 break;
		}
		case State::E:
		{
						 if (positions.insert(position).second)
						 {
							 state = State::A;
						 }
						 else
						 {
							 state = State::F;
						 }
						 positions.erase(position);
						 ++position;
						 break;
		}
		case State::F:
		{
						 if (positions.insert(position).second)
						 {
							 state = State::E;
						 }
						 else
						 {
							 state = State::A;
						 }
						 ++position;
						 break;
		}
		}
	}
	return positions.size();
}

int ex25::Ex25::Run2()
{
	return 0;
}

