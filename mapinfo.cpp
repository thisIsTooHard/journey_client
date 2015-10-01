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
#include "mapinfo.h"

namespace data
{
	mapinfo::mapinfo(node src, vector2d walls, vector2d borders)
	{
		node info = src["info"];
		if (info["VRLeft"].istype(integernode))
		{
			mapwalls = vector2d(info["VRLeft"], info["VRRight"]);
			mapborders = vector2d(info["VRTop"], info["VRBottom"]);
		}
		else
		{
			mapwalls = walls;
			mapborders = borders;
		}

		string bgmpath = info["bgm"];
		size_t split = bgmpath.find('/');
		bgm = bgmpath.substr(0, split) + ".img/" + bgmpath.substr(split + 1);

		cloud = info["cloud"].get_bool();
		fieldlimit = info["fieldLimit"];
		hideminimap = info["hideMinimap"].get_bool();
		mapmark = info["mapMark"];
		swim = info["swim"].get_bool();
		town = info["town"].get_bool();

		node stsrc = src["seat"];
		for (node sub = stsrc.begin(); sub != stsrc.end(); ++sub)
		{
			seats.push_back(sub.tov2d());
		}
	}

	vector2d* mapinfo::getseat(vector2d pos)
	{
		vector2d hor = vector2d(pos.x() - 10, pos.x() + 10);
		vector2d ver = vector2d(pos.y() - 10, pos.y() + 10);
		for (vector<vector2d>::iterator stit = seats.begin(); stit != seats.end(); ++stit)
		{
			if (hor.contains(stit->x()) && ver.contains(stit->y()))
			{
				return stit._Ptr;
			}
		}
		return 0;
	}
}
