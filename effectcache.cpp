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
#include "effectcache.h"
#include "nxfile.h"

namespace data
{
	void effectcache::init()
	{
		node src = nx::nodes["Effect"];
		node basic = src["BasicEff.img"];

		effects[0] = animation(basic["LevelUp"]);
		effects[8] = animation(basic["JobChanged"]);
		effects[10] = animation(basic["MonsterBook"]["cardGet"]);
		effects[15] = animation(basic["ItemLevelUp"]);
		effects[16] = animation(basic["ItemMake"]["Success"]);
	}

	effect effectcache::geteffect(char id)
	{
		if (effects.count(id))
		{
			return effect(&effects[id], false, 8);
		}
		else
		{
			return effect();
		}
	}
}
