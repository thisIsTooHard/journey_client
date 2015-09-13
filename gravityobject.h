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
#include "moveobject.h"
#include "footholdtree.h"

using namespace gameplay;

namespace action
{
	const float maxvspeed = 7.7f;
	const float grvacc = 0.5f;

	class gravityobject : public moveobject
	{
	public:
		gravityobject(vector2d, footholdtree*);
		gravityobject() {}
		virtual ~gravityobject() {}
		bool update();
	protected:
		footholdtree* footholds;
		foothold fh;
	};
}

