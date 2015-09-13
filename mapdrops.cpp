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
#include "mapdrops.h"

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
				toadd = new mesodrop(oid, itemid, owner, pos, dest, type, playerdrop, footholds);
			}
			else
			{
				toadd = new itemdrop(oid, itemid, owner, pos, dest, type, playerdrop, footholds);
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
		for (int i = 0; i < drops.getend(); i++)
		{
			drops.getnext(i)->draw(target, viewpos);
		}
	}

	void mapdrops::update()
	{
		vector<int> toremove;

		for (int i = 0; i < drops.getend(); i++)
		{
			bool expired = drops.getnext(i)->update();

			if (expired)
			{
				toremove.push_back(i);
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
