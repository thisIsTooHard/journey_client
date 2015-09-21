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
		textures["pressed"] = texture(src["pressed"]["0"]);
		textures["mouseOver"] = texture(src["mouseOver"]["0"]);
		textures["normal"] = texture(src["normal"]["0"]);
		textures["disabled"] = texture(src["disabled"]["0"]);
		position = vector2d();
		state = "normal";
		bttype = BTT_REGULAR;
		active = true;
	}

	button::button(node src, int x, int y)
	{
		textures["pressed"] = texture(src.resolve("pressed/0"));
		textures["mouseOver"] = texture(src.resolve("mouseOver/0"));
		textures["normal"] = texture(src.resolve("normal/0"));
		textures["disabled"] = texture(src.resolve("disabled/0"));
		position = vector2d(x, y);
		state = "normal";
		bttype = BTT_REGULAR;
		active = true;
	}
	
	button::button(texture s1, texture s2, int x, int y)
	{
		textures["normal"] = s1;
		textures["select"] = s2;
		position = vector2d(x, y);
		state = "normal";
		bttype = BTT_ONESPRITE;
		active = true;
	}

	button::button(vector2d pos, vector2d dim)
	{
		position = pos;
		dimension = dim;
		state = "normal";
		bttype = BTT_AREA;
		active = true;
	}

	pair<vector2d, vector2d> button::bounds()
	{
		if (bttype == BTT_AREA)
		{
			return pair<vector2d, vector2d>(position, dimension);
		}
		else
		{
			return pair<vector2d, vector2d>(position - textures["normal"].getorigin(), (textures["normal"].getdimension()));
		}
	}

	void button::draw(ID2D1HwndRenderTarget* target, vector2d parentpos)
	{
		if (active)
		{
			vector2d absp = position + parentpos;

			if (bttype == BTT_ONESPRITE)
			{
				if (state == "normal")
				{
					textures["normal"].draw(absp);
				}
				else if (state == "pressed" || state == "mouseOver")
				{
					textures["normal"].draw(absp);
					textures["select"].draw(absp);
				}
			}
			else if (bttype == BTT_REGULAR)
			{
				textures[state].draw(absp);
			}
		}
	}
}
