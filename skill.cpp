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
#include "Journey.h"
#include "skill.h"
#include "nxfile.h"

namespace action
{
	skill::skill(int id)
	{
		app.getimgcache()->setmode(ict_sys);
		nl::nx::view_file("Skill");

		string fullname;
		string skillstr = to_string(id);
		size_t extend = 7 - skillstr.length();
		for (char i = 0; i < extend; i++)
		{
			fullname.append("0");
		}
		fullname.append(skillstr);

		nl::node src = nl::nx::nodes["Skill"][fullname.substr(0, 3) + ".img"]["skill"][fullname];

		icon[0] = texture(src["icon"]);
		icon[1] = texture(src["iconDisabled"]);
		icon[2] = texture(src["iconMouseOver"]);

		if (src["effect"]["0"].istype(bitmapnode))
		{
			skill_e.push_back(animation(src["effect"]));
		}
		else
		{
			for (nl::node eff_n = src["effect"].begin(); eff_n != src["effect"].end(); ++eff_n)
			{
				skill_e.push_back(animation(eff_n));
			}
		}

		if (src["hit"]["0"].istype(bitmapnode))
		{
			affected.push_back(animation(src["hit"]));
		}
		else
		{
			for (nl::node eff_n = src["hit"].begin(); eff_n != src["hit"].end(); ++eff_n)
			{
				affected.push_back(animation(eff_n));
			}
		}

		if (src["affected"]["0"].istype(bitmapnode))
		{
			affected.push_back(animation(src["affected"]));
		}
		else
		{
			for (nl::node eff_n = src["affected"].begin(); eff_n != src["affected"].end(); ++eff_n)
			{
				affected.push_back(animation(eff_n));
			}
		}

		prepare = src["prepare"]["action"].get_string();
		prepare_t = src["prepare"]["time"];
		offensive = src["level"]["1"]["damage"].istype(integernode);

		for (nl::node action_n = src["action"].begin(); action_n != src["action"].end(); ++action_n)
		{
			actions.push_back(action_n.get_string());
		}

		for (nl::node level_n = src["level"].begin(); level_n != src["level"].end(); ++level_n)
		{
			int level = stoi(level_n.name());
			skillinfo info;

			if (level_n["prop"].istype(integernode))
			{
				info.chance = static_cast<float>(level_n["prop"]) / 100;
			}
			else
			{
				info.chance = 1.0f;
			}

			if (offensive)
			{
				info.damage = static_cast<float>(level_n["damage"]) / 100;
				info.attacks = level_n["attackCount"].istype(integernode)? static_cast<char>(level_n["attackCount"].get_integer()) : 1;
				info.mobs = level_n["mobCount"].istype(integernode) ? static_cast<char>(level_n["mobCount"].get_integer()) : 1;

				info.hpcost = level_n["hpCon"].istype(integernode) ? static_cast<char>(level_n["hpCon"].get_integer()) : 1;
				info.mpcost = level_n["mpCon"].istype(integernode) ? static_cast<char>(level_n["mpCon"].get_integer()) : 1;

				info.range.first = vector2d(level_n["lt"].x(), level_n["lt"].y());
				info.range.second = vector2d(level_n["rb"].x(), level_n["rb"].y());
			}

			levels[level] = info;
		}
	
		nl::nx::unview_file("Skill");
		app.getimgcache()->unlock();
	}

	void skill::addeffects(playereffects* effects, bool flip)
	{
		for (vector<animation>::iterator efit = skill_e.begin(); efit != skill_e.end(); ++efit)
		{
			effects->add(effect(*efit, vector2d(), flip));
		}
	}

	string skill::getaction(bool twoh)
	{
		if (actions.size() > 0)
		{
			if (actions.size() > 1 && twoh)
			{
				return actions[1];
			}
			return actions[0];
		}
		return "";
	}
}
