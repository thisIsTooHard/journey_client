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
#include "gravityobject.h"
#include "texture.h"

using namespace action;
using namespace graphics;

namespace maplemap
{
	enum dropstate
	{
		DST_DROPPED,
		DST_FLOATING,
		DST_INACTIVE,
		DST_EXPIRE,
		DST_PICKEDUP
	};

	class drop : public gravityobject
	{
	public:
		drop() {}
		virtual ~drop() {}
		virtual void draw(vector2d) {}
		virtual bool update();
		void init(char);
		void expire(char, moveobject*);
		void makeactive() { if (state == DST_INACTIVE) state = DST_FLOATING; }
		int getid() { return oid; }
		rectangle2d bounds() { return rectangle2d(getposition(), getposition() + vector2d(32, 32)); }
	protected:
		short oid;
		int owner;
		vector2d pos;
		vector2d dest;
		moveobject* looter;
		char pickuptype;
		bool playerdrop;
		dropstate state;
		float dalpha;
		float basey;
		float moved;
	};
}

