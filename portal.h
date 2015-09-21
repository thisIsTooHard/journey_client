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
#include "animation.h"

using namespace graphics;

namespace maplemap
{
	enum portaltype : char
	{
		PT_SPAWN,
		PT_INVISIBLE,
		PT_REGULAR,
		PT_TOUCH,
		PT_4,
		PT_5,
		PT_WARP,
		PT_SCRIPTED,
		PT_SCRIPTED_INVISIBLE,
		PT_SCRIPTED_TOUCH,
		PT_HIDDEN,
		PT_SCRIPTED_HIDDEN,
		PT_SPRING1,
		PT_SPRING2,
		PT_14
	};

	class portal
	{
	public:
		portal() {}
		~portal() {}
		portal(portaltype, string, int, bool, string, animation, vector2d);
		void draw(ID2D1HwndRenderTarget*, vector2d);
		void update() { anim.update(8); }
		void settouch(bool t) { touched = t; }
		vector2d getposition() { return position; }
		rectangle2d bounds() { return rectangle2d(position, position + vector2d(30, 50)); }
		portaltype gettype() { return type; }
		pair<int, string> getwarpinfo() { return make_pair(targetid, intermap ? targetpname : name); }
		string getname() { return name; }
	private:
		animation anim;
		portaltype type;
		string name;
		vector2d position;
		int targetid;
		string targetpname;
		bool touched;
		bool intermap;
	};
}

