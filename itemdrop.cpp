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
#include "itemdrop.h"

namespace maplemap
{
	itemdrop::itemdrop(short o, int id, texture ic, int own, vector2d pos, vector2d dst, char type, bool pld)
	{
		oid = o;
		itemid = id;
		ico = ic;
		owner = own;
		pickuptype = type;
		playerdrop = pld;

		fx = static_cast<float>(pos.x());
		fy = static_cast<float>(pos.y());

		updatefht();

		dalpha = 1.0f;
		moved = 0.0f;

		if (pos == dst)
		{
			state = DST_FLOATING;
			vspeed = 0;
			hspeed = 0;
			basey = fy;
		}
		else
		{
			state = DST_DROPPED;
			vspeed = -6.0f;
			hspeed = static_cast<float>(dst.x() - pos.x()) / 16;
		}
	}

	void itemdrop::draw(vector2d viewpos)
	{
		if (state != DST_INACTIVE)
		{
			ico.draw(viewpos + getposition(), dalpha);
		}
	}
}
