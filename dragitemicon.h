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
#include "itemicon.h"

namespace io
{
	enum itemicontype
	{
		IICT_KEY,
		IICT_INVENT,
		IICT_EQUIP
	};

	class dragitemicon : public itemicon
	{
	public:
		dragitemicon(itemicontype, map<bool, texture>, int, short, short, vector2d);
		~dragitemicon() {}
		void draw(vector2d);
		void dragdraw(vector2d);
		void ondrop();
		void setdrag(vector2d, vector2d);
		void resetdrag();
		void setposition(vector2d p) { pos = p; }
		short getslot() { return slot; }
		bool candrag() { return true; }
		icontype gettype() { return ICN_ITEM; }
		itemicontype getiitype() { return type; }
		rectangle2d bounds(vector2d v) { return itemicon::bounds(pos + v); }
	private:
		itemicontype type;
		short slot;
		vector2d pos;
		vector2d rel;
		bool drag;
	};
}

