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
#include "textfield.h"

namespace io
{
	textfield::textfield(textid i, dwfonts fnt, textcolor col, string default, vector2d pos, int length)
	{
		id = i;
		content = textlabel(fnt, col, default);
		position = pos;
		maxlength = length;
		active = true;
		focused = false;
		showmark = false;
		markpos = default.length();
	}

	rectangle2d textfield::bounds(vector2d parentpos)
	{
		vector2d absp = position + parentpos;
		return rectangle2d(absp, absp + vector2d(content.getlength(), 24));
	}

	void textfield::draw(vector2d parentpos)
	{
		if (active)
		{
			vector2d absp = position + parentpos;

			if (content.gettext() == "" && !focused)
			{
				if (bg.isloaded())
				{
					bg.draw(absp + bgposition);
				}
			}
			else
			{
				if (focused && showmark && markpos == content.gettext().length())
				{
					content.setmarker(true);
				}
				else
				{
					content.setmarker(false);
				}

				content.draw(absp);
			}
		}
	}

	void textfield::update()
	{
		if (active)
		{
			elapsed += 16;

			if (elapsed >= 300)
			{
				showmark = !showmark;
				elapsed -= 300;
			}
		}
	}

	void textfield::setbg(texture b, int x, int y)
	{
		bg = b;
		bgposition = vector2d(x, y);
	}

	void textfield::setfocus(bool f)
	{
		elapsed = 0;
		showmark = true;
		focused = f;
		markpos = content.gettext().length();
	}

	void textfield::sendchar(char letter)
	{
		if (letter == 0 && markpos > 0)
		{
			markpos--; 
			string text = content.gettext();
			text.pop_back();
			content.settext(text);
		}
		else if (letter > 2 && content.gettext().length() < maxlength)
		{
			string text = content.gettext();
			text.push_back(letter);
			content.settext(text);
			markpos++;
		}
		else if (letter == 1 && markpos > 0)
		{
			//markpos -= 1;
		}
		else if (letter == 2 && markpos < content.gettext().length())
		{
			//markpos += 1;
		}
	}
}
