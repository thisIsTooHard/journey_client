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
#include "stdfax.h"
#include "maplestats.h"
#include "maplelook.h"

namespace gameplay
{
	class maplechar
	{
	public:
		maplechar() {}
		~maplechar() {}
		maplechar(maplestats, maplelook);
		maplelook* getlook();
		maplestats* getstats();
		maplestats copystats();
		maplelook copylook();
		void setrankinfo(int r, char rm, int jr, char jrm) { rank = make_pair(r, rm); jobrank = make_pair(jr, jrm); }
		pair<int, char> getrank() { return rank; }
		pair<int, char> getjobrank() { return jobrank; }
	private:
		maplestats stats;
		maplelook look;
		pair<int, char> rank;
		pair<int, char> jobrank;
	};
}

