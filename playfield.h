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
#include "footholdtree.h"
#include "laddersropes.h"
#include "mapchars.h"
#include "mapportals.h"
#include "mapmobs.h"
#include "mapnpcs.h"
#include "mapdrops.h"

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

		void addworld(char c, world w) { worlds[c] = w; }
		world* getworld(char c) { return &worlds[c]; }
		account* getacc() { return &mapleacc; }
	};

	class playfield
	{
	public:
		playfield();
		~playfield() {}
		void init();
		void draw();
		void update();
		void setfield(int, char);
		void changechannel(char) {}
		bool moveup(bool);
		void useattack(int);
		void useitem(int);
		void buildplayer();
		vector2d getviewpos() { return cam.getposition(); }
		player* getplayer() { return &playerchar; }
		mapchars* getchars() { return &chars; }
		mapmobs* getmobs() { return &mobs; }
		mapdrops* getdrops() { return &drops; }
		mapnpcs* getnpcs() { return &npcs; }
		logininfo* getlogin() { return &login; }
	private:
		map<char, maplayer> layers;
		mapbackgrounds backgrounds;
		player playerchar;
		mapchars chars;
		mapmobs mobs;
		mapnpcs npcs;
		mapdrops drops;
		mapportals portals;
		camera cam;
		logininfo login;
		bool active;
	};
}

