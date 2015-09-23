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
		string category;
		switch (id / 1000000)
		{
		case 2:
			category = "Consume";
			break;
		case 3:
			category = "Install";
			break;
		case 4:
			category = "Etc";
			break;
		case 5:
			category = "Cash";
			break;
		default:
			category = "";
		}

		if (category.size() > 0)
		{
			nx::view_file("Item");

			node src = nx::nodes["Item"][category]["0" + to_string(id / 10000) + ".img"]["0" + to_string(id)]["info"];
			icon[false] = texture(src["icon"]);
			icon[true] = texture(src["iconRaw"]);

			nx::unview_file("Item");

			category = (category == "Install") ? "Ins" : category;

			nx::view_file("String");

			node strsrc = nx::nodes["String"][category + ".img"][to_string(id)];
			name = strsrc["name"];
			desc = strsrc["desc"];

			nx::unview_file("String");
		}

		itemid = id;
		loaded = name.size() > 0;
	}
}
