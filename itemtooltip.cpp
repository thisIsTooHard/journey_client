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
	itemtooltip::itemtooltip(imagecache* imgcache)
	{
		imgcache->setmode(ict_sys);

		node itemtt = nx::nodes["UI"]["UIToolTip.img"]["Item"];

		top = texture(itemtt["Frame"]["top"]);
		mid = texture(itemtt["Frame"]["line"]);
		bot = texture(itemtt["Frame"]["bottom"]);
		line = texture(itemtt["Frame"]["dotline"]);
		base = texture(itemtt["ItemIcon"]["base"]);
		cover = texture(itemtt["ItemIcon"]["cover"]);
		shade = texture(itemtt["ItemIcon"]["shade"]);

		imgcache->unlock();

		info = textlabel(DWF_12LL, TXC_WHITE, "");
		active = true;
	}

	void itemtooltip::setitem(iteminfo* it)
	{
		item = it;
		itemid = item->getid();

		filllength = 200;

		name = textlabel(DWF_20C, TXC_WHITE, item->getname());
	}

	void itemtooltip::draw(ID2D1HwndRenderTarget* target, vector2d drawpos)
	{
		if (active)
		{
			top.draw(drawpos);
			mid.draw(drawpos + vector2d(0, 13), vector2d(0, filllength));
			bot.draw(drawpos + vector2d(0, filllength + 13));

			line.draw(drawpos + vector2d(0, 48));

			base.draw(drawpos + vector2d(10, 58));
			shade.draw(drawpos + vector2d(10, 58));

			vector2d iconpos = drawpos + vector2d(20, 120);

			target->SetTransform(
				D2D1::Matrix3x2F::Scale(
				D2D1::Size(2.0f, 2.0f),
				D2D1::Point2F(
				static_cast<float>(iconpos.x()),
				static_cast<float>(iconpos.y()))));

			item->geticon(true).draw(iconpos);

			target->SetTransform(
				D2D1::Matrix3x2F::Scale(
				D2D1::Size(1.0f, 1.0f),
				D2D1::Point2F(
				static_cast<float>(iconpos.x()),
				static_cast<float>(iconpos.y()))));

			cover.draw(drawpos + vector2d(10, 58));

			name.draw(target, drawpos + vector2d(130, 5));
		}
	}
}
