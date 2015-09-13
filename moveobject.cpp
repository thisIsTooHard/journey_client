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
#include "moveobject.h"

namespace action
{
	moveobject::moveobject(vector2d pos)
	{
		fx = static_cast<float>(pos.x());
		fy = static_cast<float>(pos.y());
		hspeed = 0;
		vspeed = 0;
	}

	bool moveobject::update()
	{
		fx += hspeed;
		fy += vspeed;

		return false;
	}

	vector2d moveobject::getposition()
	{
		int posx = static_cast<int>(fx);
		int posy = static_cast<int>(fy);
		return vector2d(posx, posy);
	}
}
