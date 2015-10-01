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
#include "button.h"

namespace io
{
	button::button(node src)
	{
		textures[BTS_PRESSED] = texture(src["pressed"]["0"]);
		textures[BTS_MOUSEOVER] = texture(src["mouseOver"]["0"]);
		textures[BTS_NORMAL] = texture(src["normal"]["0"]);
		textures[BTS_DISABLED] = texture(src["disabled"]["0"]);
		position = vector2d();

		state = BTS_NORMAL;
		bttype = BTT_REGULAR;
		active = true;
	}

	button::button(node src, int x, int y)
	{
		textures[BTS_PRESSED] = texture(src["pressed"]["0"]);
		textures[BTS_MOUSEOVER] = texture(src["mouseOver"]["0"]);
		textures[BTS_NORMAL] = texture(src["normal"]["0"]);
		textures[BTS_DISABLED] = texture(src["disabled"]["0"]);
		position = vector2d(x, y);

		state = BTS_NORMAL;
		bttype = BTT_REGULAR;
		active = true;
	}
	
	button::button(texture s1, texture s2, int x, int y)
	{
		textures[BTS_NORMAL] = s1;
		textures[BTS_SELECT] = s2;
		position = vector2d(x, y);

		state = BTS_NORMAL;
		bttype = BTT_ONESPRITE;
		active = true;
	}

	button::button(vector2d pos, vector2d dim)
	{
		position = pos;
		dimension = dim;

		state = BTS_NORMAL;
		bttype = BTT_AREA;
		active = true;
	}

	rectangle2d button::bounds(vector2d parentpos)
	{
		if (bttype == BTT_AREA)
		{
			vector2d absp = parentpos + position;
			return rectangle2d(absp, absp + dimension);
		}
		else
		{
			vector2d absp = parentpos + position - textures[BTS_NORMAL].getorigin();
			return rectangle2d(absp, absp + textures[BTS_NORMAL].getdimension());
		}
	}

	void button::draw(vector2d parentpos)
	{
		if (active)
		{
			vector2d absp = position + parentpos;

			switch (bttype)
			{
			case BTT_REGULAR:
				textures[state].draw(absp);
				break;
			case BTT_ONESPRITE:
				textures[BTS_NORMAL].draw(absp);
				if (state == BTS_PRESSED || state == BTS_MOUSEOVER)
				{
					textures[BTS_SELECT].draw(absp);
				}
				break;
			}
		}
	}
}
