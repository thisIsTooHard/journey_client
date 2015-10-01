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
#include "vplayer.h"
#include "account.h"
#include "inventory.h"
#include "footholdtree.h"
#include "laddersropes.h"
#include "attackinfo.h"
#include "skillbook.h"
#include "questlog.h"
#include "telerock.h"
#include "monsterbook.h"

using namespace character;
using namespace data;

namespace gameplay
{
	const float FALLSPEED = 7.5f;
	const float GRAVITYACC = 0.5f;
	const float JUMPSPEED = 8.8f;
	const float WALKSPEED = 1.8f;

	enum moveinput : char
	{
		MIN_LEFT,
		MIN_RIGHT,
		MIN_DOWN,
		MIN_UP,
		MIN_JUMP
	};

	class player : public vplayer
	{
	public:
		player() {}
		~player() {}
		player(maplechar*);
		void init(int, skillbook, questlog, map<short, string>);
		void setinventory(inventory ivt) { invent = ivt; }
		void setposition(vector2d);
		void updatefht();
		void setstate(playerstate);
		bool tryclimb(bool);
		void trysit();
		void sit(bool);
		void key_jump(bool);
		void key_left(bool);
		void key_right(bool);
		void key_down(bool);
		void key_up(bool);
		void draw(vector2d);
		bool update();
		void setaction(string);
		void recalcstats(bool);
		void sendmoves(bool);
		float getattspeed();
		bool limitstate();
		bool tryattack(attackinfo*, int, short, short);
		void setexpression(char c) { look->setexpression(c); }
		bool getleft() { return fleft; }
		int getid() { return stats->getid(); }
		string getname() { return stats->getname(); }
		rectangle2d bounds() { return rectangle2d(position - vector2d(30, 70), position + vector2d(30, 10)); }
		maplestats* getstats() { return stats; }
		maplelook* getlook() { return look; }
		playereffects* geteffects() { return &effects; }
		inventory* getinventory() { return &invent; }
		skillbook* getskills() { return &skills; }
		telerock* gettrock() { return &trock; }
		monsterbook* getbook() { return &book; }
	private:
		maplestats* stats;
		maplelook* look;
		textlabel name;
		playereffects effects;
		inventory invent;
		skillbook skills;
		questlog quests;
		telerock trock;
		monsterbook book;
		map<short, string> areainfo;
		vector<movefragment> moves;
		footholdtree* footholds;
		ladderrope* ladrrope;
		foothold fh;
		bool fleft;
		short elapsed;
		short speed;
		short jump;
		vector2d position;
		vector2d c_debug;
		float ground;
		bool nofriction;
		bool candjump;
		playerstate state;
		map<moveinput, bool> keydown;
	};
}

