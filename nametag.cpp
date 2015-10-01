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
#include "nametag.h"

namespace io
{
	nametag::nametag(dwfonts fnt, textcolor col, map<bool, vector<texture>> t, string n, vector2d p, bool a)
	{
		content = textlabel(fnt, col, n);
		tag = t;
		position = p;
		active = a;
	}

	nametag::nametag(dwfonts fnt, textcolor col, vector<texture> t, string n, vector2d p)
	{
		content = textlabel(fnt, col, n);
		tag[false] = t;
		position = p;
		active = false;
	}

	void nametag::draw(vector2d parentpos)
	{
		int width = content.getwidth() - 4;

		vector2d bgpos = position + parentpos - vector2d(8 + width / 2, -3);
		tag[active][0].draw(bgpos);
		tag[active][1].draw(bgpos + vector2d(8, 0), vector2d(width + 1, 0));
		tag[active][2].draw(bgpos + vector2d(8, 0) + vector2d(width + 1, 0));

		content.draw(position + parentpos);
	}
}
