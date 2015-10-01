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
#include "chatballoon.h"
#include "Journey.h"

namespace io
{
	chatballoon::chatballoon(char type, string txt)
	{
		app.getimgcache()->setmode(ict_sys);

		string strsrc;
		if (type < 0)
		{
			switch (type)
			{
			case -1:
				strsrc = "dead";
				break;
			}
		}
		else
		{
			strsrc = to_string(type);
		}

		node src = nx::nodes["UI"]["ChatBalloon.img"]["0"];

		arrow = texture(src["arrow"]);
		center = texture(src["c"]);
		east = texture(src["e"]);
		northeast = texture(src["ne"]);
		north = texture(src["n"]);
		northwest = texture(src["nw"]);
		west = texture(src["w"]);
		southwest = texture(src["sw"]);
		south = texture(src["s"]);
		southeast = texture(src["se"]);

		app.getimgcache()->unlock();

		text = textlabel(DWF_12C, TXC_BLACK, "");
		text.settext(txt, 80);

		xtile = north.getdimension().x();
		ytile = west.getdimension().y();

		char numhor = (text.getwidth() / xtile) + 2;
		char numver = (text.getheight() / ytile);

		width = numhor * xtile;
		height = numver * ytile;

		elapsed = 0;
	}

	void chatballoon::draw(vector2d arpos)
	{
		char numhor = (width / xtile);
		char numver = (height / ytile);
		int left = arpos.x() - width / 2;
		int top = arpos.y() - height;

		northwest.draw(vector2d(left, top));
		southwest.draw(vector2d(left, top + height));

		for (char i = 0; i < numver; i++)
		{
			int yshift = (ytile * i);
			west.draw(vector2d(left, top + yshift));

			for (char j = 0; j < numhor; j++)
			{
				int xshift = (xtile * j);
				center.draw(vector2d(left + xshift, top + yshift));
			}

			east.draw(vector2d(left + width, top + yshift));
		}

		for (char i = 0; i < numhor; i++)
		{
			int xshift = (xtile * i);
			north.draw(vector2d(left + xshift, top));
			south.draw(vector2d(left + xshift, top + height));
		}

		northeast.draw(vector2d(left + width, top));
		southeast.draw(vector2d(left + width, top + height));

		arrow.draw(arpos);

		text.draw(vector2d(arpos.x(), top - 6));
	}

	bool chatballoon::update()
	{
		elapsed += 1;
		return elapsed > 250;
	}
}
