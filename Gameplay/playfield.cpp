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
#include "playfield.h"
#include "Journey.h"

namespace gameplay
{
	bool playfield::moveup(bool keydown)
	{
		if (keydown)
		{
			pair<int, string> warpinfo = portals.getportal(playerchar.getposition());

			if (warpinfo.first == map_info.getid())
			{
				vector2d spawnpos = portals.getspawnpoint(warpinfo.second);
				playerchar.setposition(spawnpos);
			}
			else if (warpinfo.second.size() > 0)
			{
				packet_c.changemap(false, warpinfo.first, warpinfo.second, false);
				return false;
			}
		}

		if (playerchar.onladderrope())
		{
			playerchar.key_up(keydown);
		}
		else if (keydown)
		{
			ladderrope lr = landr.getlr(playerchar.getposition());
			if (lr.vertical.contains(playerchar.getposition().y()))
			{
				playerchar.setlr(lr);
			}
		}

		return true;
	}

	void playfield::useattack(int skillid)
	{
		if (playerchar.attack(skillid))
		{
			if (skillid == 0)
			{
				bool left = playerchar.getleft();

				pair<vector2d, vector2d> attackrange;
				if (left)
				{
					attackrange.first = playerchar.getposition() - vector2d(100, 0);
					attackrange.second = vector2d(50, 50);
				}
				else
				{
					attackrange.first = playerchar.getposition() + vector2d(25, 0);
					attackrange.second = vector2d(50, 50);
				}

				attackinfo attack;
				attack.mastery = playerchar.getstats()->getmastery();
				attack.skill = 0;
				attack.maxattacked = 1;
				attack.display = 50;
				attack.charge = 0;
				attack.speed = 2; //todo: wep speed of char
				attack.direction = (left) ? 1 : 0;
				attack.numdamage = 1;
				attack.stance = 1; //maybe body animation?

				map_objects.getmobs()->sendattack(&attack, playerchar.getstats()->getdamage(), attackrange);
				packet_c.close_attack(attack);
			}
			else
			{
				if (!skillcache.count(skillid))
				{
					skillcache[skillid] = skill(skillid);
				}

				char skill_l = playerchar.getskills()->getlevel(skillid);
				bool left = playerchar.getleft();

				if (skill_l > 0)
				{
					skillinfo skill_i = skillcache[skillid].getlevel(skill_l);

					skillcache[skillid].addeffects(playerchar.geteffects(), !left);
					playerchar.setactions(skillcache[skillid].getactions());

					if (skillcache[skillid].isattack())
					{
						attackinfo attack;
						attack.mastery = playerchar.getstats()->getmastery();
						attack.skill = skillid;
						attack.maxattacked = skill_i.mobs;
						attack.numdamage = skill_i.attacks;
						attack.direction = (left) ? 1 : 0;
						attack.stance = 1;
						attack.speed = 2;
						attack.charge = 0;
						attack.display = 50;

						pair<vector2d, vector2d> attackrange = skill_i.range;
						if (left)
						{
							attackrange.first = playerchar.getposition() + attackrange.first;
							attackrange.second = playerchar.getposition() + attackrange.second;
						}
						else
						{
							attackrange.first = playerchar.getposition() - attackrange.first;
							attackrange.second = playerchar.getposition() - attackrange.second;
						}

						int damage = static_cast<int>(static_cast<float>(playerchar.getstats()->getdamage() * skill_i.damage) / 100);

						map_objects.getmobs()->sendattack(&attack, damage, attackrange);
						packet_c.close_attack(attack);
					}
				}
			}
		}
	}

	void playfield::draw(ID2D1HwndRenderTarget* target)
	{
		if (step == GST_GAME)
		{
			view.update(playerchar.getposition());

			backgrounds.drawbackgrounds(target, view.getposition());
			maplayers[0].draw(target, view.getposition());
			maplayers[1].draw(target, view.getposition());
			maplayers[2].draw(target, view.getposition());
			maplayers[3].draw(target, view.getposition());
			maplayers[4].draw(target, view.getposition());
			maplayers[5].draw(target, view.getposition());
			maplayers[6].draw(target, view.getposition());
			maplayers[7].draw(target, view.getposition());
			map_objects.draw(target, view.getposition());
			playerchar.draw(target, view.getposition());
			portals.draw(target, view.getposition());
			backgrounds.drawforegrounds(target, view.getposition());
		}
	}

	void playfield::update()
	{
		if (step == GST_GAME)
		{
			backgrounds.update();
			map_objects.update();

			movep_info plmove = playerchar.update();
			if (plmove.xpps != 0 || plmove.ypps != 0 || plmove.command != 0)
			{
				packet_c.moveplayer(plmove);
			}

			portals.update(playerchar.getposition());

			for (int i = 0; i < 8; i++)
			{
				maplayers[i].update();
			}
		}
	}

	void playfield::setplayer(player plchar)
	{
		step = GST_TRANSITION;

		m_account.clear();
		playerchar = plchar;
	}

	void playfield::setfield(int mapid, char pid)
	{
		step = GST_TRANSITION;

		map_objects.clear();
		portals.clear();

		string oldbgm = map_info.getbgm();

		app.getimgcache()->setmode(ict_map);
		nl::nx::view_file("Map");

		string fullname;
		string strid = to_string(mapid);
		size_t extend = 9 - strid.length();
		for (char i = 0; i < extend; i++)
		{
			fullname.append("0");
		}

		node mapdata = nl::nx::nodes["Map"].resolve("Map/Map" + to_string(mapid / 100000000) + "/" + fullname.append(strid) + ".img");

		footholds = footholdtree(mapdata["foothold"]);
		map_info = mapinfo(mapid, mapdata["info"], vector2d(footholds.getwalls()), vector2d(footholds.getborders()));
		landr = laddersropes(mapdata["ladderRope"]);

		nl::node portalnodes = mapdata["portal"];
		for (nl::node portalnd = portalnodes.begin(); portalnd != portalnodes.end(); portalnd++)
		{
			char pid = static_cast<char>(stoi(portalnd.name()));

			portaltype ptype = static_cast<portaltype>(portalnd.resolve("pt").get_integer());
			string pname = portalnd.resolve("pn").get_string();
			vector2d ppos = vector2d(static_cast<int>(portalnd.resolve("x").get_integer()), static_cast<int>(portalnd.resolve("y").get_integer()));
			int targetid = static_cast<int>(portalnd.resolve("tm").get_integer());
			string targetpname = portalnd.resolve("tn").get_string();

			animation anim;

			nl::node pnode = nl::nx::nodes["Map"].resolve("MapHelper.img/portal/game");
			switch (ptype)
			{
			case PT_REGULAR:
				anim = animation(pnode.resolve("pv"));
				break;
			case PT_HIDDEN:
			case PT_SCRIPTED_HIDDEN:
				anim = animation(pnode.resolve("ph/default/portalContinue"));
				break;
			}

			portals.addportal(pid, portal(ptype, pname, targetid, targetid == mapid, targetpname, anim, ppos));
		}

		nl::nx::view_file("Back");

		backgrounds = mapbackgrounds(mapdata.resolve("back"), map_info.getwalls(), map_info.getborders());

		nl::nx::unview_file("Back");

		nl::nx::view_file("Tile");
		nl::nx::view_file("Obj");

		for (int i = 0; i < 8; i++)
		{
			maplayers[i] = maplayer(mapdata.resolve(to_string(i)));
		}

		nl::nx::unview_file("Tile");
		nl::nx::unview_file("Obj");
		nl::nx::unview_file("Map");
		app.getimgcache()->unlock();

		vector2d startpos = portals.getspawnpoint(pid);
		playerchar.setfh(&footholds);
		playerchar.setposition(startpos);
		view.setposition(startpos);
		view.setbounds(map_info.getwalls(), map_info.getborders());

		string path = map_info.getbgm();

		if (path != oldbgm)
		{
			bgm.Cleanup();

			wstring stemp = wstring(path.begin(), path.end());
			bgm.Load(stemp.c_str());
			bgm.SetVolume((100 * config.getbgmvolume()) - 10000);
			bgm.Play();
		}

		step = GST_GAME;
	}

	void playfield::playbgm(string path)
	{
		bgm.Cleanup();

		wstring stemp = wstring(path.begin(), path.end());
		bgm.Load(stemp.c_str());
		bgm.SetVolume((100 * config.getbgmvolume()) - 10000);
		bgm.Play();
	}

	void playfield::playsound(string path)
	{
		sounds.push_back(Mp3());

		wstring stemp = wstring(path.begin(), path.end());
		if (sounds.back().Load(stemp.c_str()))
		{
			sounds.back().SetVolume((100 * config.getsfxvolume()) - 10000);
			sounds.back().Play();
		}
	}
}
