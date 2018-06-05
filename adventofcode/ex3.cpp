#include <cmath>
#include <vector>
#include "ex3.h"

using namespace std;

namespace
{
	int whichCircle(int input)
	{
		int circle = 0;
		for (int i = 1; i < 10000; i += 2)
		{
			if (i*i >= input)
			{
				return circle;
			}
			circle++;
		}
		return 0;
	}
	struct point
	{
		int x, y, value;
		point(int _x, int _y, int _value)
		{
			x = _x;
			y = _y;
			value = _value;
		}
	};

	int whichCircle2(int input)
	{
		for (int i = 1; i < 10000; i += 2)
		{
			if (i*i >= input)
			{
				return i - 2;
			}
		}
		return 0;
	}
	int calculateLength(int input)
	{
		if (input <= 1)
			return 0;

		const int circle = whichCircle2(input);
		int cir = whichCircle(input);
		point pt(cir, 1 - cir, circle*circle + 1);
		int circleLength = circle;
		int xMove = -1;
		int YMove = 1;
		int moveLength = circle;
		bool moveY = true;
		int moveLeftLength = moveLength;

		while (pt.value != input)
		{
			if (moveLeftLength > 0)
			{
				if (moveY)
				{
					pt.y += YMove;
				}
				else
				{
					pt.x += xMove;
				}
				pt.value++;
				moveLeftLength--;

			}
			else
			{
				if (moveY)
				{
					YMove = YMove* (-1);
					moveLength++;
				}
				else
				{
					xMove = xMove*(-1);
				}
				moveLeftLength = moveLength;
				moveY = !moveY;

			}
		}
		return abs(pt.x) + abs(pt.y);

	}

	int getHigher(int input)
	{
		if (input <= 1)
			return 0;

		const int snakelength = 101;
		int snake[snakelength][snakelength];
		for (int i = 0; i < snakelength; ++i)
		{
			for (int j = 0; j < snakelength; ++j)
			{
				snake[i][j] = 0;
			}
		}

		point pt(0, 0, 1);
		snake[(snakelength - 1) / 2 + pt.x][(snakelength - 1) / 2 + pt.y] = pt.value;
		int xMove = 1;
		int YMove = -1;
		int moveLength = 1;
		bool moveY = false;
		int moveLeftLength = moveLength;

		while (pt.value <= input)
		{
			if (moveLeftLength > 0)
			{
				if (moveY)
				{
					pt.y += YMove;
				}
				else
				{
					pt.x += xMove;
				}
				int xPos = (snakelength - 1) / 2 + pt.x;
				int yPos = (snakelength - 1) / 2 + pt.y;
				pt.value = snake[yPos - 1][xPos - 1] + snake[yPos - 1][xPos] + snake[yPos - 1][xPos + 1] +
					snake[yPos][xPos-1] + snake[yPos][xPos] + snake[yPos][xPos+1] +
					snake[yPos+1][xPos-1] + snake[yPos+1][xPos] + snake[yPos+1][xPos+1];

				snake[yPos][xPos] = pt.value;
				moveLeftLength--;

			}
			else
			{
				if (moveY)
				{
					YMove = YMove* (-1);
					moveLength++;
				}
				else
				{
					xMove = xMove*(-1);
				}
				moveLeftLength = moveLength;
				moveY = !moveY;

			}
		}
		return pt.value;
	}
}
int ex3::Ex3::Run1()
{
	return calculateLength(289326);
}


int ex3::Ex3::Run2()
{ 
	return getHigher(289326);
}
