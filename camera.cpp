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
#include "camera.h"
#include "Journey.h"

namespace gameplay
{
	camera::camera()
	{
		posx = 0;
		posy = 0;
		movex = 0.0f;
		movey = 0.0f;
	}

	vector2d camera::update(vector2d playerpos)
	{
		vector2d dest = vector2d(408, 416) - playerpos;
		vector2d pos = vector2d(static_cast<int>(posx), static_cast<int>(posy));

		if ((dest - pos).length() > 1)
		{
			movex = static_cast<float>(dest.x() - pos.x()) / 40;
			movey = static_cast<float>(dest.y() - pos.y()) / 40;

			posx = posx + movex;
			posy = posy + movey;

			if (abs(playerpos.x() - posx) < 1)
			{
				posx = static_cast<float>(playerpos.x());
				movex = 0;
			}
			if (abs(playerpos.y() - posy) < 1)
			{
				posy = static_cast<float>(playerpos.y());
				movey = 0;
			}
		}

		return getposition();
	}

	vector2d camera::getposition()
	{
		int retx;
		int rety;

		if (posx > hbounds.x() || hbounds.length() < 816)
			retx = hbounds.x();
		else if (posx < hbounds.y() + 816)
			retx = hbounds.y() + 816;
		else
			retx = static_cast<int>(posx);

		if (posy < vbounds.y() + 624 || vbounds.length() < 624)
			rety = vbounds.y() + 624;
		else
			rety = static_cast<int>(posy);

		return vector2d(retx, rety);
	}

	void camera::setposition(vector2d pos)
	{
		pos = vector2d(408, 416) - pos;

		posx = static_cast<float>(pos.x());
		posy = static_cast<float>(pos.y());
	}

	void camera::updateview()
	{
		vector2d mapwalls = cache.getmap()->getinfo()->getwalls();
		vector2d mapborders = cache.getmap()->getinfo()->getborders();

		hbounds = vector2d(-mapwalls.x(), -mapwalls.y());
		vbounds = vector2d(-mapborders.x(), -mapborders.y() - 30);
	}
}
