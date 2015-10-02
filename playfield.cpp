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
	void playfield::init()
	{
		drops.init();
		portals.init();

		audio loginbgm = nx::nodes["Sound"]["BgmUI.img"]["Title"].get_audio();
		app.getaudio()->playbgm((void*)loginbgm.data(), loginbgm.length());
	}

	bool playfield::moveup(bool keydown)
	{
		bool enable = true;

		if (keydown)
		{
			pair<int, string> warpinfo = portals.getportal(playerchar.bounds());

			if (warpinfo.first == cache.getmap()->getid())
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

		playerchar.key_up(keydown);

		return enable;
	}

	void playfield::useattack(int skillid)
	{
		attackinfo attack;
		attacktype type = ATT_NONE;

		if (skillid > 0)
		{
			skilldata* touse = cache.getskills()->getskill(skillid);
			char skill_l = playerchar.getskills()->getlevel(skillid);
			if (skill_l > 0)
			{
				skillinfo info = touse->getlevel(skill_l);
				bool allowed = playerchar.tryattack(&attack, skillid, info.hpcost, info.mpcost);

				if (allowed)
				{
					bool left = playerchar.getleft();
					bool twoh = playerchar.getlook()->getcloth(EQL_WEAPON)->istwo_h();

					touse->playsound("Use");
					touse->addeffects(playerchar.geteffects(), !left, 16.0f / playerchar.getattspeed(), twoh);
					playerchar.setaction(touse->getaction(twoh));

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
				clothing* weapon = playerchar.getlook()->getcloth(EQL_WEAPON);

				rectangle2d range = weapon->getrange();
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

				cache.getsounds()->play(weapon->getsfx());

				mobs.sendattack(&attack, range);

				switch (weapon->getweptype())
				{
				case WEP_1H_SWORD:
				case WEP_1H_AXE:
				case WEP_1H_MACE:
				case WEP_SPEAR:
				case WEP_POLEARM:
				case WEP_DAGGER:
				case WEP_KNUCKLE:
					type = ATT_CLOSE;
					break;
				case WEP_BOW:
				case WEP_CROSSBOW:
				case WEP_CLAW:
				case WEP_GUN:
					type = ATT_RANGED;
					break;
				case WEP_WAND:
				case WEP_STAFF:
					type = ATT_MAGIC;
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
		short slot = playerchar.getinventory()->finditem(type, itemid);
		if (slot >= 0)
		{
			if (type == IVT_USE)
			{
				packet_c.useitem(slot, itemid);
			}
		}
	}

	void playfield::pickup()
	{
		drop* drp = drops.trypickup(playerchar.bounds());
		if (drp)
		{
			packet_c.pickupitem(drp->getid(), drp->getposition());
		}
	}

	void playfield::showchareffect(char effid)
	{
		playerchar.geteffects()->add(cache.geteffects()->geteffect(effid));
		if (effid == 0)
		{
			cache.getsounds()->play(MSN_LEVELUP);
		}
	}

	void playfield::showchareffect(int cid, char effid)
	{
		vplayer* vpl = chars.getchar(cid);
		if (vpl)
		{
			vpl->geteffects()->add(cache.geteffects()->geteffect(effid));
			if (effid == 0)
			{
				cache.getsounds()->play(MSN_LEVELUP);
			}
		}
	}

	vplayer* playfield::getchar(int cid)
	{
		if (cid == playerchar.getid())
		{
			return &playerchar;
		}
		else
		{
			return chars.getchar(cid);
		}
	}

	void playfield::draw()
	{
		if (active)
		{
			vector2d viewpos = cam.getposition();
			backgrounds.drawbackgrounds(viewpos);
			layers[0].draw(viewpos);
			layers[1].draw(viewpos);
			layers[2].draw(viewpos);
			layers[3].draw(viewpos);
			layers[4].draw(viewpos);
			layers[5].draw(viewpos);
			layers[6].draw(viewpos);
			layers[7].draw(viewpos);
			npcs.draw(viewpos);
			mobs.draw(viewpos);
			chars.draw(viewpos);
			playerchar.draw(viewpos);
			drops.draw(viewpos);
			portals.draw(viewpos);
			backgrounds.drawforegrounds(viewpos);
		}
	}

	void playfield::update()
	{
		if (active)
		{
			backgrounds.update();
			npcs.update();
			mobs.update();
			drops.update();
			chars.update();
			playerchar.update();
			portals.update(playerchar.bounds());
			cam.update(playerchar.getposition());

			for (int i = 0; i < 8; i++)
			{
				layers[i].update();
			}
		}
	}

	void playfield::buildplayer()
	{
		playerchar = player(login.getacc()->getplayer());
	}

	void playfield::clear()
	{
		active = false;

		npcs.clear();
		mobs.clear();
		drops.clear();
		portals.clear();
		chars.clear();

		cache.getmobs()->clear();
	}

	void playfield::setfield(int mapid, char pid)
	{
		mapdata* mdata = cache.getmap();

		mdata->load(mapid);

		if (mdata->hasnewbgm())
		{
			audio toplay = nx::nodes["Sound"].resolve(mdata->getinfo()->getbgm()).get_audio();
			if (toplay.data())
			{
				app.getaudio()->playbgm((void*)toplay.data(), toplay.length());
			}
		}

		app.getimgcache()->setmode(ict_map);

		string strid = to_string(mapid);
		strid.insert(0, 9 - strid.length(), '0');
		node src = nx::nodes["Map"]["Map"]["Map" + to_string(mapid / 100000000)][strid + ".img"];

		backgrounds = mapbackgrounds(src["back"]);

		portals.load(src["portal"], mapid);

		for (int i = 0; i < 8; i++)
		{
			layers[i] = maplayer(src[to_string(i)]);
		}

		app.getimgcache()->unlock();

		vector2d startpos = portals.getspawnpoint(pid);

		playerchar.updatefht();
		playerchar.setposition(startpos);

		cam.setposition(startpos);
		cam.updateview();

		active = true;
		app.fadein();
	}
}
