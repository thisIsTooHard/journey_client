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
#include "mapdrops.h"
#include "Journey.h"

namespace maplemap
{
	void mapdrops::init()
	{
		mesos[MES_BRONZE] = animation(nx::nodes["Item"]["Special"]["0900.img"]["09000000"]["iconRaw"]);
		mesos[MES_GOLD] = animation(nx::nodes["Item"]["Special"]["0900.img"]["09000001"]["iconRaw"]);
		mesos[MES_BUNDLE] = animation(nx::nodes["Item"]["Special"]["0900.img"]["09000002"]["iconRaw"]);
		mesos[MES_BAG] = animation(nx::nodes["Item"]["Special"]["0900.img"]["09000003"]["iconRaw"]);
	}

	void mapdrops::adddrop(short oid, int itemid, bool meso, int owner, vector2d pos, vector2d dest, char type, char mod)
	{
		if (drops.contains(oid))
		{
			drops.get(oid)->makeactive();
		}
		else
		{
			drop* toadd = 0;

			if (meso)
			{
				mesoamount amount = (itemid > 999) ? MES_BAG : (itemid > 99) ? MES_BUNDLE : (itemid > 9) ? MES_GOLD : MES_BRONZE;
				toadd = new mesodrop(oid, &mesos[amount], owner, pos, dest, type, mod);
			}
			else
			{
				texture icon;
				int prefix = itemid / 1000000;
				if (prefix == 1)
				{
					clothing* cloth = cache.getequips()->getcloth(itemid);
					if (cloth)
					{
						icon = cloth->geticon(true);
					}
				}
				else
				{
					itemdata* item = cache.getitems()->getitem(itemid);
					if (item)
					{
						icon = item->geticon(true);
					}
				}
				toadd = new itemdrop(oid, itemid, icon, owner, pos, dest, type, mod);
			}

			drops.add(oid, toadd);
			if (mod != 2)
			{
				cache.getsounds()->play(MSN_DROP);
			}
		}
	}

	void mapdrops::removedrop(short oid, char mode, moveobject* looter)
	{
		if (drops.contains(oid))
		{
			drops.get(oid)->expire(mode, looter);
		}
	}

	void mapdrops::draw(vector2d viewpos)
	{
		for (spmit<short, drop*> drit = drops.getit(); drit.belowtop(); drit++)
		{
			drit->draw(viewpos);
		}
	}

	void mapdrops::update()
	{
		vector<int> toremove;

		for (spmit<short, drop*> drit = drops.getit(); drit.belowtop(); drit++)
		{
			bool expired = drit->update();

			if (expired)
			{
				toremove.push_back(drit.getindex());
			}
		}

		for (vector<int>::iterator rmit = toremove.begin(); rmit != toremove.end(); rmit++)
		{
			drops.remove(*rmit);
		}
	}

	drop* mapdrops::trypickup(rectangle2d range)
	{
		for (spmit<short, drop*> drit = drops.getit(); drit.belowtop(); drit++)
		{
			if (range.overlaps(drit->bounds()))
			{
				return drit.get();
			}
		}
		return 0;
	}
}
