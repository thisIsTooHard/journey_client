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

using namespace std;
using namespace character;

namespace gameplay
{
	const float FALLSPEED = 7.7f;
	const float GRAVITYACC = 0.5f;
	const float JUMPSPEED = 8.5f;
	const float WALKSPEED = 2.0f;

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
		PST_STAND,
		PST_WALK,
		PST_FALL,
		PST_PRONE,
		PST_DASH,
		PST_SKILL,
		PST_CLIMB
	};

	class player
	{
	public:
		player() {}
		~player() {}
		player(maplechar*);
		void setposition(vector2d);
		void setlr(ladderrope);
		void sit(bool);
		void key_jump(bool);
		void key_left(bool);
		void key_right(bool);
		void key_down(bool);
		void key_up(bool);
		bool tryattack(attackinfo*, int, short, short);
		void draw(ID2D1HwndRenderTarget*, vector2d);
		movefragment update();
		void setaction(string);
		void recalcstats(bool);
		void init(int, skillbook, questlog, pair<vector<int>, vector<int>>, int, map<short, char>, map<short, string>);
		void setinventory(inventory ivt) { invent = ivt; }
		void setfh(footholdtree* f) { footholds = f; }
		void setexpression(char c) { look.setexpression(c); }
		bool getleft() { return fleft; }
		bool onladderrope() { return state == PST_CLIMB; }
		vector2d getposition() { return vector2d(static_cast<int>(floor(fx)), static_cast<int>(floor(fy))); }
		rectangle2d bounds() { return rectangle2d(position, position + vector2d(50, 80)); }
		maplestats* getstats() { return &stats; }
		maplelook* getlook() { return &look; }
		playereffects* geteffects() { return &effects; }
		inventory* getinventory() { return &invent; }
		skillbook* getskills() { return &skills; }
	private:
		float getattspeed();
		maplestats stats;
		maplelook look;
		textlabel name;
		inventory invent;
		skillbook skills;
		playereffects effects;
		questlog quests;
		pair<vector<int>, vector<int>> trockmaps;
		int bookcover;
		map<short, char> bookcards;
		map<short, string> areainfo;
		ladderrope ladrrope;
		footholdtree* footholds;
		foothold fh;
		short elapsed;
		short speed;
		short jump;
		float hspeed;
		float vspeed;
		vector2d position;
		float fx;
		float fy;
		float ground;
		bool fleft;
		bool nofriction;
		bool candjump;
		playerstate state;
		map<moveinput, bool> keydown;
	};
}

