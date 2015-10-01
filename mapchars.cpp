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
#include "mapchars.h"

namespace maplemap
{
	void mapchars::addchar(int cid, maplelook toadd, byte level, short job, string name, vector2d pos)
	{
		if (chars.contains(cid))
		{

		}
		else
		{
			chars.add(cid, otherplayer(toadd, cid, level, job, name, pos));
		}
	}

	void mapchars::movechar(int cid, vector<movefragment> movements)
	{
		if (chars.contains(cid))
		{
			chars.get(cid)->addmoves(movements);
		}
	}

	void mapchars::removechar(int cid)
	{
		chars.removekey(cid);
	}

	void mapchars::draw(vector2d viewpos)
	{
		for (smit<int, otherplayer> plit = chars.getit(); plit.belowtop(); plit++)
		{
			plit->draw(viewpos);
		}
	}

	void mapchars::update()
	{
		for (smit<int, otherplayer> plit = chars.getit(); plit.belowtop(); plit++)
		{
			plit->update();
		}
	}
}
