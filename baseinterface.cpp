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
#include "baseinterface.h"
#include "Journey.h"

namespace io
{
	void baseinterface::init()
	{
		node hpbar = nx::nodes["UI"]["UIWindow2.img"]["EnergyBar"];
		mobhpbar["hpbarfront"] = texture(hpbar["w"]);
		mobhpbar["hpbarmid"] = texture(hpbar["c"]);
		mobhpbar["hpbarend"] = texture(hpbar["e"]);
		mobhpbar["hpbarfill0"] = texture(hpbar["Gage"]["1"]["0"]);
		mobhpbar["hpbarfill1"] = texture(hpbar["Gage"]["1"]["1"]);

		dmgset = charset(nx::nodes["Effect"]["BasicEff.img"]["NoRed0"]);
		critset = charset(nx::nodes["Effect"]["BasicEff.img"]["NoCri0"]);
		playerdmgset = charset(nx::nodes["Effect"]["BasicEff.img"]["NoViolet0"]);

		infotextw = textlabel(DWF_12R, TXC_WHITE, "");
		infotexty = textlabel(DWF_12R, TXC_YELLOW, "");

		position = vector2d();
		dimensions = vector2d();
		active = true;
		dragged = false;
		buttoncd = 0;
		dmglock = SRWLOCK_INIT;
	}

	void baseinterface::showdamage(vector<pair<int, char>> numbers, vector2d pos)
	{
		AcquireSRWLockExclusive(&dmglock);

		float yshift = 0;
		float ashift = 0;
		for (vector<pair<int, char>>::iterator nmit = numbers.begin(); nmit != numbers.end(); ++nmit)
		{
			dmgeffect toadd;
			toadd.number = nmit->first;
			toadd.type = nmit->second;
			toadd.fx = static_cast<float>(pos.x());
			toadd.fy = static_cast<float>(pos.y()) - yshift;
			toadd.alpha = 1.0f + ashift;
			dmgeffects.push_back(toadd);

			yshift += (toadd.type == 1) ? 26 : 24;
			ashift += 0.1f;
		}

		ReleaseSRWLockExclusive(&dmglock);
	}

	void baseinterface::draw(vector2d viewpos)
	{
		if (active)
		{
			if (TryAcquireSRWLockShared(&dmglock))
			{
				for (vector<dmgeffect>::iterator dmgit = dmgeffects.begin(); dmgit != dmgeffects.end(); ++dmgit)
				{
					float alpha = dmgit->alpha;

					if (alpha <= 1.0f)
					{
						string number = (dmgit->number > 0) ? to_string(dmgit->number) : "M";
						vector2d drawpos = vector2d(static_cast<int>(dmgit->fx), static_cast<int>(dmgit->fy));

						switch (dmgit->type)
						{
						case 0:
							dmgset.draw(number, 22, cha_center, drawpos + viewpos, alpha);
							break;
						case 1:
							critset.draw(number, 24, cha_center, drawpos + viewpos, alpha);
							break;
						case 2:
							playerdmgset.draw(number, 22, cha_center, drawpos + viewpos, alpha);
							break;
						}
					}
				}
				ReleaseSRWLockShared(&dmglock);
			}

			vector2d chatbpos = viewpos - vector2d(0, 90);
			for (smit<int, chatballoon> cbit = chatballoons.getit(); cbit.belowtop(); ++cbit)
			{
				int cid = cbit.getkey();

				if (cid == app.getui()->getfield()->getplayer()->getstats()->getid())
				{
					cbit->draw(app.getui()->getfield()->getplayer()->getposition() + chatbpos);
				}
				else
				{
					otherplayer* otherchar = app.getui()->getfield()->getchars()->getchar(cid);
					if (otherchar)
					{
						cbit->draw(otherchar->getposition() + chatbpos);
					}
					else
					{
						cbit->expire();
					}
				}
			}

			vector2d infotop = vector2d(790, 510 - (static_cast<int>(statusinfos.size()) * 16));
			for (char i = 0; i < statusinfos.size(); i++)
			{
				statusinfo sfit = statusinfos[i];
				if (sfit.white)
				{
					infotextw.setalpha(sfit.alpha);
					infotextw.drawline(sfit.text, infotop + vector2d(0, 16 * i));
				}
				else
				{
					infotexty.setalpha(sfit.alpha);
					infotexty.drawline(sfit.text, infotop + vector2d(0, 16 * i));
				}
			}
		}
	}

	void baseinterface::update()
	{
		vector<int> chatbremove;
		char dmgremove = 0;
		char inforemove = 0;

		if (TryAcquireSRWLockShared(&dmglock))
		{
			for (vector<dmgeffect>::iterator dmgit = dmgeffects.begin(); dmgit != dmgeffects.end(); ++dmgit)
			{
				dmgit->fy -= 0.4f;
				dmgit->alpha = dmgit->alpha - 0.008f;
			}
			ReleaseSRWLockShared(&dmglock);
		}

		for (vector<statusinfo>::iterator sfit = statusinfos.begin(); sfit != statusinfos.end(); ++sfit)
		{
			sfit->alpha -= 0.0025f;
			if (sfit->alpha < 0.0025f)
			{
				inforemove++;
			}
		}

		for (smit<int, chatballoon> cbit = chatballoons.getit(); cbit.belowtop(); ++cbit)
		{
			bool remove = cbit->update();

			if (remove)
			{
				chatbremove.push_back(cbit.getindex());
			}
		}

		AcquireSRWLockExclusive(&dmglock);
		for (char i = 0; i < dmgremove; i++)
		{
			dmgeffects.erase(dmgeffects.begin());
		}
		ReleaseSRWLockExclusive(&dmglock);

		for (char i = 0; i < inforemove; i++)
		{
			statusinfos.erase(statusinfos.begin());
		}

		chatballoons.removeall(chatbremove);
	}

	void baseinterface::drawmobhp(char percent, vector2d pos)
	{
		mobhpbar["hpbarfront"].draw(pos);
		mobhpbar["hpbarmid"].draw(pos + vector2d(5, 0), vector2d(50, 0));
		mobhpbar["hpbarend"].draw(pos + vector2d(55, 0));
		mobhpbar["hpbarfill1"].draw(pos + vector2d(2, 2), vector2d(percent / 2, 0));
	}

	void baseinterface::addstatusinfo(bool white, string text)
	{
		statusinfo info;
		info.white = white;
		info.text = text;
		info.alpha = 1.0f;
		statusinfos.push_back(info);
	}

	void baseinterface::addnpcbutton(int npcid, vector2d pos, vector2d dim)
	{
		npcbuttons.add(npcid, button(pos, dim));
	}

	void baseinterface::addchatballoon(int cid, char type, string text)
	{
		chatballoons.add(cid, chatballoon(type, text));
	}
}
