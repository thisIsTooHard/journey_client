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
#include "texture.h"
#include "icon.h"
#include "keyboard.h"

using namespace graphics;

namespace io
{
	class keyicon : public icon
	{
	public:
		keyicon(texture, texture, char, keyaction, vector2d);
		~keyicon() {}
		void draw(vector2d);
		void dragdraw(vector2d);
		void setdrag(vector2d, vector2d);
		void resetdrag() { drag = false; }
		void onmouseover() {}
		void ondrop() { resetdrag(); }
		void setkeytxt(texture t) { keytxt = t; }
		void setposition(vector2d p) { pos = p; }
		bool candrag() { return true; }
		char getkey() { return key; }
		keyaction getaction() { return action; }
		icontype gettype() { return ICN_KEY; }
		rectangle2d bounds(vector2d p) { return rectangle2d(p + pos, p + pos + vector2d(32, 32)); }
	private:
		texture acttxt;
		texture keytxt;
		keyaction action;
		char key;
		vector2d pos;
		vector2d rel;
		bool drag;
	};
}

