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
#include "itemdrop.h"
#include "mesodrop.h"
#include "safeptrmap.h"

namespace maplemap
{
	class mapdrops
	{
	public:
		mapdrops() {}
		~mapdrops() { drops.clear(); }
		void init();
		void adddrop(short, int, bool, int, vector2d, vector2d, char, char);
		void removedrop(short, char, moveobject*);
		void draw(vector2d);
		void update();
		drop* trypickup(rectangle2d);
		void clear() { drops.clear(); }
	private:
		safeptrmap<short, drop*> drops;
		map<mesoamount, animation> mesos;
	};
}

