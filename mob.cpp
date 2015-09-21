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
#include "mob.h"
#include "Journey.h"
#include "nxfile.h"

namespace gameplay
{
	mob::mob(int id, int o, bool con, vector2d p, char s, short f, char e, bool fd, char t, footholdtree* fht)
	{
		app.getimgcache()->setmode(ict_map);

		string fullname;
		string strid = to_string(id);
		size_t extend = 7 - strid.length();
		for (char i = 0; i < extend; i++)
		{
			fullname.append("0");
		}
		fullname.append(strid);
		node mobdata = nx::nodes["Mob"].resolve(fullname + ".img");

		for (node subnode = mobdata.begin(); subnode != mobdata.end(); ++subnode)
		{
			string state = subnode.name();

			if (state == "info")
			{
				level = subnode["level"];
				watk = subnode["PADamage"];
				matk = subnode["MADamage"];
				wdef = subnode["PDDamage"];
				mdef = subnode["MDDamage"];
				acc = subnode["acc"];
				eva = subnode["eva"];
				knockback = subnode["pushed"];
				speed = subnode["speed"];
				touchdamage = subnode["bodyAttack"].get_bool();
				undead = subnode["undead"].get_bool();
			}
			else
			{
				textures[state] = animation(subnode);
				hitrect[state] = rectangle2d(subnode["0"]["lt"].tov2d(), subnode["0"]["rb"].tov2d());
			}
		}

		node namenode = nx::nodes["String"]["Mob.img"][strid]["name"];
		name = namenode.istype(stringnode) ? namenode.get_string() : "";

		app.getimgcache()->unlock();

		sndpath = "Sound\\Mob.img\\Mob.img\\";
		string idstr = to_string(id);
		if (idstr.size() < 7)
		{
			sndpath.append("0");
		}
		sndpath.append(idstr);

		state = "stand";
		mid = id;
		oid = o;
		control = con;
		stance = s;
		effect = e;
		fadein = fd;
		team = t;
		fx = static_cast<float>(p.x());
		fy = static_cast<float>(p.y());
		footholds = fht;

		fh = fht->getbelow(p);
		hspeed = 0;
		vspeed = 0;
		walls = footholds->getpfedges(fh.getid());

		hppercent = 0;
		moved = 0;
		fleft = stance == 1;
		alpha = (fadein) ? 0.0f : 1.0f;
		speed = speed + 100;
		fade = false;
		dead = false;
	}

	void mob::damage(attackinfo* attack)
	{
		if (!dead)
		{
			vector<pair<int, char>> dmgeffects;
			vector<int> dmgnumbers;
			long totaldamage = 0;

			byte ldelta = (level > attack->pllevel) ? level - attack->pllevel : 0;

			float hitchance = static_cast<float>(attack->accuracy) / ((1.84f + 0.07f * ldelta) * eva) - 1;

			int mindamage = static_cast<int>(attack->skillmult * attack->mindamage * (1 - 0.01f * ldelta) - wdef * 0.5f);
			int maxdamage = static_cast<int>(attack->skillmult * attack->maxdamage * (1 - 0.01f * ldelta) - wdef * 0.5f);

			uniform_int_distribution<int> dmgrange(mindamage, maxdamage);

			for (char i = 0; i < attack->numdamage; i++)
			{
				bool critical = false; //TODO
				pair<int, bool> damage = calcdamage(dmgrange, hitchance, attack->critical);

				dmgnumbers.push_back(damage.first);
				dmgeffects.push_back(damage);

				totaldamage += damage.first;
			}

			if (totaldamage > knockback)
			{
				bool froml = attack->direction == 1;
				hspeed = froml ? -0.15f : 0.15f;
				fleft = !froml;
				moved = 0;
				state = "hit1";
			}

			app.getui()->getbase()->showdamage(dmgeffects, getposition() - vector2d(0, textures[state].getdimension(0).y()));

			attack->mobsdamaged[oid] = dmgnumbers;
		}
	}

	pair<int, bool> mob::calcdamage(uniform_int_distribution<int> dmgrange, float hitchance, float critchance)
	{
		uniform_real_distribution<float> range(0.0f, 1.0f);
		random_device random;

		default_random_engine engine1(random());
		bool hit = range(engine1) < hitchance;
		if (hit)
		{
			default_random_engine engine2(random());
			int damage = dmgrange(engine2);

			default_random_engine engine3(random());
			bool crit = range(engine3) < critchance;
			if (crit)
			{
				damage = static_cast<int>(damage * 1.5f);
			}

			if (damage < 1)
			{
				damage = 1;
			}
			else if (damage > DAMAGECAP)
			{
				damage = DAMAGECAP;
			}

			return make_pair(damage, crit);
		}
		else
		{
			return make_pair(0, false);
		}
	}

	rectangle2d mob::bounds()
	{
		rectangle2d bounds = hitrect[state];
		if (bounds.straight())
		{
			vector2d dim = textures[state].getdimension(0);
			vector2d lt = getposition() - vector2d(dim.y(), dim.x() / 2);
			bounds = rectangle2d(lt, lt + dim);
		}
		else
		{
			bounds.setlt(bounds.getlt() + getposition());
			bounds.setrb(bounds.getrb() + getposition());
		}
		return bounds;
	}

	void mob::kill(char animation)
	{
		switch (animation)
		{
		case 0:
			active = false;
			break;
		case 1:
			state = "die1";
			dead = true;
			break;
		case 2:
			fade = true;
			dead = true;
			break;
		}

		hspeed = 0;
		vspeed = 0;
	}

	void mob::showhp(char percent)
	{
		hppercent = percent;
	}

	void mob::setmove(char movement, bool fl)
	{
		float fspeed = static_cast<float>(speed) / 100;
		fleft = fl;

		switch (movement)
		{
		case 0:
			state = "stand";
			hspeed = 0;
			break;
		case 1:
			state = "move";
			hspeed = (fleft) ? -fspeed : fspeed;
			break;
		}
	}

	bool mob::update()
	{
		if (active)
		{
			bool aniend = textures[state].update();

			bool groundhit = gravityobject::update();

			if (state == "hit1")
			{
				moved += abs(hspeed);

				if (moved > 10)
				{
					hspeed = 0;
					state = "stand";
				}
				else
				{
					hspeed *= 1.25;
				}
			}
			else if (control)
			{
				float fspeed = static_cast<float>(speed) / 100;

				if (state == "stand")
				{
					if (moved < 100)
					{
						moved += 1;
					}
					else if (aniend || !textures[state].isanimated())
					{
						moved = 0;
						state = "move";

						random_device rd;
						uniform_int_distribution<int> udist(0, 1);
						default_random_engine e1(rd());

						fleft = udist(e1) == 1;
						hspeed = (fleft) ? -fspeed : fspeed;
					}
				}
				else
				{
					if (moved < 100)
					{
						moved += 1;
					}
					else if (aniend || !textures[state].isanimated())
					{
						moved = 0;

						random_device rd;
						uniform_int_distribution<int> udist(0, 2);
						default_random_engine e1(rd());
						int result = udist(e1);

						if (result == 2)
						{
							hspeed = 0;
							state = "stand";
						}
						else
						{
							fleft = udist(e1) == 1;
							hspeed = (fleft) ? -fspeed : fspeed;
						}
					}

					if (hspeed != 0)
					{
						int posx = static_cast<int>(fx + hspeed);
						int mobwidth = textures[state].getdimension(0).x() / 2;
						if (posx + mobwidth >= walls.y())
						{
							fleft = true;
							hspeed = -fspeed;
						}
						else if (posx - mobwidth <= walls.x())
						{
							fleft = false;
							hspeed = fspeed;
						}
					}

					if (moved % 10 == 0)
					{
						//sendmoves(10);
					}
				}
			}

			if (fade)
			{
				alpha -= 0.25f;
				if (alpha < 0.25f)
				{
					aniend = true;
				}
			}
			else if (fadein)
			{
				alpha += 0.025f;
				if (alpha > 0.975f)
				{
					alpha = 1.0f;
					fadein = false;
				}
			}

			return dead && aniend;
		}

		return false;
	}

	void mob::sendmoves(byte elapsed)
	{
		vector<movefragment> moves;
		movefragment lastmove;
		lastmove.type = MVT_ABSOLUTE;
		lastmove.command = 1;
		lastmove.newstate = 1;
		lastmove.xpos = static_cast<short>(fx);
		lastmove.ypos = static_cast<short>(fy);
		lastmove.xpps = hspeed * elapsed;
		lastmove.ypps = vspeed * elapsed;
		lastmove.duration = elapsed;
		moves.push_back(lastmove);

		packet_c.movemonster(oid, 1, 0, 0, 0, 0, 0, 0, getposition(), moves);
	}

	void mob::draw(ID2D1HwndRenderTarget* target, vector2d parentpos)
	{
		if (active)
		{
			vector2d pos = getposition();
			absp = pos + parentpos;

			if (!fleft)
			{
				target->SetTransform(
					D2D1::Matrix3x2F::Scale(
					D2D1::Size(-1.0f, 1.0f),
					D2D1::Point2F(
					(float)absp.x(),
					(float)absp.y())));
			}

			textures[state].draw(target, absp, alpha);

			if (!fleft)
			{
				target->SetTransform(
					D2D1::Matrix3x2F::Scale(
					D2D1::Size(1.0f, 1.0f),
					D2D1::Point2F(
					(float)absp.x(),
					(float)absp.y())));
			}

			if (hppercent > 1)
			{
				app.getui()->getbase()->drawmobhp(hppercent, absp - vector2d(30, textures[state].getdimension(0).y() + 25));
			}
		}
	}
}
