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
#include "portal.h"
#include "safemap.h"

namespace maplemap
{
	class mapportals
	{
	public:
		mapportals() {}
		~mapportals() {}
		void init();
		void load(node, int);
		void addportal(char, portaltype, string, int, bool, string, vector2d);
		void draw(vector2d);
		void update(rectangle2d);
		vector2d getspawnpoint(char);
		vector2d getspawnpoint(string);
		pair<int, string> getportal(rectangle2d);
		void clear() { portals.clear(); }
	private:
		safemap<char, portal> portals;
		map<portaltype, animation> animations;
	};
}
