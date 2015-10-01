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
#include "tooltip.h"
#include "itemdata.h"
#include "itemtext.h"

using namespace data;

namespace io
{
	class itemtooltip : public tooltip
	{
	public:
		itemtooltip() {}
		~itemtooltip() {}
		void init();
		void draw(vector2d);
		void setitem(itemdata*);
		void clear() { itemid = 0; }
		int getid() { return itemid; }
	private:
		int itemid;
		itemdata* item;
		int filllength;
		textlabel name;
		texture top;
		texture mid;
		texture bot;
		texture line;
		texture base;
		texture cover;
		texture shade;
	};
}

