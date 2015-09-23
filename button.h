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
#include "texture.h"

using namespace util;
using namespace std;
using namespace graphics;

namespace io
{
	enum buttontypes : char
	{
		BTT_REGULAR,
		BTT_ONESPRITE,
		BTT_AREA
	};

	class button
	{
	public:
		button(node);
		button(node, int, int);
		button(texture, texture, int, int);
		button(vector2d, vector2d);
		button() {}
		~button() {}
		void draw(vector2d);
		rectangle2d bounds(vector2d);
		void setstate(string s) { state = s; }
		void setposition(vector2d p) { position = p; }
		void setactive(bool a) { active = a; }
		bool isactive() { return active; }
		string getstate() { return state; }
	private:
		map<string, texture> textures;
		vector2d position;
		vector2d dimension;
		string state;
		char bttype;
		bool active;
	};
}

