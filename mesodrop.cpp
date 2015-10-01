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
#include "mesodrop.h"
#include "nxfile.h"

namespace maplemap
{
	mesodrop::mesodrop(short o, animation* ani, int own, vector2d ps, vector2d dst, char type, char mod)
	{
		oid = o;
		anim = ani;
		owner = own;
		pickuptype = type;
		dest = dst;
		pos = ps;

		init(mod);
	}

	void mesodrop::draw(vector2d viewpos)
	{
		if (state != DST_INACTIVE)
		{
			graphicobject::draw(anim, getposition() + viewpos - vector2d(16, 0), false);
		}
	}

	bool mesodrop::update()
	{
		if (state != DST_INACTIVE)
		{
			graphicobject::update(anim, 8);
		}
		alpha = dalpha;

		return drop::update();
	}
}
