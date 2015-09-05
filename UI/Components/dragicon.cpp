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
	dragicon::dragicon(texture txt, char kb, keyaction ka, texture key, vector2d p)
	{
		keyicon.first = txt;
		keyicon.second = key;
		keybind = kb;
		action = ka;
		pos = p;
		drag = false;
		type = dit_keyconfig;
	}

	dragicon::dragicon(itemicon ic, texture key, vector2d p)
	{
		item_ico = ic;
		keyicon.second = key;
		pos = p;
		drag = false;
		type = dit_keyitem;
	}

	dragicon::dragicon(skillicon ic, texture key, vector2d p)
	{
		skill_ico = ic;
		keyicon.second = key;
		pos = p;
		drag = false;
		type = dit_skill;
	}

	void dragicon::setdrag(vector2d cursor, vector2d parentpos)
	{
		rel = pos + parentpos + vector2d(0, 32) - cursor;
		drag = true;
	}

	void dragicon::draw(ID2D1HwndRenderTarget* target, vector2d parentpos)
	{
		if (!drag)
		{
			vector2d absp = pos + parentpos;

			switch (type)
			{
			case dit_keyconfig:
				keyicon.first.draw(absp + vector2d(0, 32));
				if (keyicon.second.isloaded())
				{
					keyicon.second.draw(absp + vector2d(3, 4));
				}
				break;
			case dit_keyitem:
				item_ico.draw(absp + vector2d(0, 32), 1.0f);
				if (keyicon.second.isloaded())
				{
					keyicon.second.draw(absp + vector2d(3, 4));
				}
				break;
			case dit_skill:
				skill_ico.draw(absp + vector2d(0, 32), 1.0f);
				if (keyicon.second.isloaded())
				{
					keyicon.second.draw(absp + vector2d(3, 4));
				}
				break;
			}
		}
	}

	void dragicon::dragdraw(ID2D1HwndRenderTarget* target, vector2d cursor)
	{
		if (drag)
		{
			switch (type)
			{
			case dit_keyconfig:
				keyicon.first.draw(cursor + rel, 0.5f);
				break;
			case dit_keyitem:
				item_ico.draw(cursor + rel, 0.5f);
				break;
			case dit_skill:
				skill_ico.draw(cursor + rel, 0.5f);
				break;
			}
		}
	}
}
