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
#include "drop.h"

namespace maplemap
{
	void drop::expire(char type)
	{
		switch (type)
		{
		case 0:
			state = DST_EXPIRE;
			break;
		case 1:
			state = DST_INACTIVE;
			break;
		case 2:
			state = DST_PICKEDUP;
			break;
		}
	}

	bool drop::update()
	{
		if (state == DST_DROPPED)
		{
			bool groundhit = gravityobject::update();

			if (groundhit)
			{
				state = DST_FLOATING;
				hspeed = 0;
				vspeed = 0;
				basey = fy;
			}
		}

		if (state == DST_FLOATING)
		{
			float shift = cos(moved) - 1.0f;
			fy = basey + 5.0f + shift * 2.5f;
			moved = (moved < 360.0f) ? moved + 0.025f : 0.0f;
		}

		if (state == DST_PICKEDUP)
		{
			dalpha -= 0.025f;
			if (dalpha < 0.025f)
			{
				dalpha = 0.0f;
				state = DST_INACTIVE;
				return true;
			}
		}

		return false;
	}
}
