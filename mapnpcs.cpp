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
#include "mapnpcs.h"
#include "Journey.h"

namespace maplemap
{
	void mapnpcs::addnpc(int oid, int id, bool front, short fh, vector2d pos)
	{
		if (npcs.contains(oid))
		{

		}
		else
		{
			app.getimgcache()->setmode(ict_map);
			npc toadd = npc(id, oid, front, fh, pos);
			app.getimgcache()->unlock();

			npcs.add(oid, toadd);
			app.getui()->getbase()->addnpcbutton(oid, pos, toadd.getdim());
		}
	}

	void mapnpcs::draw(vector2d viewpos)
	{
		for (smit<int, npc> npcit = npcs.getit(); npcit.belowtop(); npcit++)
		{
			npcit->draw(viewpos);
		}
	}

	void mapnpcs::update()
	{
		for (smit<int, npc> npcit = npcs.getit(); npcit.belowtop(); npcit++)
		{
			npcit->update();
		}
	}
}
