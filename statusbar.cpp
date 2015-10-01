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
#include "statusbar.h"
#include "Journey.h"

namespace io
{
	statusbar::statusbar(maplestats* pstats)
	{
		app.getimgcache()->setmode(ict_sys);

		node mainbar = nx::nodes["UI"]["StatusBar2.img"]["mainBar"];
		node chat = nx::nodes["UI"]["StatusBar2.img"]["chat"];

		sprites.push_back(sprite(animation(mainbar["backgrnd"]), vector2d(0, 0)));
		sprites.push_back(sprite(animation(mainbar["gaugeBackgrd"]), vector2d(0, 0)));
		sprites.push_back(sprite(animation(mainbar["notice"]), vector2d(0, 0)));
		sprites.push_back(sprite(animation(mainbar["lvBacktrnd"]), vector2d(0, 0)));
		sprites.push_back(sprite(animation(mainbar["lvCover"]), vector2d(0, 0)));

		exp = uibar(texture(mainbar.resolve("gauge/exp/0")), texture(mainbar.resolve("gauge/exp/1")), texture(mainbar.resolve("gauge/exp/2")), 308, vector2d(-261, -15));
		hp = uibar(texture(mainbar.resolve("gauge/hp/0")), texture(mainbar.resolve("gauge/hp/1")), texture(mainbar.resolve("gauge/hp/2")), 137, vector2d(-261, -31));
		mp = uibar(texture(mainbar.resolve("gauge/mp/0")), texture(mainbar.resolve("gauge/mp/1")), texture(mainbar.resolve("gauge/mp/2")), 137, vector2d(-90, -31));

		statset = charset(mainbar.resolve("gauge/number"));
		lvset = charset(mainbar.resolve("lvNumber"));

		job = textlabel(DWF_12L, TXC_YELLOW, "");
		name = textlabel(DWF_14L, TXC_WHITE, "");

		buttons[BT_BAR_WHISPER] = button(mainbar["BtChat"]);
		buttons[BT_BAR_CALLGM] = button(mainbar["BtClaim"]);

		buttons[BT_BAR_CASHSHOP] = button(mainbar["BtCashShop"]);
		buttons[BT_BAR_TRADE] = button(mainbar["BtMTS"]);
		buttons[BT_BAR_MENU] = button(mainbar["BtMenu"]);
		buttons[BT_BAR_SYSOP] = button(mainbar["BtSystem"]);

		buttons[BT_BAR_CHARINFO] = button(mainbar["BtCharacter"]);
		buttons[BT_BAR_STATS] = button(mainbar["BtStat"]);
		buttons[BT_BAR_QUEST] = button(mainbar["BtQuest"]);
		buttons[BT_BAR_INVENTORY] = button(mainbar["BtInven"]);
		buttons[BT_BAR_EQUIPS] = button(mainbar["BtEquip"]);
		buttons[BT_BAR_SKILL] = button(mainbar["BtSkill"]);

		app.getimgcache()->unlock();

		position = vector2d(512, 590);
		dimensions = vector2d(1366, 80);
		active = true;
		dragged = false;
		buttoncd = 0;
		stats = pstats;
	}

	void statusbar::draw()
	{
		uielement::draw();

		if (active)
		{
			int cexp = stats->getexp();
			int expneed = stats->getexpneeded();
			short chp = stats->getstat(MS_HP);
			short cmp = stats->getstat(MS_MP);
			short maxhp = stats->gettotal(MS_MAXHP);
			short maxmp = stats->gettotal(MS_MAXMP);

			float expperc = static_cast<float>(static_cast<double>(cexp) / expneed);
			float hpperc = static_cast<float>(chp) / maxhp;
			float mpperc = static_cast<float>(cmp) / maxmp;

			exp.draw(position, expperc);
			hp.draw(position, hpperc);
			mp.draw(position, mpperc);

			string exppercent = to_string(100 * expperc);
			statset.draw(to_string(cexp) + "[" + exppercent.substr(0, exppercent.find('.') + 3) + "%]", cha_right, position + vector2d(47, -13));
			statset.draw("[" + to_string(chp) + "/" + to_string(maxhp) + "]", cha_right, position + vector2d(-124, -29));
			statset.draw("[" + to_string(cmp) + "/" + to_string(maxmp) + "]", cha_right, position + vector2d(47, -29));

			lvset.draw(to_string(stats->getstat(MS_LEVEL)), cha_left, position + vector2d(-480, -24));
			job.draw(stats->getjobname(), position + vector2d(-435, -22));
			name.draw(stats->getname(), position + vector2d(-435, -37));
		}
	}

	void statusbar::update()
	{
		uielement::update();
	}

	void statusbar::buttonpressed(short id)
	{
		switch (id)
		{
		case BT_BAR_SYSOP:
			app.getui()->add(UI_SYSTEM);
			break;
		case BT_BAR_STATS:
			app.getui()->add(UI_STATSINFO);
			break;
		case BT_BAR_EQUIPS:
			app.getui()->add(UI_EQUIPS);
			break;
		}
		buttons[id].setstate(BTS_MOUSEOVER);
	}

	rectangle2d statusbar::bounds()
	{
		return rectangle2d(position - vector2d(512, 84), position - vector2d(512, 84) + dimensions);
	}
}
