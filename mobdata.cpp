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
#include "mobdata.h"
#include "Journey.h"

namespace data
{
	mobdata::mobdata(int mid)
	{
		string path = to_string(mid);
		path.insert(0, 7 - path.size(), '0');

		node src = nx::nodes["Mob"][path + ".img"];

		for (node sub = src.begin(); sub != src.end(); ++sub)
		{
			string state = sub.name();

			if (state == "info")
			{
				level = sub["level"];
				watk = sub["PADamage"];
				matk = sub["MADamage"];
				wdef = sub["PDDamage"];
				mdef = sub["MDDamage"];
				accuracy = sub["acc"];
				avoid = sub["eva"];
				knockback = sub["pushed"];
				speed = sub["speed"];
				touchdamage = sub["bodyAttack"].get_bool();
				undead = sub["undead"].get_bool();
			}
			else
			{
				textures[state] = animation(sub);
				rect[state] = rectangle2d(sub["0"]["lt"].tov2d(), sub["0"]["rb"].tov2d());
			}
		}

		node strsrc = nx::nodes["String"]["Mob.img"][to_string(mid)]["name"];
		name = strsrc.istype(stringnode) ? strsrc.get_string() : "";

		node sndsrc = nx::nodes["Sound"]["Mob.img"][path];
		for (node sub = sndsrc.begin(); sub != sndsrc.end(); ++sub)
		{
			if (sub.data_type() == node::type::audio)
			{
				audio snd = sub.get_audio();
				app.getaudio()->cachesound((void*)snd.data(), snd.length(), snd.id());
				sounds[sub.name()] = snd.id();
			}
		}
	}

	void mobdata::draw(string state, byte frame, float alpha, bool flip, vector2d pos)
	{
		texture* txt = textures[state].gettexture(frame);
		if (txt)
		{
			txt->draw(pos, alpha, flip);
		}
	}

	void mobdata::playsound(string state)
	{
		app.getaudio()->playsound(sounds[state]);
	}

	short mobdata::getldelta(short plvl)
	{
		short ldelta = level - plvl;
		if (ldelta < 0)
		{
			ldelta = 0;
		}
		return ldelta;
	}
}
