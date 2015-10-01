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
#include "keyicon.h"

namespace io
{
	keyicon::keyicon(texture at, texture kt, char k, keyaction a, vector2d p)
	{
		acttxt = at;
		keytxt = kt;
		key = k;
		action = a;
		pos = p;
	}

	void keyicon::draw(vector2d parentpos)
	{
		if (!drag)
		{
			acttxt.draw(pos + parentpos, 1.0f);
			keytxt.draw(pos + parentpos, 1.0f);
		}
	}

	void keyicon::dragdraw(vector2d cursor)
	{
		if (drag)
		{
			acttxt.draw(cursor + rel, 0.5f);
		}
	}

	void keyicon::setdrag(vector2d cursor, vector2d parentpos)
	{
		rel = pos + parentpos + vector2d(0, 32) - cursor;
		drag = true;
	}
}
