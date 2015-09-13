#pragma once
#include "stdfax.h"

using namespace std;

namespace character
{
	class skillbook
	{
	public:
		skillbook(map<int, int>, map<int, int>, map<int, int>, map<int, int64_t>);
		skillbook() {}
		~skillbook() {}
		int getlevel(int s) { return levels[s]; }
		int getmaster(int s) { return m_levels[s]; }
		int getcd(int s) { return cooldowns.count(s) ? cooldowns[s] : 0; }
		int64_t getexpire(int s) { return expirations[s]; }
		void updateskill(int, int, int, int64_t);
	private:
		map<int, int> levels;
		map<int, int> m_levels;
		map<int, int> cooldowns;
		map<int, int64_t> expirations;
	};
}

