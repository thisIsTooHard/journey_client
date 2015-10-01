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
#include "statsinfo.h"
#include "Journey.h"

namespace io
{
	statsinfo::statsinfo(maplestats* st, inventory* iv)
	{
		app.getimgcache()->setmode(ict_sys);

		nl::node src = nl::nx::nodes["UI"]["UIWindow4.img"]["Stat"]["main"];
		nl::node detail = nl::nx::nodes["UI"]["UIWindow4.img"]["Stat"]["detail"];

		sprites.push_back(sprite(animation(src["backgrnd"]), vector2d()));
		sprites.push_back(sprite(animation(src["backgrnd2"]), vector2d()));
		sprites.push_back(sprite(animation(src["backgrnd3"]), vector2d()));

		detailbgs.push_back(texture(detail["backgrnd"]));
		detailbgs.push_back(texture(detail["backgrnd2"]));
		detailbgs.push_back(texture(detail["backgrnd3"]));

		abilities["rare"] = texture(detail["abilityTitle"]["rare"]["0"]);
		abilities["epic"] = texture(detail["abilityTitle"]["epic"]["0"]);
		abilities["unique"] = texture(detail["abilityTitle"]["unique"]["0"]);
		abilities["legendary"] = texture(detail["abilityTitle"]["legendary"]["0"]);
		abilities["none"] = texture(detail["abilityTitle"]["normal"]["0"]);

		buttons[BT_STATS_HP] = button(src["BtHpUp"]);
		buttons[BT_STATS_MP] = button(src["BtMpUp"]);
		buttons[BT_STATS_STR] = button(src["BtStrUp"]);
		buttons[BT_STATS_DEX] = button(src["BtDexUp"]);
		buttons[BT_STATS_LUK] = button(src["BtLukUp"]);
		buttons[BT_STATS_INT] = button(src["BtIntUp"]);

		if (st->getstat(MS_AP) == 0)
		{
			buttons[BT_STATS_HP].setstate(BTS_DISABLED);
			buttons[BT_STATS_MP].setstate(BTS_DISABLED);
			buttons[BT_STATS_STR].setstate(BTS_DISABLED);
			buttons[BT_STATS_DEX].setstate(BTS_DISABLED);
			buttons[BT_STATS_LUK].setstate(BTS_DISABLED);
			buttons[BT_STATS_INT].setstate(BTS_DISABLED);
		}

		buttons[BT_STATS_DETAILOPEN] = button(src["BtDetailOpen"]);
		buttons[BT_STATS_DETAILCLOSE] = button(src["BtDetailClose"]);
		buttons[BT_STATS_DETAILCLOSE].setactive(false);

		statlabel = textlabel(DWF_12L, TXC_BLACK, "");

		app.getimgcache()->unlock();
		position = config.getconfig()->statsinfopos;
		dimensions = vector2d(212, 318);
		active = true;
		dragged = false;
		buttoncd = 0;
		showdetail = false;
		stats = st;
		invent = iv;
	}

	void statsinfo::draw()
	{
		uielement::draw();

		if (active)
		{
			statlabel.drawline(stats->getname(), position + vector2d(73, 25));
			statlabel.drawline(stats->getjobname(), position + vector2d(73, 43));
			statlabel.drawline("", position + vector2d(73, 61)); //guild
			statlabel.drawline(to_string(stats->getstat(MS_FAME)), position + vector2d(73, 79));
			statlabel.drawline(to_string(stats->getmindamage()) + " ~ " + to_string(stats->getmaxdamage()), position + vector2d(73, 97));
			statlabel.drawline(to_string(stats->getstat(MS_HP)) + " / " + to_string(stats->gettotal(MS_MAXHP)), position + vector2d(73, 115));
			statlabel.drawline(to_string(stats->getstat(MS_MP)) + " / " + to_string(stats->gettotal(MS_MAXMP)), position + vector2d(73, 133));
			statlabel.drawline(to_string(stats->getstat(MS_AP)), position + vector2d(79, 175));
			statlabel.drawline(to_string(stats->getstat(MS_STR) + invent->gettotal(ES_STR)) + " (" + to_string(stats->getstat(MS_STR)) + " + " + to_string(invent->gettotal(ES_STR)) + ")", position + vector2d(73, 202));
			statlabel.drawline(to_string(stats->getstat(MS_DEX) + invent->gettotal(ES_DEX)) + " (" + to_string(stats->getstat(MS_DEX)) + " + " + to_string(invent->gettotal(ES_DEX)) + ")", position + vector2d(73, 220));
			statlabel.drawline(to_string(stats->getstat(MS_INT) + invent->gettotal(ES_INT)) + " (" + to_string(stats->getstat(MS_INT)) + " + " + to_string(invent->gettotal(ES_INT)) + ")", position + vector2d(73, 238));
			statlabel.drawline(to_string(stats->getstat(MS_LUK) + invent->gettotal(ES_LUK)) + " (" + to_string(stats->getstat(MS_LUK)) + " + " + to_string(invent->gettotal(ES_LUK)) + ")", position + vector2d(73, 256));

			if (showdetail)
			{
				vector2d detailpos = position + vector2d(213, 0);

				for (vector<texture>::iterator dtit = detailbgs.begin(); dtit != detailbgs.end(); ++dtit)
				{
					dtit->draw(detailpos);
				}

				abilities["none"].draw(detailpos);

				string critstr = to_string(static_cast<int>(stats->getcritical() * 100));
				string mincritstr = to_string(static_cast<int>(stats->getmincrit() * 100));
				string maxcritstr = to_string(static_cast<int>(stats->getmaxcrit() * 100));
				string bdmstr = to_string(static_cast<int>(stats->getbossdmg() * 100));
				string idefstr = to_string(static_cast<int>(stats->getignoredef() * 100));
				string resistr = to_string(static_cast<int>(stats->getresist() * 100));
				string stancestr = to_string(static_cast<int>(stats->getstance() * 100));

				statlabel.drawline(to_string(stats->getattack()), detailpos + vector2d(73, 35));
				statlabel.drawline(critstr + "%", detailpos + vector2d(73, 53));
				statlabel.drawline(mincritstr + "%", detailpos + vector2d(73, 71));
				statlabel.drawline(maxcritstr + "%", detailpos + vector2d(168, 71));
				statlabel.drawline(bdmstr + "%", detailpos + vector2d(73, 89));
				statlabel.drawline(idefstr + "%", detailpos + vector2d(168, 89));
				statlabel.drawline(resistr + "%", detailpos + vector2d(73, 107));
				statlabel.drawline(stancestr + "%", detailpos + vector2d(168, 107));
				statlabel.drawline(to_string(invent->gettotal(ES_WDEF)), detailpos + vector2d(73, 125));
				statlabel.drawline(to_string(invent->gettotal(ES_MDEF)), detailpos + vector2d(73, 143));
				statlabel.drawline(to_string(stats->getaccuracy() + invent->getaccuracy()), detailpos + vector2d(73, 161));
				statlabel.drawline("0", detailpos + vector2d(73, 179));
				statlabel.drawline(to_string(invent->gettotal(ES_AVOID)), detailpos + vector2d(73, 197));
				statlabel.drawline("0", detailpos + vector2d(73, 215));
				statlabel.drawline(to_string(invent->gettotal(ES_SPEED) + 100) + "%", detailpos + vector2d(73, 233));
				statlabel.drawline(to_string(invent->gettotal(ES_JUMP) + 100) + "%", detailpos + vector2d(168, 233));
				statlabel.drawline(to_string(stats->gethonor()), detailpos + vector2d(73, 351));
			}
		}
	}

	void statsinfo::sendbool(bool hasap)
	{
		if (hasap)
		{
			buttons[BT_STATS_HP].setstate(BTS_NORMAL);
			buttons[BT_STATS_MP].setstate(BTS_NORMAL);
			buttons[BT_STATS_STR].setstate(BTS_NORMAL);
			buttons[BT_STATS_DEX].setstate(BTS_NORMAL);
			buttons[BT_STATS_LUK].setstate(BTS_NORMAL);
			buttons[BT_STATS_INT].setstate(BTS_NORMAL);
		}
		else
		{
			buttons[BT_STATS_HP].setstate(BTS_DISABLED);
			buttons[BT_STATS_MP].setstate(BTS_DISABLED);
			buttons[BT_STATS_STR].setstate(BTS_DISABLED);
			buttons[BT_STATS_DEX].setstate(BTS_DISABLED);
			buttons[BT_STATS_LUK].setstate(BTS_DISABLED);
			buttons[BT_STATS_INT].setstate(BTS_DISABLED);
		}
	}

	void statsinfo::buttonpressed(short id)
	{
		switch (id)
		{
		case BT_STATS_DETAILOPEN:
			showdetail = true;
			buttons[BT_STATS_DETAILOPEN].setactive(false);
			buttons[BT_STATS_DETAILCLOSE].setactive(true);
			break;
		case BT_STATS_DETAILCLOSE:
			showdetail = false;
			buttons[BT_STATS_DETAILCLOSE].setactive(false);
			buttons[BT_STATS_DETAILOPEN].setactive(true);
			break;
		case BT_STATS_HP:
			packet_c.spendap(MS_HP);
			app.getui()->disableactions();
			break;
		case BT_STATS_MP:
			packet_c.spendap(MS_MP);
			app.getui()->disableactions();
			break;
		case BT_STATS_STR:
			packet_c.spendap(MS_STR);
			app.getui()->disableactions();
			break;
		case BT_STATS_DEX:
			packet_c.spendap(MS_DEX);
			app.getui()->disableactions();
			break;
		case BT_STATS_INT:
			packet_c.spendap(MS_INT);
			app.getui()->disableactions();
			break;
		case BT_STATS_LUK:
			packet_c.spendap(MS_LUK);
			app.getui()->disableactions();
			break;
		}

		buttons[id].setstate(BTS_NORMAL);
	}

	rectangle2d statsinfo::dragarea()
	{
		return rectangle2d(position, position + vector2d(212, 20));
	}
}
