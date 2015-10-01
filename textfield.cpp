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
#include "textfield.h"

namespace io
{
	textfield::textfield(textid i, dwfonts fnt, textcolor col, string def, vector2d pos, int max)
	{
		init();

		getfont(fnt);
		settext(def);

		color = col;
		id = i;
		position = pos;
		maxlength = max;

		marker = textlabel(fnt, col, "|");
		markpos = text.length();
		crypt = 0;
		active = true;
		focused = false;
		showmark = false;
	}

	rectangle2d textfield::bounds(vector2d parentpos)
	{
		vector2d absp = position + parentpos;
		return rectangle2d(absp, absp + vector2d(14 * maxlength, 24));
	}

	void textfield::draw(vector2d parentpos)
	{
		if (active)
		{
			vector2d absp = position + parentpos;

			if (text.size() > 0)
			{
				if (crypt > 0)
				{
					string crtext;
					crtext.insert(0, text.size(), crypt);
					textlabel::drawover(crtext, absp);
				}
				else
				{
					textlabel::draw(absp);
				}
			}

			if (focused)
			{
				if (showmark)
				{
					marker.draw(absp + vector2d(getadvance(markpos), 0));
				}
			}
			else if (text.size() == 0)
			{
				bg.draw(absp + bgposition);
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
		markpos = text.length();
	}

	void textfield::sendchar(char letter)
	{
		if (letter == 0 && markpos > 0)
		{
			markpos--;
			text.erase(markpos, 1);
			textlabel::settext(text);
		}
		else if (letter > 2 && text.length() < maxlength)
		{
			text.insert(markpos, 1, letter);
			textlabel::settext(text);
			markpos++;
		}
		else if (letter == 1 && markpos > 0)
		{
			markpos -= 1;
		}
		else if (letter == 2 && markpos < text.length())
		{
			markpos += 1;
		}
	}

	void textfield::settext(string txt)
	{
		markpos = txt.length();
		textlabel::settext(txt);
	}
}
