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
#include "soundcache.h"
#include "Journey.h"

namespace data
{
	void soundcache::init()
	{
		node src = nx::nodes["Sound"];
		node uisrc = src["UI.img"];
		node gamesrc = src["Game.img"];

		sounds[MSN_MSCLICK] = cache(uisrc["BtMouseClick"]);
		sounds[MSN_MSOVER] = cache(uisrc["BtMouseOver"]);
		sounds[MSN_MSGRAB] = cache(uisrc["DragStart"]);
		sounds[MSN_MSENDGRAB] = cache(uisrc["DragEnd"]);

		sounds[MSN_CHARSEL] = cache(uisrc["CharSelect"]);

		sounds[MSN_GAMEIN] = cache(gamesrc["GameIn"]);
		sounds[MSN_JUMP] = cache(gamesrc["Jump"]);
		sounds[MSN_DROP] = cache(gamesrc["DropItem"]);
		sounds[MSN_PICKUP] = cache(gamesrc["PickUpItem"]);
		sounds[MSN_PORTAL] = cache(gamesrc["Portal"]);
		sounds[MSN_LEVELUP] = cache(gamesrc["LevelUp"]);
	}

	void soundcache::play(maplesound snd)
	{
		size_t id = sounds[snd];
		app.getaudio()->playsound(id);
	}

	size_t soundcache::cache(node n)
	{
		audio snd = n.get_audio();
		app.getaudio()->cachesound((void*)snd.data(), snd.length(), snd.id());
		return snd.id();
	}
}
