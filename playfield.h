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
#include "player.h"
#include "world.h"
#include "account.h"
#include "camera.h"
#include "settings.h"
#include "mapinfo.h"
#include "mapbackgrounds.h"
#include "maplayer.h"
#include "mapobjects.h"
#include "footholdtree.h"
#include "laddersropes.h"
#include "mapchars.h"
#include "mapportals.h"
#include "mapdrops.h"
#include "attackfactory.h"

using namespace action;
using namespace maplemap;

namespace gameplay
{
	struct logininfo
	{
		map<char, world> worlds;
		account mapleacc;
		char worldid;
		char channelid;
	};

	class playfield
	{
	public:
		playfield();
		~playfield() {}
		void init();
		void draw(ID2D1HwndRenderTarget*);
		void update();
		void setplayer(player);
		void setfield(int, char);
		void changechannel(char) {}
		bool moveup(bool);
		void useattack(int);
		void useitem(int);
		vector2d getviewpos() { return cam.getposition(); }
		player* getplayer() { return &playerchar; }
		mapchars* getchars() { return &chars; }
		mapmobs* getmobs() { return &mobs; }
		mapdrops* getdrops() { return &drops; }
		mapobjects* getmapobjects() { return &objects; }
		char getchannel() { return login.channelid; }
		char getworld() { return login.worldid; }
		account* getaccount() { return &login.mapleacc; }
		map<char, world>* getworlds() { return &login.worlds; }
		void setworldchannel(char wld, char chd) { login.worldid = wld; login.channelid = chd; }
	private:
		attackfactory attfactory;
		player playerchar;
		camera cam;
		mapinfo maplemap;
		mapbackgrounds backgrounds;
		map<char, maplayer> layers;
		mapobjects objects;
		mapchars chars;
		mapmobs mobs;
		mapdrops drops;
		footholdtree footholds;
		laddersropes landr;
		mapportals portals;
		logininfo login;
		bool active;
	};
}

