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
#include "rectangle2d.h"

namespace util
{
	rectangle2d::rectangle2d(int l, int r, int t, int b)
	{
		lt = vector2d(l, t);
		rb = vector2d(r, b);
	}

	rectangle2d::rectangle2d(vector2d v1, vector2d v2)
	{
		lt = v1;
		rb = v2;
	}

	rectangle2d::rectangle2d()
	{
		lt = vector2d();
		rb = vector2d();
	}

	bool rectangle2d::contains(vector2d v)
	{
		return !straight() && v.x() >= lt.x() && v.x() <= rb.x() && v.y() >= lt.y() && v.y() <= rb.y();
	}

	bool rectangle2d::contains(int x, vector2d ver)
	{
		vector2d rhor = vector2d(lt.x(), rb.x());
		vector2d rver = vector2d(lt.y(), rb.y());
		return rhor.contains(x) && rver.overlaps(ver);
	}

	bool rectangle2d::overlaps(rectangle2d ar)
	{
		vector2d rhor = vector2d(lt.x(), rb.x());
		vector2d rver = vector2d(lt.y(), rb.y()); 
		vector2d ahor = vector2d(ar.getlt().x(), ar.getrb().x());
		vector2d aver = vector2d(ar.getlt().y(), ar.getrb().y());
		return rhor.overlaps(ahor) && rver.overlaps(aver);
	}
}
