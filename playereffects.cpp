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
#include "playereffects.h"

namespace gameplay
{
	void playereffects::add(sprite efc)
	{
		effects.add(top, efc);
		top++;
	}

	void playereffects::draw(vector2d playerpos)
	{
		for (smit<int, sprite> efit = effects.getit(); efit.belowtop(); ++efit)
		{
			efit->draw(playerpos);
		}
	}

	void playereffects::update()
	{
		vector<int> toremove;

		for (smit<int, sprite> efit = effects.getit(); efit.belowtop(); ++efit)
		{
			bool remove = efit->update();

			if (remove)
			{
				toremove.push_back(efit.getindex());
			}
		}

		if (toremove.size() > 0)
		{
			for (vector<int>::iterator rmit = toremove.begin(); rmit != toremove.end(); ++rmit)
			{
				effects.remove(*rmit);
			}
		}
	}
}
