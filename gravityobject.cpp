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
#include "gravityobject.h"

namespace action
{
	gravityobject::gravityobject(vector2d pos, footholdtree* fht)
	{
		fx = static_cast<float>(pos.x());
		fy = static_cast<float>(pos.y());
		footholds = fht;
		fh = fht->getbelow(pos);
		hspeed = 0;
		vspeed = 0;
	}

	bool gravityobject::update()
	{
		bool groundhit = false;

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

		if (ground - fy <= fh.getslope() * abs(hspeed))
		{
			fy = ground;
		}

		if (ground > fy)
		{
			vspeed += grvacc;
			vspeed = min(vspeed, maxvspeed);

			if (fy + vspeed >= ground)
			{
				vspeed = 0;
				fy = ground;
				groundhit = true;
			}
		}

		bool moveend = moveobject::update();

		return groundhit;
	}
}
