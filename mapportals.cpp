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
#include "mapportals.h"
#include "nxfile.h"

namespace maplemap
{
	void mapportals::init()
	{
		node pnode = nx::nodes["Map"]["MapHelper.img"]["portal"]["game"];
		animations[PT_REGULAR] = animation(pnode["pv"]);
		animations[PT_HIDDEN] = animation(pnode["ph"]["default"]["portalContinue"]);
	}

	void mapportals::load(node src, int mapid)
	{
		for (node ptnode = src.begin(); ptnode != src.end(); ++ptnode)
		{
			char pid = static_cast<char>(stoi(ptnode.name()));
			portaltype type = static_cast<portaltype>(ptnode["pt"].toi8());
			string name = ptnode["pn"];
			int targetid = ptnode["tm"];
			string targetname = ptnode["tn"];
			vector2d pos = vector2d(ptnode["x"], ptnode["y"]);

			animation* anim;
			switch (type)
			{
			case PT_REGULAR:
			case PT_HIDDEN:
				anim = &animations[type];
				break;
			case PT_SCRIPTED_HIDDEN:
				anim = &animations[PT_HIDDEN];
				break;
			default:
				anim = 0;
			}

			portals.add(pid, portal(type, name, targetid, mapid == targetid, targetname, anim, pos));
		}
	}

	vector2d mapportals::getspawnpoint(char id)
	{
		return portals.contains(id) ? portals.get(id)->getposition() : vector2d();
	}

	vector2d mapportals::getspawnpoint(string pname)
	{
		vector2d ret = vector2d();

		for (smit<char, portal> ptit = portals.getit(); ptit.belowtop(); ptit++)
		{
			if (ptit->getname() == pname)
			{
				ret = ptit->getposition();
				break;
			}
		}

		return ret;
	}

	pair<int, string> mapportals::getportal(rectangle2d playerrect)
	{
		pair<int, string> warpinfo = make_pair(999999999, "");

		for (smit<char, portal> ptit = portals.getit(); ptit.belowtop(); ptit++)
		{
			if (ptit->bounds().overlaps(playerrect) && ptit->gettype() != PT_WARP)
			{
				warpinfo = ptit->getwarpinfo();
				break;
			}
		}

		return warpinfo;
	}

	void mapportals::draw(vector2d viewpos)
	{
		for (smit<char, portal> ptit = portals.getit(); ptit.belowtop(); ptit++)
		{
			ptit->draw(viewpos);
		}
	}

	void mapportals::update(rectangle2d playerrect)
	{
		for (smit<char, portal> ptit = portals.getit(); ptit.belowtop(); ptit++)
		{
			ptit->settouch(ptit->bounds().overlaps(playerrect));
			ptit->update();
		}
	}
}
