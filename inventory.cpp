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
	}

	void inventory::recalcstats()
	{
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
	}

	short inventory::getaccuracy()
	{
		float dexacc = static_cast<float>(totalstats[ES_DEX]) * 0.8f;
		float lukacc = static_cast<float>(totalstats[ES_LUK]) * 0.5f;
		return totalstats[ES_ACC] + static_cast<short>(dexacc + lukacc);
	}

	void inventory::removeitem(inventorytype type, short slot)
	{
		switch (type)
		{
		case IVT_EQUIPPED:
			equipped.erase(slot);
			break;
		case IVT_EQUIP:
			equips.erase(slot);
			break;
		case IVT_USE:
			useitems.erase(slot);
			break;
		case IVT_SETUP:
			setupitems.erase(slot);
			break;
		case IVT_ETC:
			etcitems.erase(slot);
			break;
		case IVT_CASH:
			cashitems.erase(slot);
			break;
		}
	}

	short inventory::finditem(int id)
	{
		inventorytype type = gettypebyid(id);
		return finditem(type, id);
	}

	short inventory::finditem(inventorytype type, int id)
	{
		short ret = -1;

		switch (type)
		{
		case IVT_USE:
			for (map<char, mapleitem>::iterator ivit = useitems.begin(); ivit != useitems.end(); ++ivit)
			{
				if (ivit->second.getid() == id)
				{
					ret = ivit->first;
					break;
				}
			}
			break;
		}

		return ret;
	}

	short inventory::countitem(int id)
	{
		short ret = 0;

		inventorytype type = gettypebyid(id);
		switch (type)
		{
		case IVT_USE:
			for (map<char, mapleitem>::iterator ivit = useitems.begin(); ivit != useitems.end(); ++ivit)
			{
				if (ivit->second.getid() == id)
				{
					ret += ivit->second.getcount();
				}
			}
			break;
		case IVT_SETUP:
			for (map<char, mapleitem>::iterator ivit = setupitems.begin(); ivit != setupitems.end(); ++ivit)
			{
				if (ivit->second.getid() == id)
				{
					ret += ivit->second.getcount();
				}
			}
			break;
		case IVT_ETC:
			for (map<char, mapleitem>::iterator ivit = etcitems.begin(); ivit != etcitems.end(); ++ivit)
			{
				if (ivit->second.getid() == id)
				{
					ret += ivit->second.getcount();
				}
			}
			break;
		case IVT_CASH:
			for (map<char, mapleitem>::iterator ivit = cashitems.begin(); ivit != cashitems.end(); ++ivit)
			{
				if (ivit->second.getid() == id)
				{
					ret += ivit->second.getcount();
				}
			}
			break;
		case IVT_EQUIP:
			ret = 1;
			break;
		}

		return ret;
	}

	short inventory::getprimstat(short job)
	{
		if (equipped.count(11))
		{
			switch (job / 100)
			{
			case 0:
			case 1:
			case 20:
			case 21:
				return gettotal(ES_STR);
			case 2:
				return gettotal(ES_INT);
			case 3:
				return gettotal(ES_DEX);
			case 4:
				return gettotal(ES_LUK);
			case 5:
				return (equipped[11].getid() / 10000 == 149) ? gettotal(ES_DEX) : gettotal(ES_STR);
			}
		}

		return 0;
	}

	short inventory::getsecstat(short job)
	{
		if (equipped.count(11))
		{
			switch (job / 100)
			{
			case 0:
			case 1:
			case 20:
			case 21:
				return gettotal(ES_DEX);
			case 2:
				return gettotal(ES_LUK);
			case 3:
				return gettotal(ES_STR);
			case 4:
				return gettotal(ES_DEX);
			case 5:
				return (equipped[11].getid() / 10000 == 149) ? gettotal(ES_STR) : gettotal(ES_DEX);
			}
		}

		return 0;
	}

	const float inventory::getwmult()
	{
		if (equipped.count(11))
		{
			switch (equipped[11].getid() / 10000)
			{
			case 130:
				return 4.0f;
			case 131:
			case 132:
			case 137:
			case 138:
				return 4.4f;
			case 133:
			case 146:
			case 147:
			case 149:
				return 3.6f;
			case 140:
				return 4.6f;
			case 141:
			case 142:
			case 148:
				return 4.8f;
			case 143:
			case 144:
				return 5.0f;
			case 145:
				return 3.4f;
			}
		}

		return 0;
	}

	const inventorytype inventory::gettypebyid(int itemid)
	{
		switch (itemid / 1000000)
		{
		case 1:
			return IVT_EQUIP;
		case 2:
			return IVT_USE;
		case 3:
			return IVT_SETUP;
		case 4:
			return IVT_ETC;
		case 5:
			return IVT_CASH;
		}

		return IVT_NONE;
	}
}
