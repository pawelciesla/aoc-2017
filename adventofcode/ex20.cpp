#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "ex20.h"
using namespace std;

namespace
{
	struct point
	{
		vector<long long int> xyz;
		point(int _x, int _y, int _z) 
		{
			xyz.insert(xyz.begin(),{ _x, _y, _z});
		}

		point& operator +(const point& pt)
		{
			xyz[0] += pt.xyz[0];
			xyz[1] += pt.xyz[1];
			xyz[2] += pt.xyz[2];
			return *this;
			//return this;
		}
	};
	struct particle
	{
		long long int minimumLen = 999999;
		point p, v, a;
		particle(point _p, point _v, point _a) : p(_p), v(_v), a(_a) {}
		
		void doMove()
		{
			v = v + a;
			p = p + v;
		}
		 int getAccceleration() const
		{
			 return abs(a.xyz[0]) + abs(a.xyz[1]) + abs(a.xyz[2]);
		}
		int getPosition() const
		{
			return p.xyz[0] + p.xyz[1] + p.xyz[2];
		}
		int getSpeed() const
		{
			return abs(v.xyz[0]) + abs(v.xyz[1]) + abs(v.xyz[2]);
		}

	};

	bool compareParticlesAcceleraton(const particle& p1, const particle& p2)
	{
		return p1.getAccceleration() < p2.getAccceleration();
	}

	bool ParticlesAreEquals(const particle& p1, const particle& p2)
	{
		return p1.p.xyz[0] == p2.p.xyz[0] && p1.p.xyz[1] == p2.p.xyz[1] && p1.p.xyz[2] == p2.p.xyz[2];
	}

	bool compareParticles(const particle& p1, const particle& p2)
	{
		return p1.getPosition() < p2.getPosition();
	}

	bool compareSpeeds(const particle& p1, const particle& p2)
	{
		return p1.getSpeed() < p2.getSpeed();
	}

	vector<particle> particles;
	void readFile()
	{
		particles.clear();

		ifstream sstream("input20.txt");
		string line;
		while (getline(sstream, line))
		{
			vector<int>values;
			int index = 0;
			int stringLength = line.length();
			for (int i = 0; i < 3; ++i)
			{
				int indexOpen = line.find('<', index) + 1;
				index = line.find('>', indexOpen);
				int length = index - indexOpen;
				string tmpString = line.substr(indexOpen, length);
				int indexTmp = tmpString.find(',');
				string s1 = tmpString.substr(0, indexTmp++); 
				values.push_back(stoi(s1));
				tmpString = tmpString.substr(indexTmp);
				indexTmp = tmpString.find(',');
				s1 = tmpString.substr(0, indexTmp++);
				values.push_back(stoi(s1));
				s1 = tmpString.substr(indexTmp);
				values.push_back(stoi(s1));
			}
			particles.push_back(particle(point(values[0], values[1], values[2]), point(values[3], values[4], values[5]), point(values[6], values[7], values[8])));
		}
	}
	int getMinimumAcceleration()
	{
		for (auto& it : particles)
		{
			for (int i = 0; i < 10000;++i)
				it.doMove();
		}
		auto it = min_element(particles.begin(), particles.end(), compareSpeeds);
		return it - particles.begin();
	}
	int removeCollisions()
	{

		auto size = particles.size();
		for (int i = 0; i < 10000; ++i)
		{
			map<vector<long long int>, int> indexes;
			for (auto it : particles)
			{
				indexes[(it.p.xyz)]++;
			}

			for (auto it : indexes)
			{
				if (it.second > 1)
				{
					for (int i = 0; i < size; ++i)
					{
						if (particles[i].p.xyz == it.first)
						{
							particles.erase(particles.begin() + i--);
							--size;
						}
					}
				}
			}

			for (auto& it : particles)
			{
				it.doMove();
			}
		}
		return size;
	}
}

int ex20::Ex20::Run1()
{
	readFile();
	return getMinimumAcceleration();
	return 0;
}

int ex20::Ex20::Run2()
{
	readFile();
	return removeCollisions();
	return 0;
}

