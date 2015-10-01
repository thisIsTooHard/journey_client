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
#include "charset.h"
#include "icon.h"

using namespace graphics;

namespace io
{
	class itemicon : public icon
	{
	public:
		itemicon(map<bool, texture>, int, bool, short);
		itemicon() {}
		~itemicon() {}
		void draw(vector2d);
		void onmouseover();
		void toggle() { raw = !raw; }
		void setqty(short q) { qty = q; showcount = q > 1; }
		int getid() { return iid; }
		icontype gettype() { return ICN_ITEM; }
		virtual void ondrop() { resetdrag(); }
		virtual bool candrag() { return false; }
		virtual rectangle2d bounds(vector2d p) { return rectangle2d(p, p + vector2d(32, 32)); }
	protected:
		map<bool, texture> textures;
		charset* countset;
		int iid;
		short qty;
		bool showcount;
		bool raw;
		float alpha;
	};
}

