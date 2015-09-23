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
#include "stdfax.h"
#include "node.h"
#include "vector2d.h"

using namespace util;
using namespace std;
using namespace nl;

namespace data
{
	struct foothold
	{
		short id;
		short prev;
		short next;
		vector2d horizontal;
		vector2d vertical;

		int getid() { return id; }
		bool iswall() { return horizontal.x() == horizontal.y(); }
		bool isfloor() { return vertical.x() == vertical.y(); }
		bool hcontains(int x) { return horizontal.contains(x); }
		bool vcontains(int y) { return vertical.contains(y); }
		int gethdelta() { return horizontal.y() - horizontal.x(); }
		int getvdelta() { return vertical.y() - vertical.x(); }
		float getslope() { return iswall() ? 0 : static_cast<float>(getvdelta()) / gethdelta(); }
		float resolvex(int x) { return isfloor() ? vertical.x() : getslope() * (x - horizontal.x()) + vertical.x(); }
		vector2d getledge() { return vector2d(horizontal.x() - 1, vertical.x()); }
		vector2d getredge() { return vector2d(horizontal.y() + 1, vertical.y()); }
	};

	class footholdtree
	{
	public:
		footholdtree(node);
		footholdtree() {}
		~footholdtree() {}
		float getgroundbelow(vector2d);
		float nextground(bool, vector2d);
		vector2d getwalls();
		vector2d getborders();
		vector2d getpfedges(short);
		foothold getfh(short);
		foothold getnext(bool, foothold);
		foothold getbelow(vector2d);
	private:
		map<short, foothold> footholds;
		vector<map<short, short>> platforms;
		vector<short> edgesl;
		vector<short> edgesr;
		foothold ground;
		foothold lwall;
		foothold rwall;
		int lowestg;
	};
}

