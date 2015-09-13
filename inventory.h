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
#include "mapleitem.h"
#include "mapleequip.h"

using namespace std;

namespace gameplay
{
	enum inventorytype : char
	{
		IVT_EQUIPPED = -1,
		IVT_EQUIP = 0,
		IVT_USE = 1,
		IVT_SETUP = 2,
		IVT_ETC = 3,
		IVT_CASH = 4,
		IVT_CLOTHES = 5,
		IVT_CASHCLOTHES = 6,
		IVT_NONE = 7
	};

	class inventory
	{
	public:
		inventory(vector<char>, map<short, mapleequip>, map<short, mapleequip>, map<short, mapleequip>, map<char, mapleitem>, map<char, mapleitem>, map<char, mapleitem>, map<char, mapleitem>);
		inventory() {}
		~inventory() {}
		void removeitem(inventorytype, short);
		void recalcstats();
		short countitem(int);
		short getprimstat(short);
		short getsecstat(short);
		short getaccuracy();
		short finditem(int);
		short finditem(inventorytype, int);
		const float getwmult();
		const inventorytype gettypebyid(int);
		short gettotal(equipstat es) { return totalstats[es]; }
		map<short, mapleequip>* getequipped() { return &equipped; }
		map<short, mapleequip>* getequippedcash() { return &equippedcash; }
		mapleequip* getequip(short s) { return (equipped.count(s)) ? &equipped[s] : 0; }
	private:
		vector<char> slots;
		map<equipstat, short> totalstats;
		map<short, mapleequip> equipped;
		map<short, mapleequip> equippedcash;
		map<short, mapleequip> equips;
		map<char, mapleitem> useitems;
		map<char, mapleitem> setupitems;
		map<char, mapleitem> etcitems;
		map<char, mapleitem> cashitems;
	};
}

