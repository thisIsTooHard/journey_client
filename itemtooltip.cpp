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
#include "itemtooltip.h"
#include "Journey.h"

namespace io
{
	void itemtooltip::init()
	{
		node itemtt = nx::nodes["UI"]["UIToolTip.img"]["Item"];

		top = texture(itemtt["Frame"]["top"]);
		mid = texture(itemtt["Frame"]["line"]);
		bot = texture(itemtt["Frame"]["bottom"]);
		line = texture(itemtt["Frame"]["dotline"]);
		base = texture(itemtt["ItemIcon"]["base"]);
		cover = texture(itemtt["ItemIcon"]["cover"]);
		shade = texture(itemtt["ItemIcon"]["shade"]);

		itemid = 0;
		active = false;
	}

	void itemtooltip::setitem(itemdata* it)
	{
		item = it;
		itemid = item->getid();

		filllength = 200;

		name = textlabel(DWF_20C, TXC_WHITE, item->getname());
		active = true;
	}

	void itemtooltip::draw(vector2d drawpos)
	{
		if (active)
		{
			int bdelta = SCREENW - drawpos.x() - 277;
			drawpos.shift(min(bdelta, 0), 16);

			top.draw(drawpos);
			mid.draw(drawpos + vector2d(0, 13), vector2d(0, filllength));
			bot.draw(drawpos + vector2d(0, filllength + 13));

			line.draw(drawpos + vector2d(0, 48));

			base.draw(drawpos + vector2d(10, 58));
			shade.draw(drawpos + vector2d(10, 58));

			vector2d iconpos = drawpos + vector2d(20, 131);

			item->geticon(true).draw(iconpos, 2.0f, 2.0f);

			cover.draw(drawpos + vector2d(10, 58));

			name.draw(drawpos + vector2d(130, 5));
		}
	}
}
