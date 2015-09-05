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
#pragma once
#include "stdfax.h"
#include "mapleitem.h"
#include "mapleequip.h"

using namespace std;

namespace gameplay
{
	enum inventorytype : char
	{
		ivt_equips = -1,
		ivt_equip = 0,
		ivt_use = 1,
		ivt_setup = 2,
		ivt_etc = 3,
		ivt_cash = 4,
		ivt_equipped = 5,
		ivt_equippedcash = 6
	};

	class inventory
	{
	public:
		inventory(vector<char>, map<short, mapleequip>, map<short, mapleequip>, map<short, mapleequip>, map<char, mapleitem>, map<char, mapleitem>, map<char, mapleitem>, map<char, mapleitem>);
		inventory() {}
		~inventory() {}
		void recalcstats();
		void removeitem(inventorytype, short);
		short countitem(int);
		map<short, mapleequip>* getequipped() { return &equipped; }
		map<short, mapleequip>* getequippedcash() { return &equippedcash; }
		float getwepmult() { return wepmultiplier; }
		short gettotal(equipstat es) { return totalstats[es]; }
		mapleequip* getequip(short s) { return (equipped.count(s)) ? &equipped[s] : 0; }
	private:
		vector<char> slots;
		bool twohandedwep;
		float wepmultiplier;
		map<equipstat, short> totalstats;
		map<inventorytype, map<short, mapleitem>> inventories;
		map<short, mapleequip> equipped;
		map<short, mapleequip> equippedcash;
		map<short, mapleequip> equips;
		map<char, mapleitem> useitems;
		map<char, mapleitem> setupitems;
		map<char, mapleitem> etcitems;
		map<char, mapleitem> cashitems;
		SRWLOCK itemlock;
	};
}

