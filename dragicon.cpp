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
#include "dragicon.h"

namespace io
{
	dragicon::dragicon(dragicontype t, texture txt, texture key, vector2d p, char kb, int ka)
	{
		keyicon.first = txt;
		keyicon.second = key;
		pos = p;
		keybind = kb;
		action = ka;
		drag = false;
		type = t;
	}

	dragicon::dragicon(dragicontype t, itemicon ic, texture key, vector2d p, char slot, int iid)
	{
		item_ico = ic;
		keyicon.second = key;
		pos = p;
		keybind = slot;
		action = iid;
		drag = false;
		type = t;
	}

	void dragicon::setdrag(vector2d cursor, vector2d parentpos)
	{
		rel = pos + parentpos + vector2d(0, 32) - cursor;
		drag = true;
	}

	void dragicon::draw(vector2d parentpos)
	{
		if (!drag)
		{
			vector2d absp = pos + parentpos;

			switch (type)
			{
			case DIT_KEY:
			case DIT_SKILLKEY:
				keyicon.first.draw(absp + vector2d(0, 32));
				keyicon.second.draw(absp + vector2d(3, 4));
				break;
			case DIT_ITEMKEY:
				item_ico.draw(absp + vector2d(0, 32), 1.0f);
				keyicon.second.draw(absp + vector2d(3, 4));
				break;
			case DIT_ITEM:
				item_ico.draw(absp + vector2d(0, 32), 1.0f);
				break;
			}
		}
	}

	void dragicon::dragdraw(vector2d cursor)
	{
		if (drag)
		{
			switch (type)
			{
			case DIT_KEY:
			case DIT_SKILLKEY:
				keyicon.first.draw(cursor + rel, 0.5f);
				break;
			case DIT_SKILL:
				skill_ico.draw(cursor + rel, 0.5f);
				break;
			case DIT_ITEMKEY:
			case DIT_ITEM:
				item_ico.draw(cursor + rel, 0.5f);
				break;
			}
		}
	}

	rectangle2d dragicon::bounds(vector2d parentpos)
	{
		vector2d absp = pos + parentpos;
		return rectangle2d(absp, absp + vector2d(32, 32));
	}
}
