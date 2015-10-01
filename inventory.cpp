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
#include "inventory.h"

namespace gameplay
{
	inventory::inventory(vector<char> slt)
	{
		slots = slt;
		meso = 0;
	}

	void inventory::modify(inventorytype type, short slot, char mode, short arg)
	{
		if (items[type].contains(slot))
		{
			switch (mode)
			{
			case 1:
				items[type].get(slot)->setcount(arg);
				break;
			case 2:
				items[type].changekey(slot, arg);
				break;
			case 3:
				items[type].removekey(slot);
				break;
			}
		}
	}

	void inventory::recalcstats()
	{
		for (equipstat es = ES_STR; es <= ES_JUMP; es = static_cast<equipstat>(es + 1))
		{
			totalstats[es] = 0;
		}

		for (spmit<short, mapleitem*> eqit = items[IVT_EQUIPPED].getit(); eqit.belowtop(); ++eqit)
		{
			mapleequip* equip = reinterpret_cast<mapleequip*>(eqit.get());
			for (equipstat es = ES_STR; es <= ES_JUMP; es = static_cast<equipstat>(es + 1))
			{
				totalstats[es] += equip->getstat(es);
			}
		}
	}

	short inventory::getaccuracy()
	{
		float dexacc = static_cast<float>(totalstats[ES_DEX]) * 0.8f;
		float lukacc = static_cast<float>(totalstats[ES_LUK]) * 0.5f;
		return totalstats[ES_ACC] + static_cast<short>(dexacc + lukacc);
	}

	short inventory::finditem(int id)
	{
		inventorytype type = gettypebyid(id);
		return finditem(type, id);
	}

	short inventory::finditem(inventorytype type, int id)
	{
		short ret = -1;

		for (spmit<short, mapleitem*> itit = items[type].getit(); itit.belowtop(); ++itit)
		{
			if (itit->getid() == id)
			{
				ret = itit.getkey();
				break;
			}
		}

		return ret;
	}

	short inventory::countitem(int id)
	{
		inventorytype type = gettypebyid(id);

		if (type == IVT_EQUIP)
		{
			return 1;
		}
		else
		{
			short ret = 0;

			for (spmit<short, mapleitem*> itit = items[type].getit(); itit.belowtop(); ++itit)
			{
				if (itit->getid() == id)
				{
					ret += itit->getcount();
				}
			}

			return ret;
		}
	}

	mapleequip* inventory::getequip(inventorytype type, short slot)
	{
		if (items[type].contains(slot) && (type == IVT_EQUIP || type == IVT_EQUIPPED))
		{
			return reinterpret_cast<mapleequip*>(items[type].get(slot));
		}
		else
		{
			return 0;
		}
	}
}
