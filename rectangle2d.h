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
#include "vector2d.h"

namespace util
{
	class rectangle2d
	{
	public:
		rectangle2d(int, int, int, int);
		rectangle2d(vector2d, vector2d);
		rectangle2d();
		~rectangle2d() {}
		bool contains(vector2d);
		bool contains(int, vector2d);
		bool overlaps(rectangle2d);
		bool straight() { return lt == rb; }
		void setlt(vector2d l) { lt = l; }
		void setrb(vector2d r) { rb = r; }
		void shift(vector2d v) { lt = lt + v; rb = rb + v; }
		void shiftlt(vector2d l) { lt = lt + l; }
		void shiftrb(vector2d r) { rb = rb + r; }
		vector2d getlt() { return lt; }
		vector2d getrb() { return rb; }
	private:
		vector2d lt;
		vector2d rb;
	};
}

