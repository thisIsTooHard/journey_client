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
#include "graphicobject.h"

namespace graphics
{
	graphicobject::graphicobject()
	{
		elapsed = 0;
		frame = 0;
		alpha = 1.0f;
		alphastep = 0.0f;
	}

	bool graphicobject::draw(animation* ani, vector2d pos, bool flip)
	{
		if (ani)
		{
			texture* txt = ani->gettexture(frame);
			if (txt)
			{
				txt->draw(pos, alpha, flip);
				return true;
			}
		}
		return false;
	}

	bool graphicobject::update(animation* ani)
	{
		return update(ani, DPF);
	}

	bool graphicobject::update(animation* ani, short amount)
	{
		if (ani)
		{
			if (ani->isanimated())
			{
				elapsed += amount;

				if (ani->hasblending(frame))
				{
					alpha += alphastep;
					if (alpha < 0.f)
						alpha = 0.f;
					else if (alpha > 255.f)
						alpha = 255.f;
				}

				short delay = ani->getdelay(frame);
				if (elapsed > delay)
				{
					elapsed -= delay;

					frame = ani->nextframe(frame);

					if (ani->hasblending(frame))
					{
						float nexta = ani->getalpha(frame) - alpha;
						alphastep = (nexta * amount) / ani->getdelay(frame);
					}

					return frame == 0;
				}
			}
		}

		return false;
	}

	void graphicobject::resetani()
	{
		elapsed = 0;
		frame = 0;
		alphastep = 0.0f;
	}
}
