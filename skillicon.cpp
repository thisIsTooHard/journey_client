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
#include "skillicon.h"
#include "nxfile.h"

namespace io
{
	skillicon::skillicon(int id)
	{
		nl::nx::view_file("Skill");

		string fullname;
		string skillstr = to_string(id);
		char extend = 7 - skillstr.length();
		for (char i = 0; i < extend; i++)
		{
			fullname.append("0");
		}
		fullname.append(skillstr);

		nl::node src = nl::nx::nodes["Skill"][fullname.substr(0, 3) + ".img"]["skill"][fullname];

		textures["normal"] = texture(src["icon"]);
		textures["disabled"] = texture(src["iconDisabled"]);
		textures["mouseOver"] = texture(src["iconMouseOver"]);

		nl::nx::unview_file("Skill");

		state = "normal";
	}

	void skillicon::draw(vector2d pos, float alpha)
	{
		textures[state].draw(pos, alpha);
	}
}
