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
#include "itemdata.h"
#include "nxfile.h"

namespace data
{
	itemdata::itemdata(int id)
	{
		int32_t prefix = id / 1000000;

		node strsrc = nx::nodes["String"];

		string category;
		switch (prefix)
		{
		case 2:
			category = "Consume";
			strsrc = strsrc["Consume.img"][to_string(id)];
			break;
		case 3:
			category = "Install";
			strsrc = strsrc["Ins.img"][to_string(id)];
			break;
		case 4:
			category = "Etc";
			strsrc = strsrc["Etc.img"]["Etc"][to_string(id)];
			break;
		case 5:
			category = "Cash";
			strsrc = strsrc["Cash.img"][to_string(id)];
			break;
		default:
			category = "";
		}

		if (category.size() > 0)
		{
			node src = nx::nodes["Item"][category]["0" + to_string(id / 10000) + ".img"]["0" + to_string(id)]["info"];
			icon[false] = texture(src["icon"]);
			icon[true] = texture(src["iconRaw"]);

			name = strsrc["name"];
			desc = strsrc["desc"];

			txtargs descargs;
			descargs.text = desc;
			descargs.color = TXC_WHITE;
			desctext = itemtext(descargs, DWF_12LL, vector2d(150, 0));
		}

		itemid = id;
		loaded = name.size() > 0;
	}
}
