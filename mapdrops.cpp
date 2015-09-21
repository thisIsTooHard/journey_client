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
	void mapdrops::adddrop(short oid, int itemid, bool meso, int owner, vector2d pos, vector2d dest, char type, bool playerdrop)
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
				app.getimgcache()->setmode(ict_sys);
				toadd = new mesodrop(oid, itemid, owner, pos, dest, type, playerdrop, footholds);
				app.getimgcache()->unlock();
			}
			else
			{
				texture icon;
				int prefix = itemid / 1000000;
				if (prefix == 1)
				{
					clothing* cloth = app.getlookfactory()->getcloth(itemid);
					if (cloth)
					{
						icon = cloth->geticon(true);
					}
				}
				else
				{
					iteminfo* item = app.getui()->getfield()->getitems()->getitem(itemid);
					if (item)
					{
						icon = item->geticon(true);
					}
				}
				toadd = new itemdrop(oid, itemid, icon, owner, pos, dest, type, playerdrop, footholds);
			}

			drops.add(oid, toadd);
		}
	}

	void mapdrops::removedrop(short oid, char mode)
	{
		if (drops.contains(oid))
		{
			drops.get(oid)->expire(mode);
		}
	}

	void mapdrops::draw(ID2D1HwndRenderTarget* target, vector2d viewpos)
	{
		for (spmit<short, drop*> drit = drops.getit(); drit.belowtop(); drit++)
		{
			drit->draw(target, viewpos);
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

	mapdrops::~mapdrops()
	{
		drops.clear();
	}
}
