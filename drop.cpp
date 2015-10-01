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
	void drop::init(char mod)
	{
		dalpha = 1.0f;
		moved = 0.0f;
		looter = 0;

		fx = static_cast<float>(pos.x());
		fy = static_cast<float>(pos.y());

		updatefht();

		switch (mod)
		{
		case 0:
		case 1:
			state = DST_DROPPED;
			vspeed = -6.0f;
			hspeed = static_cast<float>(dest.x() - pos.x()) / 16;
			if (fy >= fh.resolvex(pos.x()))
			{
				fy -= 1.0f;
			}
			break;
		case 2:
			state = DST_FLOATING;
			vspeed = 0.0f;
			hspeed = 0.0f;
			basey = fy;
			break;
		case 3:
			state = DST_EXPIRE;
			vspeed = -6.0f;
			hspeed = 0.0f;
			break;
		}
	}

	void drop::expire(char type, moveobject* lt)
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
			looter = lt;
			vspeed = -6.0f;
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
			if (looter)
			{
				hspeed = looter->gethspeed() + static_cast<float>(looter->getposition().x() - fx) / 10;
			}
			else
			{
				hspeed = 0.0f;
			}

			gravityobject::update();

			dalpha -= 1.0f / 32;
			if (dalpha <= 1.0f / 32)
			{
				dalpha = 0.0f;
				state = DST_INACTIVE;
				return true;
			}
		}

		return false;
	}
}
