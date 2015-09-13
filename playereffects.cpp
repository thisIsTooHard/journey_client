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
	playereffects::playereffects()
	{
		efflock = SRWLOCK_INIT;
		top = 0;
	}

	void playereffects::add(effect efc)
	{
		AcquireSRWLockExclusive(&efflock);
		effects[top] = efc;
		top++;
		ReleaseSRWLockExclusive(&efflock);
	}

	void playereffects::draw(ID2D1HwndRenderTarget* target, vector2d playerpos)
	{
		if (TryAcquireSRWLockShared(&efflock))
		{
			for (map<int, effect>::iterator efit = effects.begin(); efit != effects.end(); ++efit)
			{
				efit->second.draw(target, playerpos);
			}
			ReleaseSRWLockShared(&efflock);
		}
	}

	void playereffects::update()
	{
		vector<int> toremove;

		if (TryAcquireSRWLockShared(&efflock))
		{
			for (map<int, effect>::iterator efit = effects.begin(); efit != effects.end(); ++efit)
			{
				bool remove = efit->second.update();

				if (remove)
				{
					toremove.push_back(efit->first);
				}
			}
			ReleaseSRWLockShared(&efflock);
		}

		if (toremove.size() > 0)
		{
			AcquireSRWLockExclusive(&efflock);
			for (vector<int>::iterator rmit = toremove.begin(); rmit != toremove.end(); ++rmit)
			{
				effects.erase(*rmit);
			}
			ReleaseSRWLockExclusive(&efflock);
		}
	}
}
