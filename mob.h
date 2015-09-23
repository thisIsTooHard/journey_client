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
#include "animation.h"
#include "attackinfo.h"
#include "mobdata.h"
#include "maplelook.h"
#include "graphicobject.h"
#include "gravityobject.h"

using namespace graphics;
using namespace action;
using namespace data;

namespace gameplay
{
	const int DAMAGECAP = 999999;

	class mob : public graphicobject, public gravityobject
	{
	public:
		mob(int, int, bool, vector2d, char, short, char, bool, char);
		mob() {}
		~mob() {}
		bool update();
		void draw(vector2d);
		void damage(attackinfo*);
		void showhp(char);
		void setmove(char, bool);
		void kill(char);
		rectangle2d bounds();
		void setstate(string);
		pair<int, bool> calcdamage(uniform_int_distribution<int>, float, float);
		void makeactive() { active = true; }
		bool isalive() { return state != "die1"; }
		bool isactive() { return active && isalive(); }
	private:
		void sendmoves(byte);
		mobdata* mdata;
		int mid;
		bool active;
		int oid;
		char hppercent;
		vector<movefragment> moves;
		vector2d absp;
		vector2d walls;
		string state;
		short speed;
		bool control;
		byte moved;
		char stance;
		char effect;
		bool fadein;
		bool dead;
		bool fade;
		bool fleft;
		char team;
	};
}

