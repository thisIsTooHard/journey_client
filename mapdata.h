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
#include "mapinfo.h"
#include "footholdtree.h"
#include "laddersropes.h"

namespace data
{
	class mapdata
	{
	public:
		mapdata() {}
		~mapdata() {}
		void init();
		void load(int);
		int getid() { return id; }
		mapinfo* getinfo() { return &info; }
		laddersropes* getlandr() { return &landr; }
		footholdtree* getfht() { return &fht; }
	private:
		mapinfo info;
		laddersropes landr;
		footholdtree fht;
		int id;
	};
}

