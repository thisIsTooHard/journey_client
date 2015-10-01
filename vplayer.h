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
#include "maplelook.h"
#include "playereffects.h"

using namespace action;

namespace gameplay
{
	enum playerstate : char
	{
		PST_WALK = 2,
		PST_STAND = 4,
		PST_FALL = 6,
		PST_ALERT = 8,
		PST_PRONE = 10,
		PST_SWIM = 12,
		PST_LADDER = 14,
		PST_ROPE = 16,
		PST_DIED = 18,
		PST_SIT = 20,
		PST_SKILL = 22
	};

	class vplayer : public moveobject
	{
	public:
		virtual ~vplayer() {}
		virtual int getid() = 0;
		virtual maplelook* getlook() = 0;
		virtual playereffects* geteffects() = 0;
		virtual string getname() = 0;
		virtual void draw(vector2d) = 0;
	};
}

