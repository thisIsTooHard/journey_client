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
	playfield::playfield()
	{
		active = false;
	}

	void playfield::init()
	{
		portals.init();
	}

	bool playfield::moveup(bool keydown)
	{
		bool enable = true;

		if (keydown)
		{
			pair<int, string> warpinfo = portals.getportal(playerchar.getposition());

			if (warpinfo.first == maplemap.getid())
			{
				vector2d spawnpos = portals.getspawnpoint(warpinfo.second);
				playerchar.setposition(spawnpos);
			}
			else if (warpinfo.first < 999999999)
			{
				packet_c.changemap(false, warpinfo.first, warpinfo.second, false);
				enable = false;
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

		return enable;
	}

	void playfield::useattack(int skillid)
	{
		attackinfo attack;
		attacktype type = ATT_NONE;

		if (skillid > 0)
		{
			skill* touse = attfactory.getskill(skillid);
			char skill_l = playerchar.getskills()->getlevel(skillid);
			if (skill_l > 0)
			{
				skillinfo info = touse->getlevel(skill_l);
				bool allowed = playerchar.tryattack(&attack, skillid, info.hpcost, info.mpcost);

				if (allowed)
				{
					bool left = playerchar.getleft();

					touse->addeffects(playerchar.geteffects(), !left);
					playerchar.setaction(touse->getaction(playerchar.getlook()->getcloth("Weapon")->istwo_h()));

					if (touse->isattack())
					{
						attack.maxattacked = info.mobs;
						attack.numdamage = info.attacks;
						attack.stance = 1;
						attack.charge = 0;
						attack.display = 50;
						attack.skillmult = info.damage;

						vector2d lt = info.range.first;
						vector2d rb = info.range.second;
						vector2d plpos = playerchar.getposition();
						if (left)
						{
							lt = plpos + lt;
							rb = plpos + rb;
						}
						else
						{
							int left = lt.x();
							int right = rb.x();
							lt = vector2d(plpos.x() - right, plpos.y() + lt.y());
							rb = vector2d(plpos.x() - left, plpos.y() + rb.y());
						}

						mobs.sendattack(&attack, rectangle2d(lt, rb));
						packet_c.close_attack(attack);
					}
				}
			}
		}
		else
		{
			bool allowed = playerchar.tryattack(&attack, skillid, 0, 0);

			if (allowed)
			{
				regularattack regtype = static_cast<regularattack>(playerchar.getlook()->getcloth("Weapon")->getattack());

				rectangle2d range = attfactory.getnormalrange(regtype);
				vector2d plpos = playerchar.getposition();
				bool left = playerchar.getleft();
				if (left)
				{
					range.shift(plpos);
				}
				else
				{
					vector2d lt = range.getlt();
					vector2d rb = range.getrb();
					range.setlt(vector2d(plpos.x() - rb.x(), plpos.y() + lt.y()));
					range.setrb(vector2d(plpos.x() - lt.x(), plpos.y() + rb.y()));
				}

				attack.maxattacked = 1;
				attack.display = 50;
				attack.charge = 0;
				attack.numdamage = 1;
				attack.skillmult = 1.0f;

				mobs.sendattack(&attack, range);

				switch (regtype)
				{
				case RGA_1HWEP:
				case RGA_2HWEP:
				case RGA_SPEAR_PA:
				case RGA_KNUCKLE:
					type = ATT_CLOSE;
					break;
				case RGA_BOW:
				case RGA_XBOW:
				case RGA_CLAW:
				case RGA_GUN:
					type = ATT_RANGED;
					break;
				}
			}
		}

		switch (type)
		{
		case ATT_CLOSE:
			packet_c.close_attack(attack);
			break;
		}
	}

	void playfield::useitem(int itemid)
	{
		inventorytype type = playerchar.getinventory()->gettypebyid(itemid);
		short slot = playerchar.getinventory()->finditem(itemid);

		if (slot >= 0)
		{
			if (type == IVT_USE)
			{
				packet_c.useitem(slot, itemid);
			}
		}
	}

	void playfield::draw(ID2D1HwndRenderTarget* target)
	{
		if (active)
		{
			cam.update(playerchar.getposition());

			vector2d viewpos = cam.getposition();
			backgrounds.drawbackgrounds(target, viewpos);
			layers[0].draw(target, viewpos);
			layers[1].draw(target, viewpos);
			layers[2].draw(target, viewpos);
			layers[3].draw(target, viewpos);
			layers[4].draw(target, viewpos);
			layers[5].draw(target, viewpos);
			layers[6].draw(target, viewpos);
			layers[7].draw(target, viewpos);
			mobs.draw(target, viewpos);
			objects.draw(target, viewpos);
			chars.draw(target, viewpos);
			playerchar.draw(target, viewpos);
			drops.draw(target, viewpos);
			portals.draw(target, viewpos);
			backgrounds.drawforegrounds(target, viewpos);
		}
	}

	void playfield::update()
	{
		if (active)
		{
			backgrounds.update();
			objects.update();
			mobs.update();
			drops.update();
			chars.update();

			movefragment movement = playerchar.update();
			if (movement.newstate > 0)
			{
				packet_c.moveplayer(movement);
			}

			portals.update(playerchar.getposition());

			for (int i = 0; i < 8; i++)
			{
				layers[i].update();
			}
		}
	}

	void playfield::setplayer(player plchar)
	{
		playerchar = plchar;
	}

	void playfield::setfield(int mapid, char pid)
	{
		active = false;

		objects.clear();
		mobs.clear();
		drops.clear();
		portals.clear();
		chars.clear();

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
		maplemap = mapinfo(mapid, mapdata["info"], vector2d(footholds.getwalls()), vector2d(footholds.getborders()));
		landr = laddersropes(mapdata["ladderRope"]);

		nl::node portalnodes = mapdata["portal"];
		for (nl::node portalnd = portalnodes.begin(); portalnd != portalnodes.end(); portalnd++)
		{
			char pid = static_cast<char>(stoi(portalnd.name()));

			portaltype ptype = static_cast<portaltype>(portalnd.resolve("pt").get_integer());
			string pname = portalnd.resolve("pn").get_string();
			int targetid = static_cast<int>(portalnd.resolve("tm").get_integer());
			string targetpname = portalnd.resolve("tn").get_string();
			vector2d ppos = vector2d(static_cast<int>(portalnd.resolve("x").get_integer()), static_cast<int>(portalnd.resolve("y").get_integer()));

			portals.addportal(pid, ptype, pname, targetid, mapid == targetid, targetpname, ppos);
		}

		backgrounds = mapbackgrounds(mapdata.resolve("back"), maplemap.getwalls(), maplemap.getborders());

		for (int i = 0; i < 8; i++)
		{
			layers[i] = maplayer(mapdata.resolve(to_string(i)));
		}

		nl::nx::unview_file("Map");
		app.getimgcache()->unlock();

		vector2d startpos = portals.getspawnpoint(pid);

		playerchar.setfh(&footholds);
		playerchar.setposition(startpos);

		cam.setposition(startpos);
		cam.setbounds(maplemap.getwalls(), maplemap.getborders());

		mobs.setfh(&footholds);
		drops.setfh(&footholds);

		active = true;
	}
}
