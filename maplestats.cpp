/////////////////////////////////////////////////////////////////////////////
// This file is part of the Journey MMORPG client                           //
// Copyright © 2015 SYJourney                                               //
//                                                                          //
// This program is free software: you can redistribute it and/or modify     //
// it under the terms of the GNU Affero General Public License as           //
// published by the Free Software Foundation, either version 3 of the       //
// License, or (at your option) any later version.                          //
//                                                                          //
// This program is distributed in the hope that it will be useful,          //
// but WITHOUT ANY WARRANTY; without even the implied warranty of           //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            //
// GNU Affero General Public License for more details.                      //
//                                                                          //
// You should have received a copy of the GNU Affero General Public License //
// along with this program.  If not, see <http://www.gnu.org/licenses/>.    //
//////////////////////////////////////////////////////////////////////////////
#include "maplestats.h"

namespace gameplay
{
	maplestats::maplestats(int i, string nm, bool fem, short sk, int fc, int hr, int ep, short fm, map<maplestat, short> st, pair<int, char> wi, vector<int64_t> pets)
	{
		id = i;
		name = nm;
		female = fem;
		skin = sk;
		face = fc;
		hair = hr;
		exp = ep;
		fame = fm;
		stats = st;
		spawninfo = wi;
		petids = pets;

		maxdamage = 0;
		mindamage = 0;
		totalmaxhp = 0;
		totalmaxmp = 0;
		mastery = 0.5f;
		critical = 0.05f;
	}

	void maplestats::calcdamage(short prim, short sec, short watk)
	{
		maxdamage = static_cast<int>(prim + sec) * (static_cast<float>(watk) / 100);
		mindamage = static_cast<int>((prim * 0.9 * mastery) + sec) * (static_cast<float>(watk) / 100);
	}

	short maplestats::getstat(maplestat s) 
	{ 
		return (stats.count(s)) ? stats[s] : 0;
	}

	short maplestats::getprim(short weapon)
	{
		if (weapon > 0)
		{
			switch (getstat(JOB) / 100)
			{
			case 0:
			case 1:
			case 20:
			case 21:
				return getstat(STR);
			case 2:
				return getstat(INT_);
			case 3:
				return getstat(DEX);
			case 4:
				return getstat(LUK);
			case 5:
				return (weapon == 149) ? getstat(DEX) : getstat(STR);
			}
		}

		return 0;
	}

	short maplestats::getsec(short weapon)
	{
		if (weapon > 0)
		{
			switch (getstat(JOB) / 100)
			{
			case 0:
			case 1:
			case 20:
			case 21:
				return getstat(DEX);
			case 2:
				return getstat(LUK);
			case 3:
				return getstat(STR);
			case 4:
				return getstat(DEX);
			case 5:
				return (weapon == 149) ? getstat(STR) : getstat(DEX);
			}
		}

		return 0;
	}

	short maplestats::getaccuracy()
	{
		float dexacc = static_cast<float>(stats[DEX]) * 0.8f;
		float lukacc = static_cast<float>(stats[LUK]) * 0.5f;
		return static_cast<short>(dexacc + lukacc);
	}

	const string maplestats::getjobname()
	{
		switch (stats[JOB])
		{
		case 0:
			return "Beginner";
		case 100:
			return "Swordsman";
		case 110:
			return "Fighter";
		case 111:
			return "Crusader";
		case 112:
			return "Hero";
		case 120:
			return "Page";
		case 121:
			return "White Knight";
		case 122:
			return "Paladin";
		case 130:
			return "Spearman";
		case 131:
			return "Dragon Knight";
		case 132:
			return "Dark Knight";
		case 200:
			return "Magician";
		case 210:
			return "Wizard (F/P)";
		case 211:
			return "Mage (F/P)";
		case 212:
			return "Archmage (F/P)";
		case 220:
			return "Wizard (I/L)";
		case 221:
			return "Mage (I/L)";
		case 222:
			return "Archmage (I/L)";
		case 230:
			return "Cleric";
		case 231:
			return "Priest";
		case 232:
			return "Bishop";
		case 300:
			return "Archer";
		case 310:
			return "Hunter";
		case 311:
			return "Ranger";
		case 312:
			return "Bowmaster";
		case 320:
			return "Crossbowman";
		case 321:
			return "Sniper";
		case 322:
			return "Marksman";
		case 400:
			return "Rogue";
		case 410:
			return "Assassin";
		case 411:
			return "Hermit";
		case 412:
			return "Nightlord";
		case 420:
			return "Bandit";
		case 421:
			return "Chief Bandit";
		case 422:
			return "Shadower";
		case 500:
			return "Pirate";
		case 510:
			return "Brawler";
		case 511:
			return "Marauder";
		case 512:
			return "Buccaneer";
		case 520:
			return "Gunslinger";
		case 521:
			return "Outlaw";
		case 522:
			return "Corsair";
		case 2000:
		case 2100:
		case 2110:
		case 2111:
		case 2112:
			return "Aran";
		}

		return "";
	}
}
