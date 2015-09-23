//////////////////////////////////////////////////////////////////////////////
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
#include "animation.h"

using namespace graphics;

namespace data
{
	class mobdata
	{
	public:
		mobdata(int);
		mobdata() {}
		~mobdata() {}
		void draw(string, byte, float, bool, vector2d);
		short getldelta(short);
		string getname() { return name; }
		short getlvl() { return level; }
		short getspeed() { return speed; }
		short getwatk() { return watk; }
		short getmatk() { return matk; }
		short getwdef() { return wdef; }
		short getmdef() { return mdef; }
		short getacc() { return accuracy; }
		short geteva() { return avoid; }
		short getkb() { return knockback; }
		rectangle2d bounds(string st) { return rect[st]; }
		animation* getani(string st) { return textures.count(st) ? &textures[st] : 0; }
	private:
		map<string, animation> textures;
		map<string, rectangle2d> rect;
		string name;
		short level;
		short speed;
		short watk;
		short matk;
		short wdef;
		short mdef;
		short accuracy;
		short avoid;
		short knockback;
		bool undead;
		bool touchdamage;
	};
}

