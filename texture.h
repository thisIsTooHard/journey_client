/////////////////////////////////////////////////////////////////////////////
// This file is part of the Journey MMORPG client                           //
// Copyright � 2015 SYJourney                                               //
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
#include "rectangle2d.h"
#include "imagecache.h"

using namespace util;
using namespace nl;
using namespace std;
using namespace program;

namespace graphics
{
	class texture
	{
	public:
		texture(node);
		texture();
		~texture() {}
		void draw();
		void draw(vector2d);
		void draw(vector2d, float, float);
		void draw(vector2d, bool);
		void draw(vector2d, float);
		void draw(vector2d, float, bool);
		void draw(vector2d, vector2d);
		void draw(vector2d, vector2d, bool);
		void draw(vector2d, vector2d, float, bool);
		void draw(vector2d, vector2d, float, float, float);
		void shift(vector2d s) { origin -= s; }
		void setshift(vector2d s) { shf = s; }
		void setorigin(vector2d v) { origin = v; }
		bool isloaded() { return loaded; }
		vector2d getdimension() { return dimension; }
		vector2d getorigin() { return origin; }
		rectangle2d getbounds() { return rectangle2d(origin, origin + dimension); }
	private:
		pair<imgcontext, size_t> source;
		vector2d origin;
		vector2d dimension;
		vector2d shf;
		bool loaded;
	};
}

