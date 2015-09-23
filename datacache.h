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
#include "mapdata.h"
#include "equipcache.h"
#include "itemcache.h"
#include "mobcache.h"
#include "skillcache.h"

using namespace data;

namespace program
{
	class datacache
	{
	public:
		datacache() {}
		~datacache() {}
		mapdata* getmap() { return &mdata; }
		equipcache* getequips() { return &equips; }
		itemcache* getitems() { return &items; }
		mobcache* getmobs() { return &mobs; }
		skillcache* getskills() { return &skills; }
	private:
		mapdata mdata;
		equipcache equips;
		itemcache items;
		mobcache mobs;
		skillcache skills;
	};
}

