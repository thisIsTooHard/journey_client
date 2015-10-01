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
	itemdrop::itemdrop(short o, int id, texture ic, int own, vector2d ps, vector2d dst, char type, char mod)
	{
		oid = o;
		itemid = id;
		ico = ic;
		owner = own;
		pickuptype = type;
		dest = dst;
		pos = ps;

		init(mod);
	}

	void itemdrop::draw(vector2d viewpos)
	{
		if (state != DST_INACTIVE)
		{
			ico.draw(viewpos + getposition() - vector2d(16, 0), dalpha);
		}
	}
}
