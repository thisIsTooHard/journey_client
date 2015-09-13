#include "skillbook.h"

namespace character
{
	skillbook::skillbook(map<int, int> lvs, map<int, int> mlvs, map<int, int> cds, map<int, int64_t> exps)
	{
		levels = lvs;
		m_levels = mlvs;
		cooldowns = cds;
		expirations = exps;
	}

	void skillbook::updateskill(int id, int lv, int mlv, int64_t exp)
	{
		levels[id] = lv;
		m_levels[id] = mlv;
		expirations[id] = exp;
	}
}
