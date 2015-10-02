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
			hspeed = -0.5f;
			break;
		case BGT_VMOVEA:
		case BGT_VMOVEB:
			vspeed = -0.5f;
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

		int xcom = -parentpos.x() - mapwalls.x() + 400;
		//int xcom = -parentpos.x();
		int ycom = -parentpos.y() + mapborders.y();

		int shiftx = static_cast<int>(0.5 * rpos.x() * static_cast<float>(xcom) / 100 + 400);
		int shifty = static_cast<int>(0.5 * rpos.y() * static_cast<float>(ycom - 300) / 100 + 300);

		vector2d absp = pos + vector2d(shiftx, shifty);

		switch (type)
		{
		case BGT_HMOVEA:
			absp.setx(cshiftx() + parentpos.x());
			htile = 2 + (mapwalls.y() - mapwalls.x()) / cpos.x();
			break;
		case BGT_HTILED:
			//absp.setx(cshifty() + parentpos.y());
			htile = 2 + (mapwalls.y() - mapwalls.x()) / cpos.x();
			break;
		case BGT_VMOVEA:
			absp.setx(cshifty() + parentpos.y());
			vtile = 2 + (mapborders.y() + cpos.y() - mapborders.x()) / cpos.y();
			break;
		case BGT_VTILED:
			//absp.setx(pos.x() + parentpos.x());
			vtile = 2 + (mapborders.y() + cpos.y() - mapborders.x()) / cpos.y();
			break;
		case BGT_HMOVEB:
			absp.setx(cshiftx() + parentpos.x());
			htile = 2 + (mapwalls.y() + cpos.x() - mapwalls.x()) / cpos.x();
			vtile = 2 + (mapborders.y() + cpos.y() - mapborders.x()) / cpos.y();
			break;
		case BGT_VMOVEB:
			absp.setx(cshifty() + parentpos.y());
		case BGT_TILED:
			htile = 2 + (mapwalls.y() + cpos.x() - mapwalls.x()) / cpos.x();
			vtile = 2 + (mapborders.y() + cpos.y() - mapborders.x()) / cpos.y();
			break;
		case BGT_HSTRETCH:
			absp = vector2d();
			stretch.setx(800);
			break;
		case BGT_VSTRETCH:
			absp = vector2d();
			stretch.sety(600);
			break;
		case BGT_STRETCH:
			absp = vector2d();
			stretch = vector2d(800, 600);
			break;
		}

		int starty = absp.y();
		
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
				absp.sety(starty);
				absp.shiftx(cpos.x());
			}
		}
	}

	int background::cshiftx()
	{
		int x = static_cast<int>(fx);
		if (fx < mapwalls.x())
		{
			fx += cpos.x();
		}
		return (x % cpos.x()) - cpos.x();
	}

	int background::cshifty()
	{
		int y = static_cast<int>(fy);
		if (y < mapborders.x())
		{
			fy += cpos.x();
		}
		return (y % cpos.y()) - cpos.y();
	}

	bool background::update()
	{
		graphicobject::update(&ani);
		moveobject::update();

		return false;
	}
}
