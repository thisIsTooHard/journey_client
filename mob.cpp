/////////////////////////////////////////////////////////////////////////////
// This file is part of the Journey MMORPG client                           //
// Copyright � 2015 SYJourney                                               //
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

namespace gameplay
{
	mob::mob(int id, int o, bool con, vector2d p, char s, short f, char e, bool fd, char t)
	{
		mid = id;
		oid = o;
		control = con;
		stance = s;
		effect = e;
		fadein = fd;
		team = t;

		mdata = cache.getmobs()->getmob(mid);

		elapsed = 0;
		frame = 0;
		alpha = (fadein) ? 0.0f : 1.0f;
		alphastep = 0.0f;
		fx = static_cast<float>(p.x());
		fy = static_cast<float>(p.y());

		updatefht();

		hspeed = 0;
		vspeed = 0;
		walls = footholds->getpfedges(fh.getid());

		hppercent = 0;
		moved = 0;
		fleft = stance == 1;
		speed = mdata->getspeed() + 100;
		fade = false;
		dead = false;

		state = "move";
		nextmove();
	}

	void mob::damage(attackinfo* attack)
	{
		if (!dead)
		{
			vector<pair<int, char>> dmgeffects;
			vector<int> dmgnumbers;
			long totaldamage = 0;

			short ldelta = mdata->getldelta(attack->pllevel);
			float hitchance = static_cast<float>(attack->accuracy) / ((1.84f + 0.07f * ldelta) * mdata->geteva()) - 1;

			int mindamage = static_cast<int>(attack->skillmult * attack->mindamage * (1 - 0.01f * ldelta) - mdata->getwdef() * 0.5f);
			int maxdamage = static_cast<int>(attack->skillmult * attack->maxdamage * (1 - 0.01f * ldelta) - mdata->getwdef() * 0.6f);

			for (char i = 0; i < attack->numdamage; i++)
			{
				pair<int, bool> damage = calcdamage(mindamage, maxdamage, hitchance, attack->critical);

				dmgnumbers.push_back(damage.first);
				dmgeffects.push_back(damage);

				totaldamage += damage.first;
			}

			if (totaldamage > mdata->getkb())
			{
				bool froml = attack->direction == 1;
				hspeed = froml ? -0.15f : 0.15f;
				fleft = !froml;
				moved = 0;
				mdata->playsound("Damage");
				setstate("hit1");
			}

			app.getui()->getbase()->showdamage(dmgeffects, getposition() + vector2d(0, mdata->bounds(state).getlt().y()));

			attack->mobsdamaged[oid] = dmgnumbers;
		}
	}

	pair<int, bool> mob::calcdamage(int mindmg, int maxdmg, float hitchance, float critchance)
	{
		if (random.below(hitchance))
		{
			int damage = random.nextint<int>(mindmg, maxdmg);

			bool crit = random.below(critchance);
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
		rectangle2d bounds = mdata->bounds(state);
		bounds.setlt(bounds.getlt() + getposition());
		bounds.setrb(bounds.getrb() + getposition());
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
			mdata->playsound("Die");
			setstate("die1");
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
			setstate("stand");
			hspeed = 0;
			break;
		case 1:
			setstate("move");
			hspeed = (fleft) ? -fspeed : fspeed;
			break;
		}
	}

	bool mob::update()
	{
		if (active)
		{
			animation* ani = mdata->getani(state);

			if (ani)
			{
				bool aniend = graphicobject::update(ani);

				bool groundhit = gravityobject::update();

				if (state == "hit1")
				{
					moved += abs(hspeed);

					if (moved > 10)
					{
						hspeed = 0;
						setstate("stand");
					}
					else
					{
						hspeed *= 1.25;
					}
				}
				else if (control)
				{
					if (state != "stand")
					{
						if (hspeed != 0)
						{
							float fspeed = static_cast<float>(speed) / 100;
							int posx = static_cast<int>(fx + hspeed);
							int mobwidth = mdata->getani(state)->getdimension(frame).x() / 2;
							if (posx + mobwidth + hspeed >= walls.y())
							{
								fleft = true;
								hspeed = -fspeed;
							}
							else if (posx - mobwidth - hspeed <= walls.x())
							{
								fleft = false;
								hspeed = fspeed;
							}
						}

						if (moved % 100 == 0)
						{
							sendmoves(moved == 0);
						}
					}

					if (moved < 100)
					{
						moved += 1;
					}
					else if (aniend || !(ani->isanimated()))
					{
						nextmove();
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
		}

		return false;
	}

	void mob::nextmove()
	{
		moved = 0;

		if (state == "move" && random.nextbool())
		{
			hspeed = 0;

			setstate("stand");
		}
		else
		{
			float fspeed = static_cast<float>(speed) / 100;

			fleft = random.nextbool();
			hspeed = (fleft) ? -fspeed : fspeed;

			setstate("move");
		}
	}

	void mob::sendmoves(bool first)
	{
		if (first)
		{
			movefragment firstmove;
			firstmove.type = MVT_ABSOLUTE;
			firstmove.command = 0;
			firstmove.newstate = 1;
			firstmove.xpps = 0;
			firstmove.ypps = 0;
			firstmove.xpos = static_cast<short>(fx);
			firstmove.ypos = static_cast<short>(fy);
			firstmove.unk = 0;
			firstmove.duration = 50;

			moves.push_back(firstmove);
		}
		else
		{
			movefragment lastmove;
			lastmove.type = MVT_ABSOLUTE;
			lastmove.command = 0;
			lastmove.newstate = 1;
			lastmove.xpps = static_cast<short>(hspeed * 3);
			lastmove.ypps = static_cast<short>(vspeed * 3);
			lastmove.xpos = static_cast<short>(fx);
			lastmove.ypos = static_cast<short>(fy);
			lastmove.unk = 0;
			lastmove.duration = 50;

			moves.push_back(lastmove);
			packet_c.movemonster(oid, 1, 0, 0, 0, 0, 0, 0, getposition(), moves);

			moves.clear();
		}
	}

	void mob::setstate(string st)
	{
		state = st;
		resetani();
	}

	void mob::draw(vector2d parentpos)
	{
		if (active)
		{
			mdata->draw(state, frame, alpha, !fleft, getposition() + parentpos);
		}
	}
}
