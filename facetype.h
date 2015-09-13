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
		facetype(int, map<string, map<byte, vector2d>>);
		facetype() {}
		~facetype() {}
		void draw(vector2d);
		void update();
		void setexp(char);
		byte getframe() { return frame; }
		string getname() { return name; }
		string getexp() { return expression; }
		vector2d getshift(string s, byte f) { return facepos[s][f]; }
	private:
		map<string, map<byte, texture>> textures;
		map<string, map<byte, short>> delays;
		map<string, map<byte, vector2d>> facepos;
		string expression;
		short elapsed;
		byte frame;
		string name;
	};
}

