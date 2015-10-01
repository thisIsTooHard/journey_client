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
#include "mapletext.h"

namespace io
{
	mapletext::mapletext(txtargs text, dwfonts font, vector2d bounds)
	{
		size_t length = text.text.size();
		size_t pos = 0;
		deffont = font;
		defcolor = text.color;
		defbounds = bounds;

		vector<string> lines;
		while (pos < length)
		{
			size_t split = text.text.find("\\n", pos);
			if (split != string::npos)
			{
				lines.push_back(text.text.substr(pos, split));
				pos = split + 2;
			}
			else
			{
				lines.push_back(text.text.substr(pos));
				pos = length;
			}
		}

		drawpos = vector2d();
		for (vector<string>::iterator lnit = lines.begin(); lnit != lines.end(); ++lnit)
		{
			convertline(*lnit);
		}
	}

	void mapletext::convertline(string line)
	{
		size_t length = line.size();
		size_t pos = 0;

		while (pos < length)
		{
			size_t special = line.find_first_of('#', pos);
			if (special != string::npos)
			{
				if (length > special + 1)
				{
					char arg = line[special + 1];

					textcolor lastc = defcolor;
					switch (arg)
					{
					case 'k':
						defcolor = TXC_BLACK;
						break;
					case 'r':
						defcolor = TXC_RED;
						break;
					}

					if (defcolor != lastc)
					{
						textlabel lastline = textlabel(deffont, lastc, line.substr(pos, special), defbounds);
						textlabels.push_back(make_pair(lastline, drawpos));
						pos = special + 2;
						drawpos += lastline.getend();
					}
				}
			}
			else
			{
				textlabel lastline = textlabel(deffont, defcolor, line.substr(pos), defbounds);
				textlabels.push_back(make_pair(lastline, drawpos));
				pos = length;
				drawpos = vector2d(0, lastline.getheight() + 9);
			}
		}
	}

	void mapletext::draw(vector2d parentpos)
	{
		for (vector<pair<textlabel, vector2d>>::iterator tlit = textlabels.begin(); tlit != textlabels.end(); ++tlit)
		{
			tlit->first.draw(parentpos + tlit->second);
		}
		for (vector<pair<texture, vector2d>>::iterator icit = icons.begin(); icit != icons.end(); ++icit)
		{
			icit->first.draw(parentpos + icit->second);
		}
	}
}
