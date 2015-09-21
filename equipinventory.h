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
#include "uielement.h"
#include "player.h"

using namespace gameplay;

namespace io
{
	class equipinventory : public uielement
	{
	public:
		equipinventory(player*);
		~equipinventory() {}
		void draw(ID2D1HwndRenderTarget*);
		void buttonpressed(short);
		void oniteminfo(dragicon*);
		rectangle2d dragarea();
	private:
		maplelook* look;
		inventory* invent;
		maplestats* stats;
		vector<texture> petsprites;
		bool showpet;
	};
}

