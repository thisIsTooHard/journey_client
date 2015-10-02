/////////////////////////////////////////////////////////////////////////////
// This file is part of the Journey MMORPG client                           //
// Copyright � 2015 SYJourney                                               //
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
#include "cursor.h"
#include "Journey.h"

namespace io
{
	cursor::cursor()
	{
		position = vector2d();
		state = MST_IDLE;
	}

	void cursor::init()
	{
		node cursornode = nx::nodes["UI"]["Basic.img"]["Cursor"];

		for (mousestate i = MST_IDLE; i <= MST_RCLICK; i = static_cast<mousestate>(i + 1))
		{
			animations[i] = animation(cursornode[to_string(i)]);
		}
	}

	void cursor::draw()
	{
		animations[state].draw(frame, position);
	}

	void cursor::setstate(mousestate s)
	{
		if (state != s)
		{
			switch (s)
			{
			case MST_CLICKING:
				if (state == MST_IDLE || state == MST_CANCLICK || state == MST_CANCLICK2)
				{
				}
				break;
			}
			state = s;
			resetani();
		}
	}
}