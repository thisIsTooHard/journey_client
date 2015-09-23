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
#include "texture.h"

using namespace graphics;

namespace character
{
	class facetype
	{
	public:
		facetype(int);
		facetype() {}
		~facetype() {}
		void draw(string, byte, vector2d, vector2d, bool);
		string getname() { return name; }
		byte getlastf(string s) { return static_cast<byte>(delays[s].size() - 1); }
		short getdelay(string s, byte f) { return delays[s][f]; }
	private:
		map<string, map<byte, texture>> textures;
		map<string, map<byte, short>> delays;
		string name;
	};
}

