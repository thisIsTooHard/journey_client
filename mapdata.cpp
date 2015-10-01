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
#include "mapdata.h"
#include "nxfile.h"

namespace data
{
	void mapdata::init()
	{
		//load something here
	}

	void mapdata::load(int mapid)
	{
		string oldbgm = (id > 0) ? info.getbgm() : "";

		string strid = to_string(mapid);
		strid.insert(0, 9 - strid.length(), '0');
		strid.append(".img");

		node src = nx::nodes["Map"]["Map"]["Map" + to_string(mapid / 100000000)][strid];

		fht = footholdtree(src["foothold"]);
		info = mapinfo(src, fht.getwalls(), fht.getborders());
		landr = laddersropes(src["ladderRope"]);

		newbgm = oldbgm != info.getbgm();
		id = mapid;
	}
}
