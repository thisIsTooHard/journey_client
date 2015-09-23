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
#include "background.h"

namespace gameplay
{
	background::background(node src, node back, vector2d walls, vector2d borders)
	{
		ani = animation(back[src["bS"].get_string() + ".img"][(src["ani"].get_bool()) ? "ani" : "back"][to_string(src["no"].get_integer())]);
		type = static_cast<bgtype>(src["type"].get_integer());
		rpos = vector2d(static_cast<int>(src["rx"]), static_cast<int>(src["ry"]));
		cpos = vector2d(static_cast<int>(src["cx"]), static_cast<int>(src["cy"]));
		alpha = static_cast<float>(src["a"].get_integer()) / 255;
		fx = static_cast<float>(src["x"]);
		fy = static_cast<float>(src["y"]);
		flipped = src["f"].get_bool();

		hspeed = 0;
		vspeed = 0;

		blending = false;
		resetani();

		mapwalls = walls;
		mapborders = borders;

		if (cpos.x() == 0)
			cpos = vector2d(ani.getdimension(0).x(), cpos.y());
		if (cpos.y() == 0)
			cpos = vector2d(cpos.x(), ani.getdimension(0).y());

		switch (type)
		{
		case BGT_HMOVEA:
		case BGT_HMOVEB:
			hspeed = 0.5f;
			break;
		case BGT_VMOVEA:
		case BGT_VMOVEB:
			vspeed = 0.5f;
			break;
		case BGT_HTILED:
			if (cpos.x() < 16)
			{
				type = BGT_HSTRETCH;
			}
			break;
		case BGT_VTILED:
			if (cpos.y() < 16)
			{
				type = BGT_VSTRETCH;
			}
			break;
		case BGT_TILED:
			if (cpos.x() < 16 || cpos.y() < 16)
			{
				type = BGT_STRETCH;
			}
			break;
		default:
			hspeed = 0;
			vspeed = 0;
		}
	}

	void background::draw(vector2d parentpos)
	{
		vector2d pos = getposition();

		vector2d stretch = vector2d();
		short htile = 1;
		short vtile = 1;

		vector2d absp = pos + parentpos;

		//vector2d absp = pos + vector2d(static_cast<float>(rpos.x() * parentpos.x()) / 200, static_cast<float>(rpos.y() * parentpos.y()) / 150) + parentpos + vector2d(400, 300);

		switch (type)
		{
		case BGT_HMOVEA:
		case BGT_HTILED:
			htile = (mapwalls.y() + cpos.x() - mapwalls.x()) / cpos.x();
			absp.setx(parentpos.x() - cpos.x());
			break;
		case BGT_VMOVEA:
		case BGT_VTILED:
			vtile = (mapborders.y() + cpos.y() - mapborders.x()) / cpos.y();
			absp.sety(parentpos.y() - cpos.y());
			break;
		case BGT_HMOVEB:
		case BGT_VMOVEB:
		case BGT_TILED:
			htile = (mapwalls.y() + cpos.x() - mapwalls.x()) / cpos.x();
			vtile = (mapborders.y() + cpos.y() - mapborders.x()) / cpos.y();
			absp = parentpos - cpos;
			break;
		case BGT_HSTRETCH:
			absp.setx(0);
			stretch.setx(800);
			break;
		case BGT_VSTRETCH:
			absp.sety(0);
			stretch.sety(600);
			break;
		case BGT_STRETCH:
			absp = vector2d();
			stretch = vector2d(800, 600);
			break;
		}
		
		texture* txt = ani.gettexture(frame);
		if (txt)
		{
			for (short h = 0; h < htile; h++)
			{
				for (short v = 0; v < vtile; v++)
				{
					txt->draw(absp, stretch, alpha, flipped);

					absp.shifty(cpos.y());
				}

				absp.shiftx(cpos.x());
			}
		}
	}

	bool background::update()
	{
		graphicobject::update(&ani);
		moveobject::update();

		return false;
	}
}
