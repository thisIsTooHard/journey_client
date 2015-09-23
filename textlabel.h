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
#include "stdfax.h"
#include "vector2d.h"

using namespace util;
using namespace std;

namespace graphics
{
	enum dwfonts
	{
		DWF_12L,
		DWF_12LL,
		DWF_12C,
		DWF_12BC,
		DWF_12R,
		DWF_14L,
		DWF_14C,
		DWF_14BC,
		DWF_14R,
		DWF_20C
	};

	enum textcolor
	{
		TXC_BLACK,
		TXC_WHITE,
		TXC_YELLOW,
		TXC_BLUE,
		TXC_RED,
		TXC_BROWN,
		TXC_GREY,
		TXC_ORANGE,
		TXC_MBLUE,
		TXC_VIOLET
	};

	enum textbg
	{
		TXB_NONE,
		TXB_NAMETAG
	};

	class textlabel
	{
	public:
		textlabel(dwfonts, textcolor, string, textbg);
		textlabel(dwfonts, textcolor, string);
		textlabel() { font = 0; brush = 0; bgbrush = 0; }
		~textlabel();
		void draw(string, vector2d);
		void draw(vector2d);
		float getlength() { return (font->GetFontSize() - 8.0f) * text.length() + 10.0f; }
		void settext(string s) { text = s; }
		void setmarker(bool b) { marker = b; }
		void setalpha(float a) { alpha = a; }
		string gettext() { return text; }
	private:
		IDWriteTextFormat* font;
		ID2D1SolidColorBrush* brush;
		ID2D1SolidColorBrush* bgbrush;
		textcolor color;
		textbg back;
		string text;
		float alpha;
		bool marker;
		vector2d position;
	};
}

