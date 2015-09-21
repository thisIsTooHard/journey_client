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
#include "charset.h"
#include "gravityobject.h"

using namespace graphics;
using namespace action;

namespace gameplay
{
	const int DAMAGECAP = 999999;

	class mob : public gravityobject
	{
	public:
		mob(int, int, bool, vector2d, char, short, char, bool, char, footholdtree*);
		mob() {}
		~mob() {}
		bool update();
		void draw(ID2D1HwndRenderTarget*, vector2d);
		void damage(attackinfo*);
		void showhp(char);
		void setmove(char, bool);
		void kill(char);
		rectangle2d bounds();
		void setstate(string st) { state = st; }
		void makeactive() { active = true; }
		bool isalive() { return state != "die1"; }
		bool isactive() { return active && isalive(); }
	private:
		pair<int, bool> calcdamage(uniform_int_distribution<int>, float, float);
		void sendmoves(byte);
		map<string, animation> textures;
		map<string, texture> uitextures;
		map<string, rectangle2d> hitrect;
		float alpha;
		bool active;
		int oid;
		int mid;
		string name;
		string sndpath;
		short level;
		short speed;
		short watk;
		short matk;
		short wdef;
		short mdef;
		short acc;
		short eva;
		short knockback;
		bool undead;
		bool touchdamage;
		char hppercent;
		vector2d absp;
		vector2d walls;
		string state;
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

