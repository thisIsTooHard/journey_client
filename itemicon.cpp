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
#include "nxfile.h"

namespace io
{
	itemicon::itemicon(map<bool, texture> txt, bool r, short q)
	{
		textures = txt;
		raw = r;
		qty = q;

		showcount = qty > 1;
		pos = vector2d();
	}

	void itemicon::draw(vector2d parentpos, float alpha)
	{
		textures[raw].draw(pos + parentpos, alpha);

		if (!raw && showcount && alpha == 1.0f)
		{
			countset.draw(to_string(qty), 8, cha_left, pos + parentpos + vector2d(-6, -12));
		}
	}
}
