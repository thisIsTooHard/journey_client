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
#include "charsprites.h"

namespace character
{
	void charsprites::draw(charlayer layer, string state, byte frame, vector2d pos, bool flip)
	{
		if (textures.count(layer))
		{
			if (textures[layer].count(state))
			{
				if (textures[layer][state].count(frame))
				{
					textures[layer][state][frame].draw(pos, flip);
				}
			}
		}
	}

	void charsprites::draw(charlayer layer, string state, byte frame, vector2d pos, vector2d shift, bool flip)
	{
		if (textures.count(layer))
		{
			if (textures[layer].count(state))
			{
				if (textures[layer][state].count(frame))
				{
					textures[layer][state][frame].setshift(shift);
					textures[layer][state][frame].draw(pos, flip);
				}
			}
		}
	}
}
