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
#include "Journey.h"

namespace gameplay
{
	player::player(maplechar* ch)
	{
		look = ch->copylook();
		stats = ch->copystats();

		name = textlabel(DWF_14C, TXC_WHITE, stats.getname(), TXB_NAMETAG);
	}

	void player::init(int meso, skillbook skl, questlog qst, pair<vector<int>, vector<int>> trock, int cov, map<short, char> mb, map<short, string> area)
	{
		stats.setmeso(meso);
		skills = skl;
		quests = qst;
		trockmaps = trock;
		bookcover = cov;
		bookcards = mb;
		areainfo = area;

		recalcstats(true);

		hspeed = 0;
		vspeed = 0;
		state = PST_STAND;
		nofriction = false;
		fleft = true;
		look.setfleft(true);
		candjump = true;

		for (moveinput i = MIN_LEFT; i <= MIN_JUMP; i = static_cast<moveinput>(i + 1))
		{
			keydown[i] = false;
		}
	}

	void player::setposition(vector2d pos)
	{
		pos = pos - vector2d(0, 15);
		fx = static_cast<float>(pos.x());
		fy = static_cast<float>(pos.y());

		hspeed = 0;
		vspeed = 0;

		ground = footholds->getgroundbelow(pos);
		if (ground > fy)
		{
			state = PST_FALL;
		}
		else if (state == PST_CLIMB)
		{
			state = PST_STAND;
		}
	}

	void player::draw(ID2D1HwndRenderTarget* target, vector2d parentpos)
	{
		fx += hspeed;
		fy += vspeed;
		position = getposition();

		if (vspeed > 0)
		{
			if (fy + vspeed >= ground && ground >= fy)
			{
				vspeed = 0;
				fy = ground;
			}
		}

		vector2d absp = parentpos + position;

		look.draw(target, absp);
		name.draw(target, absp);
		effects.draw(target, absp);
	}

	movefragment player::update()
	{
		bool anidone = look.update();
		effects.update();

		float fspeed = WALKSPEED * static_cast<float>(speed) / 100;

		if (state == PST_CLIMB)
		{
			if (keydown[MIN_UP])
			{
				vspeed = -fspeed;
			}
			else if (keydown[MIN_DOWN])
			{
				vspeed = fspeed;
			}
			else
			{
				vspeed = 0;
			}

			float cfriction = 0.01f;

			if (vspeed > 0)
			{
				vspeed -= cfriction;
				vspeed = max(vspeed, 0);
			}
			else if (vspeed < 0)
			{
				vspeed += cfriction;
				vspeed = min(vspeed, 0);
			}

			if (fy + vspeed > ladrrope.vertical.y() || fy + vspeed < ladrrope.vertical.x())
			{
				state = PST_FALL;
			}
		}
		else
		{
			if (state != PST_SKILL && state != PST_PRONE)
			{
				float maxhspeed = (candjump) ? fspeed * 1.5f : fspeed * 4.0f;

				if (keydown[MIN_LEFT])
				{
					hspeed = hspeed - (fspeed / 10);
					hspeed = max(hspeed, -maxhspeed);
				}
				else if (hspeed < 0)
				{
					hspeed += 0.13f;
					hspeed = min(hspeed, 0);
				}

				if (keydown[MIN_RIGHT])
				{
					hspeed = hspeed + (fspeed / 10);
					hspeed = min(hspeed, maxhspeed);
				}
				else if (hspeed > 0)
				{
					hspeed -= 0.13f;
					hspeed = max(hspeed, 0);
				}
			}

			if (hspeed != 0 && !nofriction)
			{
				float friction;

				switch (state)
				{
				case PST_SKILL:
					friction = 0.2f;
					break;
				case PST_PRONE:
				case PST_STAND:
				case PST_CLIMB:
				case PST_WALK:
					friction = 0.08f;
					break;
				case PST_FALL:
					friction = 0.01f;
					break;
				}

				if (hspeed > 0)
				{
					hspeed -= friction;
					hspeed = max(hspeed, 0);
				}
				else if (hspeed < 0)
				{
					hspeed += friction;
					hspeed = min(hspeed, 0);
				}
			}

			if (hspeed != 0 && vspeed == 0)
			{
				ground = footholds->nextground(hspeed < 0, getposition());
				if (abs(ground - fy) <= 7)
				{
					fy = ground;
				}
			}
			else if (vspeed != 0)
			{
				ground = footholds->getgroundbelow(getposition());
			}

			if (ground != fy)
			{
				vspeed = vspeed + GRAVITYACC;
				vspeed = min(vspeed, FALLSPEED);

				if (state != PST_SKILL)
				{
					state = PST_FALL;
				}
			}
		}

		if (state == PST_FALL)
		{
			if (vspeed == 0 && ground == fy)
			{
				candjump = true;

				if (keydown[MIN_LEFT] || keydown[MIN_RIGHT])
				{
					state = PST_WALK;
				}
				else if (keydown[MIN_DOWN])
				{
					state = PST_PRONE;
				}
				else
				{
					state = PST_STAND;
				}
			}
		}

		if (anidone)
		{
			switch (state)
			{
			case PST_SKILL:
				if (keydown[MIN_DOWN])
				{
					state = PST_PRONE;
				}
				else
				{
					state = (vspeed == 0) ? PST_STAND : PST_FALL;
				}

				if (keydown[MIN_LEFT])
				{
					fleft = true;
				}

				if (keydown[MIN_RIGHT])
				{
					fleft = false;
				}
				break;
			}
		}

		look.setfleft(fleft);

		switch (state)
		{
		case PST_STAND:
			if (hspeed == 0)
			{
				look.setstate("stand");
			}
			else
			{
				look.setstate("walk");
			}
			break;
		case PST_WALK:
			look.setstate("walk", static_cast<float>(speed) / 100);
			break;
		case PST_FALL:
			look.setstate("jump");
			break;
		case PST_PRONE:
			look.setstate("prone");
			break;
		case PST_CLIMB:
			look.setstate((ladrrope.ladder) ? "ladder" : "rope", static_cast<float>(abs(vspeed)) / 2);
			break;
		}

		movefragment ret;
		ret.newstate = 0;

		elapsed += DPF;
		if (elapsed > 100)
		{
			switch (state)
			{
			case PST_WALK:
				ret.newstate = 2;
				break;
			case PST_STAND:
				ret.newstate = 4;
				break;
			case PST_FALL:
				ret.newstate = 6;
				break;
			}

			if (ret.newstate > 0)
			{
				ret.command = 0;
				ret.newstate += fleft ? 1 : 0;
				ret.xpps = static_cast<short>(hspeed * 6);
				ret.ypps = static_cast<short>(vspeed * 6);
				ret.xpos = static_cast<short>(fx + hspeed);
				ret.ypos = static_cast<short>(fy + vspeed);
				ret.duration = 100;
				ret.unk = 0;
			}

			elapsed = 0;
		}

		return ret;
	}

	void player::key_left(bool kst)
	{
		if (kst)
		{
			keydown[MIN_RIGHT] = false;

			switch (state)
			{
			case PST_STAND:
				fleft = true;
				state = PST_WALK;
				break;
			case PST_WALK:
				if (!fleft)
				{
					fleft = true;
					hspeed = 0;
				}
				else if (hspeed < 0 && !keydown[MIN_LEFT])
				{
					//hspeed = hspeed - 5;
				}
				break;
			case PST_FALL:
				fleft = true;
				break;
			}
		}
		else
		{
			if (!keydown[MIN_RIGHT] && state == PST_WALK)
			{
				state = PST_STAND;
			}
		}

		keydown[MIN_LEFT] = kst;
	}

	void player::key_right(bool kst)
	{
		if (kst)
		{
			keydown[MIN_LEFT] = false;

			switch (state)
			{
			case PST_STAND:
				fleft = false;
				state = PST_WALK;
				break;
			case PST_WALK:
				if (fleft)
				{
					fleft = false;
					hspeed = 0;
				}
				else if (hspeed > 0 && !keydown[MIN_LEFT])
				{
					//hspeed = hspeed + 5;
				}
				break;
			case PST_FALL:
				fleft = false;
				break;
			}
		}
		else
		{
			if (!keydown[MIN_LEFT] && state == PST_WALK)
			{
				state = PST_STAND;
			}
		}

		keydown[MIN_RIGHT] = kst;
	}

	void player::key_jump(bool kst)
	{
		if (!keydown[MIN_JUMP] && kst)
		{
			switch (state)
			{
			case PST_STAND:
			case PST_WALK:
				if (keydown[MIN_DOWN])
				{
					float gbelow = footholds->getgroundbelow(getposition() + vector2d(0, 20));
					if (gbelow > ground && gbelow - ground < 1000)
					{
						setposition(getposition() + vector2d(0, 20));
					}
					else
					{
						vspeed = -JUMPSPEED * (static_cast<float>(jump) / 100);
					}
				}
				else
				{
					vspeed = -JUMPSPEED * (static_cast<float>(jump) / 100);
				}
				state = PST_FALL;
				break;
			case PST_FALL:
				if (candjump && vspeed < 0)
				{
					hspeed = 5 * (static_cast<float>(speed) / 100) * WALKSPEED;
					hspeed *= (fleft) ? -1 : 1;
					vspeed = -JUMPSPEED * (static_cast<float>(jump) / 100);
					candjump = false;
				}
				break;
			case PST_PRONE:
				if (candjump)
				{
					float gbelow = footholds->getgroundbelow(getposition() + vector2d(0, 20));
					if (gbelow > ground && gbelow - ground < 1000)
					{
						setposition(getposition() + vector2d(0, 20));
					}
					else
					{
						vspeed = -JUMPSPEED * (static_cast<float>(jump) / 100);
					}
					state = PST_FALL;
				}
				break;
			case PST_CLIMB:
				if (keydown[MIN_LEFT] || keydown[MIN_RIGHT])
				{
					fleft = keydown[MIN_LEFT];
					fleft = !keydown[MIN_RIGHT];
					vspeed = -JUMPSPEED * (static_cast<float>(jump) / 200);
					state = PST_FALL;
					ladrrope.vertical = vector2d();
				}
				break;
			}
		}

		keydown[MIN_JUMP] = kst;
	}

	void player::key_down(bool kst)
	{
		if (kst)
		{
			switch (state)
			{
			case PST_STAND:
			case PST_WALK:
				hspeed = 0;
				state = PST_PRONE;
				break;
			case PST_CLIMB:
				break;
			}
		}
		else
		{
			switch (state)
			{
			case PST_PRONE:
				state = PST_STAND;

				if (keydown[MIN_LEFT])
				{
					fleft = true;
				}

				if (keydown[MIN_RIGHT])
				{
					fleft = false;
				}
				break;
			}
		}

		keydown[MIN_DOWN] = kst;
	}

	void player::key_up(bool kst)
	{
		keydown[MIN_UP] = kst;
	}

	bool player::tryattack(attackinfo* info, int skillid, short hpcost, short mpcost)
	{
		bool stateok = state != PST_SKILL && state != PST_CLIMB;
		bool nocd = skills.getcd(skillid) == 0;
		bool hpmpok = stats.getstat(MS_HP) >= hpcost && stats.getstat(MS_MP) >= mpcost;

		bool allow = stateok && nocd && hpmpok;

		if (allow)
		{
			info->mastery = stats.getmastery();
			info->maxdamage = stats.getmaxdamage();
			info->mindamage = stats.getmindamage();
			info->pllevel = stats.getstat(MS_LEVEL);
			info->speed = look.getcloth(EQL_WEAPON)->getwspeed();
			info->direction = fleft ? 1 : 0;
			info->skill = skillid;
			info->critical = stats.getcritical();
			info->accuracy = stats.getaccuracy() + invent.getaccuracy();

			if (skillid == 0)
			{
				if (state == PST_PRONE)
				{
					state = PST_SKILL;
					look.setstate("proneStab", getattspeed());
				}
				else
				{
					state = PST_SKILL;
					look.setstate("attack", getattspeed());
				}
			}
		}

		return allow;
	}

	void player::setaction(string act)
	{
		state = PST_SKILL;
		look.setaction(act, getattspeed());
	}

	float player::getattspeed()
	{ 
		return 1.7f - (static_cast<float>(look.getcloth(EQL_WEAPON)->getwspeed()) / 10); 
	}

	void player::recalcstats(bool equipchange)
	{
		if (equipchange)
		{
			invent.recalcstats();
		}

		speed = 100 + invent.gettotal(ES_SPEED);
		jump = 100 + invent.gettotal(ES_JUMP);

		stats.settotal(MS_STR, stats.getstat(MS_STR) + invent.gettotal(ES_STR));
		stats.settotal(MS_DEX, stats.getstat(MS_DEX) + invent.gettotal(ES_DEX));
		stats.settotal(MS_INT, stats.getstat(MS_INT) + invent.gettotal(ES_INT));
		stats.settotal(MS_LUK, stats.getstat(MS_LUK) + invent.gettotal(ES_LUK));
		stats.settotal(MS_MAXHP, stats.getstat(MS_MAXHP) + invent.gettotal(ES_HP));
		stats.settotal(MS_MAXMP, stats.getstat(MS_MAXMP) + invent.gettotal(ES_MP));

		stats.setattack(invent.gettotal(ES_WATK));

		short primary = stats.getprim(look.getweptype());
		short secondary = stats.getsec(look.getweptype());
		short watk = stats.getattack();
		float wmult = look.getcloth(EQL_WEAPON)->getwmultiplier();
		stats.calcdamage(static_cast<short>(primary * wmult), secondary, watk);
	}

	void player::setlr(ladderrope lr)
	{
		ladrrope = lr;
		hspeed = 0;
		vspeed = min(vspeed, 0);
		fx = static_cast<float>(lr.x);
		state = PST_CLIMB;
	}
}
