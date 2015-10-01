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
#include "moveobject.h"

using namespace action;
using namespace graphics;

namespace gameplay
{
	enum bgtype : char
	{
		BGT_NORMAL,
		BGT_HTILED,
		BGT_VTILED,
		BGT_TILED,
		BGT_HMOVEA,
		BGT_VMOVEA,
		BGT_HMOVEB,
		BGT_VMOVEB,
		BGT_HSTRETCH,
		BGT_VSTRETCH,
		BGT_STRETCH
	};

	class background : public moveobject, public graphicobject
	{
	public:
		background(node, node, vector2d, vector2d);
		background() {}
		~background() {}
		void draw(vector2d);
		bool update();
		int cshiftx();
		int cshifty();
	private:
		animation ani;
		bgtype type;
		vector2d rpos;
		vector2d cpos;
		vector2d mapwalls;
		vector2d mapborders;
		bool flipped;
	};
}

