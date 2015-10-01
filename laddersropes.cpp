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
#include "laddersropes.h"

namespace data
{
	laddersropes::laddersropes(node src)
	{
		for (node lrnode = src.begin(); lrnode != src.end(); ++lrnode)
		{
			ladderrope lr;
			lr.x = lrnode["x"];
			lr.ladder = lrnode["l"].get_bool();
			lr.vertical = vector2d(lrnode["y1"], lrnode["y2"]);
			landr.push_back(lr);
		}
	}

	ladderrope* laddersropes::getlr(vector2d pos, bool up)
	{
		for (vector<ladderrope>::iterator lrit = landr.begin(); lrit != landr.end(); ++lrit)
		{
			ladderrope* lr = lrit._Ptr;
			vector2d hor = vector2d(pos.x() - 25, pos.x() + 25);
			vector2d ver = up ? vector2d(lr->vertical.x(), lr->vertical.y() + 5) : vector2d(lr->vertical.x() - 5, lr->vertical.y());
			if (hor.contains(lr->x) && ver.contains(pos.y()))
			{
				return lr;
			}
		}

		return 0;
	}
}
