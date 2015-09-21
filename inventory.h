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
#include "safeptrmap.h"

using namespace util;

namespace gameplay
{
	enum inventorytype : char
	{
		IVT_EQUIPPED = -1,
		IVT_NONE = 0,
		IVT_EQUIP = 1,
		IVT_USE = 2,
		IVT_SETUP = 3,
		IVT_ETC = 4,
		IVT_CASH = 5
	};

	class inventory
	{
	public:
		inventory(vector<char>);
		inventory() {}
		~inventory() { items.clear(); }
		void recalcstats();
		short countitem(int);
		short getprimstat(short);
		short getsecstat(short);
		short getaccuracy();
		short finditem(int);
		short finditem(inventorytype, int);
		mapleequip* getequip(inventorytype, short);
		mapleitem* getitem(inventorytype t, short s) { return items[t].get(s); }
		void additem(mapleitem* i, inventorytype t) { items[t].add(i->getpos(), i); }
		void removeitem(inventorytype t, short s) { items[t].removekey(s); }
		short gettotal(equipstat es) { return totalstats[es]; }
		inventorytype gettypebyid(int id) { return static_cast<inventorytype>(id / 1000000); }
		spmit<short, mapleitem*> getinventory(inventorytype t) { return items[t].getit(); }
	private:
		map<inventorytype, safeptrmap<short, mapleitem*>> items;
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

