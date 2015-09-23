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
#include "maplechar.h"
#include "playereffects.h"
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
	const float FALLSPEED = 7.7f;
	const float GRAVITYACC = 0.5f;
	const float JUMPSPEED = 8.5f;
	const float WALKSPEED = 1.8f;

	enum moveinput : char
	{
		MIN_LEFT,
		MIN_RIGHT,
		MIN_DOWN,
		MIN_UP,
		MIN_JUMP
	};

	enum playerstate : char
	{
		PST_WALK = 2,
		PST_STAND = 4,
		PST_FALL = 6,
		PST_ALERT = 8,
		PST_PRONE = 10,
		PST_SWIM = 12,
		PST_LADDER = 14,
		PST_ROPE = 16,
		PST_SKILL = 18
	};

	class player
	{
	public:
		player() {}
		~player() {}
		player(maplechar*);
		void setposition(vector2d);
		void updatefht();
		void setlr(ladderrope);
		void sit(bool);
		void key_jump(bool);
		void key_left(bool);
		void key_right(bool);
		void key_down(bool);
		void key_up(bool);
		bool tryattack(attackinfo*, int, short, short);
		void draw(vector2d);
		void setaction(string);
		void recalcstats(bool);
		bool update();
		float getattspeed();
		void init(int, skillbook, questlog, map<short, string>);
		void setinventory(inventory ivt) { invent = ivt; }
		void setexpression(char c) { look->setexpression(c); }
		bool getleft() { return fleft; }
		vector2d getposition() { return vector2d(static_cast<int>(floor(fx)), static_cast<int>(floor(fy))); }
		rectangle2d bounds() { return rectangle2d(position, position + vector2d(50, 80)); }
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
		playereffects effects;
		inventory invent;
		skillbook skills;
		questlog quests;
		telerock trock;
		monsterbook book;
		map<short, string> areainfo;
		textlabel name;
		vector<movefragment> moves;
		footholdtree* footholds;
		ladderrope* ladrrope;
		foothold fh;
		bool fleft;
		short elapsed;
		short speed;
		short jump;
		float hspeed;
		float vspeed;
		vector2d position;
		float fx;
		float fy;
		float ground;
		bool nofriction;
		bool candjump;
		playerstate state;
		map<moveinput, bool> keydown;
	};
}

