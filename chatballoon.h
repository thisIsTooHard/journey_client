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
#include "texture.h"
#include "textlabel.h"

using namespace graphics;

namespace io
{
	class chatballoon
	{
	public:
		chatballoon(char, string);
		chatballoon() {}
		~chatballoon() {}
		void draw(vector2d);
		void expire() { elapsed = 250; }
		bool update();
	private:
		textlabel text;
		texture arrow;
		texture center;
		texture east;
		texture northeast;
		texture north;
		texture northwest;
		texture west;
		texture southwest;
		texture south;
		texture southeast;
		short width;
		short height;
		short elapsed;
		short xtile;
		short ytile;
	};
}

