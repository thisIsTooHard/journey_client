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
#include "gravityobject.h"
#include "Journey.h"

namespace action
{
	gravityobject::gravityobject()
	{
		fx = 0.0f;
		fy = 0.0f;
		hspeed = 0;
		vspeed = 0;

		updatefht();
	}

	gravityobject::gravityobject(vector2d pos)
	{
		fx = static_cast<float>(pos.x());
		fy = static_cast<float>(pos.y());
		hspeed = 0;
		vspeed = 0;

		updatefht();
	}

	bool gravityobject::update()
	{
		bool groundhit = false;

		if (footholds)
		{
			if (hspeed != 0 && vspeed == 0)
			{
				if (fx > fh.horizontal.y())
				{
					fh = footholds->getnext(false, fh);
				}
				else if (fx < fh.horizontal.x())
				{
					fh = footholds->getnext(true, fh);
				}
			}
			else
			{
				fh = footholds->getbelow(getposition());
			}

			float ground = fh.resolvex(static_cast<int>(fx));

			if (ground - fy <= fh.getslope() * hspeed)
			{
				fy = ground;
				groundhit = true;
			}

			if (ground > fy)
			{
				vspeed += GRAVITYACC;
				if (vspeed > MAXVSPEED)
				{
					vspeed = MAXVSPEED;
				}

				if (fy + vspeed >= ground)
				{
					vspeed = 0;
					fy = ground;
					groundhit = true;
				}
			}
		}

		moveobject::update();

		return groundhit;
	}

	bool gravityobject::updatefht()
	{
		footholds = cache.getmap()->getfht();

		if (footholds)
		{
			fh = footholds->getbelow(getposition());
		}
		else
		{
			fh = foothold();
		}

		return footholds == 0;
	}
}
