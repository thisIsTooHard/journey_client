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

		sounds[MSN_MSCLICK] = cache(uisrc["BtMouseClick"]);
		sounds[MSN_MSOVER] = cache(uisrc["BtMouseOver"]);
		sounds[MSN_MSGRAB] = cache(uisrc["DragStart"]);
		sounds[MSN_MSENDGRAB] = cache(uisrc["DragEnd"]);
		sounds[MSN_CHARSEL] = cache(uisrc["CharSelect"]);

		node gamesrc = src["Game.img"];

		sounds[MSN_GAMEIN] = cache(gamesrc["GameIn"]);
		sounds[MSN_JUMP] = cache(gamesrc["Jump"]);
		sounds[MSN_DROP] = cache(gamesrc["DropItem"]);
		sounds[MSN_PICKUP] = cache(gamesrc["PickUpItem"]);
		sounds[MSN_PORTAL] = cache(gamesrc["Portal"]);
		sounds[MSN_LEVELUP] = cache(gamesrc["LevelUp"]);

		node wepsrc = src["Weapon.img"];

		sounds[MSN_WEP_HANDS] = cache(wepsrc["barehands"]["Attack"]);
		sounds[MSN_WEP_BOW] = cache(wepsrc["bow"]["Attack2"]);
		sounds[MSN_WEP_XBOW] = cache(wepsrc["cBow"]["Attack2"]);
		sounds[MSN_WEP_GUN] = cache(wepsrc["gun"]["Attack2"]);
		sounds[MSN_WEP_KNUCKLE] = cache(wepsrc["knuckle"]["Attack"]);
		sounds[MSN_WEP_MACE] = cache(wepsrc["mace"]["Attack"]);
		sounds[MSN_WEP_POLEARM] = cache(wepsrc["poleArm"]["Attack"]);
		sounds[MSN_WEP_SPEAR] = cache(wepsrc["spear"]["Attack"]);
		sounds[MSN_WEP_SWORDL] = cache(wepsrc["swordL"]["Attack"]);
		sounds[MSN_WEP_SWORDS] = cache(wepsrc["swordS"]["Attack"]);
		sounds[MSN_WEP_TGLOVE] = cache(wepsrc["tGlove"]["Attack2"]);
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
