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
#include "graphicobject.h"

using namespace graphics;

namespace io
{
	enum mousestate : char 
	{
		MST_IDLE = 0,
		MST_CANCLICK = 1,
		MST_GAME = 2,
		MST_HOUSE = 3,
		MST_CANCLICK2 = 4,
		MST_CANGRAB = 5,
		MST_GIFT = 6,
		MST_VSCROLL = 7,
		MST_HSCROLL = 8,
		MST_VSCROLLIDLE = 9,
		MST_HSCROLLIDLE = 10,
		MST_GRABBING = 11,
		MST_CLICKING = 12,
		MST_RCLICK = 13
	};

	class cursor : public graphicobject
	{
	public:
		cursor();
		~cursor() {}
		void init();
		void draw();
		void setstate(mousestate);
		void update() { graphicobject::update(&animations[state]); }
		void setposition(vector2d p) { position = p; }
		mousestate getstate() { return state; }
		vector2d getposition() { return position; }
	private:
		mousestate state;
		map<mousestate, animation> animations;
		vector2d position;
	};
}

