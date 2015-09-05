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
#include "statsinfo.h"
#include "Journey.h"

namespace io
{
	statsinfo::statsinfo(maplestats* st)
	{
		app.getimgcache()->setmode(ict_sys);

		nl::node src = nl::nx::nodes["UI"]["UIWindow4.img"]["Stat"]["main"];
		nl::node detail = nl::nx::nodes["UI"]["UIWindow4.img"]["Stat"]["detail"];

		sprites.push_back(sprite(animation(src["backgrnd"]), vector2d()));
		sprites.push_back(sprite(animation(src["backgrnd2"]), vector2d()));
		sprites.push_back(sprite(animation(src["backgrnd3"]), vector2d()));

		detailbgs.push_back(texture(detail["backgrnd"]));
		detailbgs.push_back(texture(detail["backgrnd2"]));
		detailbgs.push_back(texture(detail["backgrnd3"]));

		abilities["rare"] = texture(detail["abilityTitle"]["rare"]["0"]);
		abilities["epic"] = texture(detail["abilityTitle"]["epic"]["0"]);
		abilities["unique"] = texture(detail["abilityTitle"]["unique"]["0"]);
		abilities["legendary"] = texture(detail["abilityTitle"]["legendary"]["0"]);
		abilities["none"] = texture(detail["abilityTitle"]["normal"]["0"]);

		app.getimgcache()->unlock();
		stats = st;
		position = config.getstatspos();
		dimensions = vector2d();
		active = true;
	}
}
