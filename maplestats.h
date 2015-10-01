/////////////////////////////////////////////////////////////////////////////
// This file is part of the Journey MMORPG client                           //
// Copyright � 2015 SYJourney                                               //
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
#pragma once
#include "stdfax.h"

using namespace std;

namespace gameplay
{
	enum maplestat
	{
		MS_SKIN = 0x1,
		MS_FACE = 0x2,
		MS_HAIR = 0x4,
		MS_LEVEL = 0x10,
		MS_JOB = 0x20,
		MS_STR = 0x40,
		MS_DEX = 0x80,
		MS_INT = 0x100,
		MS_LUK = 0x200,
		MS_HP = 0x400,
		MS_MAXHP = 0x800,
		MS_MP = 0x1000,
		MS_MAXMP = 0x2000,
		MS_AP = 0x4000,
		MS_SP = 0x8000,
		MS_EXP = 0x10000,
		MS_FAME = 0x20000,
		MS_MESO = 0x40000,
		MS_PET = 0x180008,
		MS_GACHAEXP = 0x200000
	};

	enum weapontype
	{
		WEP_NONE = 0,
		WEP_1H_SWORD = 130,
		WEP_1H_AXE = 131,
		WEP_1H_MACE = 132,
		WEP_DAGGER = 133,
		WEP_WAND = 137,
		WEP_STAFF = 138,
		WEP_2H_SWORD = 140,
		WEP_2H_AXE = 141,
		WEP_2H_MACE = 142,
		WEP_SPEAR = 143,
		WEP_POLEARM = 144,
		WEP_BOW = 145,
		WEP_CROSSBOW = 146,
		WEP_CLAW = 147,
		WEP_KNUCKLE = 148,
		WEP_GUN = 149,
		WEP_CASH = 170
	};

	const maplestat statvalues[20] = { MS_SKIN, MS_FACE, MS_HAIR, MS_LEVEL, MS_JOB, MS_STR, MS_DEX, MS_INT, MS_LUK, MS_HP, MS_MAXHP, MS_MP, MS_MAXMP, MS_AP, MS_SP, MS_EXP, MS_FAME, MS_MESO, MS_PET, MS_GACHAEXP };

	const int exptable[201] = { 1, 15, 34, 57, 92, 135, 372, 560, 840, 1242, 1144, 1573, 2144, 2800, 3640, 4700, 5893, 7360, 9144, 11120, 13477, 16268, 19320, 22880, 27008, 31477, 36600, 42444, 48720, 55813, 63800, 86784, 98208, 110932, 124432, 139372, 155865, 173280, 192400, 213345, 235372, 259392, 285532, 312928, 342624, 374760, 408336, 445544, 483532, 524160, 567772, 598886, 631704, 666321, 702836, 741351, 781976, 824828, 870028, 917625, 967995, 1021041, 1076994, 1136013, 1198266, 1263930, 1333194, 1406252, 1483314, 1564600, 1650340, 1740778, 1836173, 1936794, 2042930, 2154882, 2272970, 2397528, 2528912, 2667496, 2813674, 2967863, 3130502, 3302053, 3483005, 3673873, 3875201, 4087562, 4311559, 4547832, 4797053, 5059931, 5337215, 5629694, 5938202, 6263614, 6606860, 6968915, 7350811, 7753635, 8178534, 8626718, 9099462, 9598112, 10124088, 10678888, 11264090, 11881362, 12532461, 13219239, 13943653, 14707765, 15513750, 16363902, 17260644, 18206527, 19204245, 20256637, 21366700, 22537594, 23772654, 25075395, 26449526, 27898960, 29427822, 31040466, 32741483, 34535716, 36428273, 38424542, 40530206, 42751262, 45094030, 47565183, 50171755, 52921167, 55821246, 58880250, 62106888, 65510344, 69100311, 72887008, 76881216, 81094306, 85594273, 90225770, 95170142, 100385466, 105886589, 111689174, 117809740, 124265714, 131075474, 138258410, 145834970, 153826726, 162256430, 171148082, 180526997, 190419876, 200854885, 211861732, 223471711, 223471711, 248635353, 262260570, 276632449, 291791906, 307782102, 324648562, 342439302, 361204976, 380999008, 401877754, 423900654, 447130410, 471633156, 497478653, 524740482, 553496261, 583827855, 615821622, 649568646, 685165008, 722712050, 762316670, 804091623, 848155844, 894634784, 943660770, 995373379, 1049919840, 1107455447, 1168144006, 1232158297, 1299680571, 1370903066, 1446028554, 1525246918, 1608855764, 1697021059 };

	class maplestats
	{
	public:
		maplestats(int, string, int, map<maplestat, short>, pair<int, char>, vector<int64_t>);
		maplestats() {}
		~maplestats() {}
		short getprim(weapontype);
		short getsec(weapontype);
		short getaccuracy();
		void calcdamage(short, short, short);
		string getjobname(short);
		string getjobname() { return getjobname(stats[MS_JOB]); }
		short getstat(maplestat s) { return stats.count(s) ? stats[s] : 0; }
		short gettotal(maplestat s) { return totalstats.count(s) ? totalstats[s] : 0; }
		void setstat(maplestat s, short v) { stats[s] = v; }
		void settotal(maplestat t, short v) { totalstats[t] = v; }
		void setexp(int v) { exp = v; }
		void setattack(short v) { attack = v; }
		float getmastery() { return mastery; }
		float getcritical() { return critical; }
		float getmincrit() { return mincrit; }
		float getmaxcrit() { return maxcrit; }
		float getbossdmg() { return bossdmg; }
		float getignoredef() { return ignoredef; }
		float getstance() { return stance; }
		float getresist() { return resiststatus; }
		int getmaxdamage() { return maxdamage; }
		int getmindamage() { return mindamage; }
		short getattack() { return attack; }
		short gethonor() { return honor; }
		int getid() { return id; }
		int getexp() { return exp; }
		int getexpneeded() { return exptable[stats[MS_LEVEL]]; }
		string getname() { return name; }
		pair<int, char> getspawninfo() { return spawninfo; }
		maplestat statvalue(char s) { return statvalues[s]; }
	private:
		int id;
		string name;
		int maxdamage;
		int mindamage;
		short attack;
		short honor;
		float mastery;
		float critical;
		float mincrit;
		float maxcrit;
		float bossdmg;
		float ignoredef;
		float stance;
		float resiststatus;
		int exp;
		map<maplestat, short> stats;
		map<maplestat, short> totalstats;
		pair<int, char> spawninfo;
		vector<int64_t> petids;
	};
}

