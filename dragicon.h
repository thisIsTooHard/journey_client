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
#include "skillicon.h"
#include "itemicon.h"
#include "keyboard.h"

using namespace graphics;

namespace io
{
	enum dragicontype : char
	{
		DIT_KEY,
		DIT_SKILLKEY,
		DIT_ITEMKEY,
		DIT_SKILL,
		DIT_ITEM
	};

	class dragicon
	{
	public:
		dragicon(dragicontype, texture, texture, vector2d, char, int);
		dragicon(dragicontype, itemicon, texture, vector2d, char, int);
		dragicon() {}
		~dragicon() {}
		void draw(vector2d);
		void dragdraw(vector2d);
		void setdrag(vector2d, vector2d);
		void resetdrag() { drag = false; }
		void setposition(vector2d p) { pos = p; }
		void setkeyicon(texture t) { keyicon.second = t; }
		bool dragged() { return drag; }
		char getkey() { return keybind; }
		int getaction() { return action; }
		dragicontype gettype() { return type; }
		rectangle2d bounds(vector2d);
	private:
		itemicon item_ico;
		skillicon skill_ico;
		pair<texture, texture> keyicon;
		dragicontype type;
		int action;
		char keybind;
		bool drag;
		vector2d pos;
		vector2d rel;
	};
}

