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
#include "effect.h"

namespace graphics
{
	effect::effect(animation* a, bool f, int16_t s)
	{
		anim = a;
		flip = f;
		speed = s;

		resetani();
	}

	void effect::draw(vector2d pos)
	{
		if (anim)
		{
			texture* txt = anim->gettexture(frame);
			if (txt)
			{
				txt->draw(pos, flip);
			}
		}
	}

	bool effect::update()
	{
		if (anim)
		{
			return graphicobject::update(anim, speed);
		}
		else
		{
			return true;
		}
	}
}
