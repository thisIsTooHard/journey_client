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
#include "inventory.h"
#include "gameconstants.h"

namespace gameplay
{
	inventory::inventory(vector<char> slt, map<short, mapleequip> eq, map<short, mapleequip> eqc, map<short, mapleequip> e, map<char, mapleitem> ui, map<char, mapleitem> si, map<char, mapleitem> ei, map<char, mapleitem> ci)
	{
		slots = slt;
		equipped = eq;
		equippedcash = eqc;
		equips = e;
		useitems = ui;
		setupitems = si;
		etcitems = ei;
		cashitems = ci;
		itemlock = SRWLOCK_INIT;
	}

	void inventory::recalcstats()
	{
		AcquireSRWLockShared(&itemlock);
		for (equipstat es = ES_STR; es <= ES_JUMP; es = static_cast<equipstat>(es + 1))
		{
			totalstats[es] = 0;
		}

		for (map<short, mapleequip>::iterator eqit = equipped.begin(); eqit != equipped.end(); ++eqit)
		{
			for (equipstat es = ES_STR; es <= ES_JUMP; es = static_cast<equipstat>(es + 1))
			{
				totalstats[es] += eqit->second.getstat(es);
			}
		}

		wepmultiplier = 1.5f;
		ReleaseSRWLockShared(&itemlock);
	}

	void inventory::removeitem(inventorytype type, short slot)
	{
		AcquireSRWLockExclusive(&itemlock);
		switch (type)
		{
		case ivt_equips:
			equipped.erase(slot);
			break;
		case ivt_equip:
			equips.erase(slot);
			break;
		case ivt_use:
			useitems.erase(slot);
			break;
		case ivt_setup:
			setupitems.erase(slot);
			break;
		case ivt_etc:
			etcitems.erase(slot);
			break;
		case ivt_cash:
			cashitems.erase(slot);
			break;
		}
		ReleaseSRWLockExclusive(&itemlock);
	}

	short inventory::countitem(int id)
	{
		short ret = 1;

		inventorytype type = util::getinvtype(id);
		switch (type)
		{
		case ivt_use:
			for (map<char, mapleitem>::iterator ivit = useitems.begin(); ivit != useitems.end(); ++ivit)
			{
				if (ivit->second.getid() == id)
				{
					ret += ivit->second.getcount();
				}
			}
			break;
		case ivt_setup:
			for (map<char, mapleitem>::iterator ivit = setupitems.begin(); ivit != setupitems.end(); ++ivit)
			{
				if (ivit->second.getid() == id)
				{
					ret += ivit->second.getcount();
				}
			}
			break;
		case ivt_etc:
			for (map<char, mapleitem>::iterator ivit = etcitems.begin(); ivit != etcitems.end(); ++ivit)
			{
				if (ivit->second.getid() == id)
				{
					ret += ivit->second.getcount();
				}
			}
			break;
		case ivt_cash:
			for (map<char, mapleitem>::iterator ivit = cashitems.begin(); ivit != cashitems.end(); ++ivit)
			{
				if (ivit->second.getid() == id)
				{
					ret += ivit->second.getcount();
				}
			}
			break;
		}

		return ret;
	}
}
