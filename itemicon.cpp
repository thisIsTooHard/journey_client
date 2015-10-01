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
#include "itemicon.h"
#include "Journey.h"

namespace io
{
	itemicon::itemicon(map<bool, texture> t, int i, bool r, short q)
	{
		textures = t;
		iid = i;
		raw = r;
		qty = q;

		showcount = qty > 0;
		alpha = 1.0f;
	}

	void itemicon::onmouseover()
	{
		app.getui()->showiteminfo(iid);
	}

	void itemicon::draw(vector2d pos)
	{
		textures[raw].draw(pos, alpha);

		if (!raw && showcount && alpha == 1.0f)
		{
			if (!countset)
			{
				countset = cache.getitems()->getcountset();
			}

			countset->draw(to_string(qty), cha_left, pos + vector2d(0, -12));
		}
	}
}
