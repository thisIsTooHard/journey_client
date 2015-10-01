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
#include "textlabel.h"
#include "texture.h"

using namespace graphics;

namespace io
{
	class mapletext
	{
	public:
		mapletext(txtargs, dwfonts, vector2d);
		mapletext() {}
		~mapletext() {}
		void draw(vector2d);
		int getheight() { return drawpos.y(); }
	private:
		void convertline(string);
		vector<pair<textlabel, vector2d>> textlabels;
		vector<pair<texture, vector2d>> icons;
		vector2d defbounds;
		vector2d drawpos;
		dwfonts deffont;
		textcolor defcolor;
	};
}

