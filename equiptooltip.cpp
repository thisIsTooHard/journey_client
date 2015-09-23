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
#include "equiptooltip.h"
#include "Journey.h"

namespace io
{
	void equiptooltip::init()
	{
		node itemtt = nx::nodes["UI"]["UIToolTip.img"]["Item"];

		top = texture(itemtt["Frame"]["top"]);
		mid = texture(itemtt["Frame"]["line"]);
		line = texture(itemtt["Frame"]["dotline"]);
		bot = texture(itemtt["Frame"]["bottom"]);
		base = texture(itemtt["ItemIcon"]["base"]);
		cover = texture(itemtt["ItemIcon"]["cover"]);
		shade = texture(itemtt["ItemIcon"]["shade"]);

		potential[PTR_HIDDEN] = texture(itemtt["ItemIcon"]["0"]);
		potential[PTR_RARE] = texture(itemtt["ItemIcon"]["1"]);
		potential[PTR_EPIC] = texture(itemtt["ItemIcon"]["2"]);
		potential[PTR_UNIQUE] = texture(itemtt["ItemIcon"]["3"]);
		potential[PTR_LEGEND] = texture(itemtt["ItemIcon"]["4"]);

		reqstat[MS_LEVEL][false] = texture(itemtt["Equip"]["Cannot"]["reqLEV"]);
		reqstat[MS_LEVEL][true] = texture(itemtt["Equip"]["Can"]["reqLEV"]);
		reqstat[MS_FAME][false] = texture(itemtt["Equip"]["Cannot"]["reqPOP"]);
		reqstat[MS_FAME][true] = texture(itemtt["Equip"]["Can"]["reqPOP"]);
		reqstat[MS_STR][false] = texture(itemtt["Equip"]["Cannot"]["reqSTR"]);
		reqstat[MS_STR][true] = texture(itemtt["Equip"]["Can"]["reqSTR"]);
		reqstat[MS_DEX][false] = texture(itemtt["Equip"]["Cannot"]["reqDEX"]);
		reqstat[MS_DEX][true] = texture(itemtt["Equip"]["Can"]["reqDEX"]);
		reqstat[MS_INT][false] = texture(itemtt["Equip"]["Cannot"]["reqINT"]);
		reqstat[MS_INT][true] = texture(itemtt["Equip"]["Can"]["reqINT"]);
		reqstat[MS_LUK][false] = texture(itemtt["Equip"]["Cannot"]["reqLUK"]);
		reqstat[MS_LUK][true] = texture(itemtt["Equip"]["Can"]["reqLUK"]);

		reqset[false] = charset(itemtt["Equip"]["Cannot"]);
		reqset[true] = charset(itemtt["Equip"]["Can"]);

		jobsbg = texture(itemtt["Equip"]["Job"]["normal"]);
		jobs[false][0] = texture(itemtt["Equip"]["Job"]["disable"]["0"]);
		jobs[false][1] = texture(itemtt["Equip"]["Job"]["disable"]["1"]);
		jobs[false][2] = texture(itemtt["Equip"]["Job"]["disable"]["2"]);
		jobs[false][3] = texture(itemtt["Equip"]["Job"]["disable"]["3"]);
		jobs[false][4] = texture(itemtt["Equip"]["Job"]["disable"]["4"]);
		jobs[false][5] = texture(itemtt["Equip"]["Job"]["disable"]["5"]);
		jobs[true][0] = texture(itemtt["Equip"]["Job"]["enable"]["0"]);
		jobs[true][1] = texture(itemtt["Equip"]["Job"]["enable"]["1"]);
		jobs[true][2] = texture(itemtt["Equip"]["Job"]["enable"]["2"]);
		jobs[true][3] = texture(itemtt["Equip"]["Job"]["enable"]["3"]);
		jobs[true][4] = texture(itemtt["Equip"]["Job"]["enable"]["4"]);
		jobs[true][5] = texture(itemtt["Equip"]["Job"]["enable"]["5"]);

		itemid = 0;
		slot = 0;
		active = false;
	}

	void equiptooltip::setequip(clothing* cl, mapleequip* eq, maplestats* stats)
	{
		cloth = cl;
		equip = eq;

		itemid = cloth->getid();
		slot = equip->getpos();

		filllength = 500;

		canequip[MS_LEVEL] = stats->getstat(MS_LEVEL) >= cloth->getreqstat(MS_LEVEL);
		canequip[MS_FAME] = true;
		canequip[MS_STR] = stats->gettotal(MS_STR) >= cloth->getreqstat(MS_STR);
		canequip[MS_DEX] = stats->gettotal(MS_DEX) >= cloth->getreqstat(MS_DEX);
		canequip[MS_INT] = stats->gettotal(MS_INT) >= cloth->getreqstat(MS_INT);
		canequip[MS_LUK] = stats->gettotal(MS_LUK) >= cloth->getreqstat(MS_LUK);

		okjobs.clear();
		switch (cloth->getreqstat(MS_JOB))
		{
		case 0:
			okjobs.push_back(0);
			okjobs.push_back(1);
			okjobs.push_back(2);
			okjobs.push_back(3);
			okjobs.push_back(4);
			okjobs.push_back(5);
			canequip[MS_JOB] = true;
			break;
		case 1:
			okjobs.push_back(1);
			canequip[MS_JOB] = (stats->getstat(MS_JOB) / 100 == 1) || (stats->getstat(MS_JOB) / 100 >= 20);
			break;
		case 2:
			okjobs.push_back(2);
			canequip[MS_JOB] = stats->getstat(MS_JOB) / 100 == 2;
			break;
		case 4:
			okjobs.push_back(3);
			canequip[MS_JOB] = stats->getstat(MS_JOB) / 100 == 3;
			break;
		case 8:
			okjobs.push_back(4);
			canequip[MS_JOB] = stats->getstat(MS_JOB) / 100 == 4;
			break;
		case 16:
			okjobs.push_back(5);
			canequip[MS_JOB] = stats->getstat(MS_JOB) / 100 == 5;
			break;
		default:
			canequip[MS_JOB] = false;
		}

		rank = equip->getrank();

		switch (rank)
		{
		case PTR_HIDDEN:
			potflag = textlabel(DWF_12C, TXC_RED, "(Hidden Potential)");
			break;
		case PTR_RARE:
			potflag = textlabel(DWF_12C, TXC_WHITE, "(Rare Item)");
			break;
		case PTR_EPIC:
			potflag = textlabel(DWF_12C, TXC_WHITE, "(Epic Item)");
			break;
		case PTR_UNIQUE:
			potflag = textlabel(DWF_12C, TXC_WHITE, "(Unique Item)");
			break;
		case PTR_LEGEND:
			potflag = textlabel(DWF_12C, TXC_WHITE, "(Legendary Item)");
			break;
		default:
			filllength -= 16;
		}

		textcolor namecolor;
		switch (equip->getquality())
		{
		case EQQ_GREY:
			namecolor = TXC_GREY;
			break;
		case EQQ_ORANGE:
			namecolor = TXC_ORANGE;
			break;
		case EQQ_BLUE:
			namecolor = TXC_MBLUE;
			break;
		case EQQ_VIOLET:
			namecolor = TXC_VIOLET;
			break;
		case EQQ_GOLD:
			namecolor = TXC_YELLOW;
			break;
		default:
			namecolor = TXC_WHITE;
		}
		string namestr = cloth->getname();
		if (equip->getlevel() > 0)
		{
			namestr.append(" (+");
			namestr.append(to_string(equip->getlevel()));
			namestr.append(")");
		}
		name = textlabel(DWF_14C, namecolor, namestr);
		
		category = textlabel(DWF_12LL, TXC_WHITE, "CATEGORY: " + cloth->gettype());
		wepspeed = textlabel(DWF_12LL, TXC_WHITE, "ATTACK SPEED: " + cloth->getdisplayspeed());

		if (cloth->getslots() > 0)
		{
			slots = textlabel(DWF_12LL, TXC_WHITE, "UPGRADES AVAILABLE: " + to_string(equip->getslots()));

			string vicious = to_string(equip->getvicious());
			if (equip->getvicious() > 1)
			{
				vicious.append(" (MAX) ");
			}
			hammers = textlabel(DWF_12LL, TXC_WHITE, "VICIOUS HAMMERS USED: " + vicious);
		}
		else
		{
			filllength -= 36;
		}

		if (cloth->getwspeed() == 0)
		{
			filllength -= 18;
		}

		statlabels.clear();
		for (equipstat es = ES_STR; es <= ES_JUMP; es = static_cast<equipstat>(es + 1))
		{
			if (equip->getstat(es) > 0)
			{
				short delta = equip->getstat(es) - cloth->getdefstat(es);
				string statstr = to_string(equip->getstat(es));
				if (delta != 0)
				{
					statstr.append(" (");
					statstr.append((delta < 0) ? "-" : "+");
					statstr.append(to_string(abs(delta)) + ")");
				}
				statlabels[es] = textlabel(DWF_12LL, TXC_WHITE, cloth->getdisplaystat(es) + ": " + statstr);
			}
			else
			{
				filllength -= 18;
			}
		}

		active = true;
	}

	void equiptooltip::draw(vector2d pos)
	{
		if (active)
		{
			top.draw(pos);
			mid.draw(pos + vector2d(0, 13), vector2d(0, filllength));
			bot.draw(pos + vector2d(0, filllength + 13));
			name.draw(pos + vector2d(130, 3));

			if (equip->getrank() != PTR_NONE)
			{
				potflag.draw(pos + vector2d(130, 20));
				pos = pos + vector2d(0, 16);
			}

			pos = pos + vector2d(0, 28);

			line.draw(pos);

			base.draw(pos + vector2d(10, 10));
			shade.draw(pos + vector2d(10, 10));

			vector2d iconpos = pos + vector2d(20, 82);

			texture* ico = &cloth->geticon(true);
			ico->draw(iconpos, 2.0f, 2.0f);

			potential[rank].draw(pos + vector2d(10, 10));
			cover.draw(pos + vector2d(10, 10));

			pos = pos + vector2d(0, 12);

			string rlvstr = to_string(cloth->getreqstat(MS_LEVEL));
			rlvstr.insert(0, 3 - rlvstr.size(), '0');
			reqstat[MS_LEVEL][canequip[MS_LEVEL]].draw(pos + vector2d(98, 48));
			reqset[canequip[MS_LEVEL]].draw(rlvstr, 6, cha_left, pos + vector2d(145, 48));

			string rstrstr = to_string(cloth->getreqstat(MS_STR));
			rstrstr.insert(0, 3 - rstrstr.size(), '0');
			reqstat[MS_STR][canequip[MS_STR]].draw(pos + vector2d(98, 64));
			reqset[canequip[MS_STR]].draw(rstrstr, 6, cha_left, pos + vector2d(145, 64));

			string rdexstr = to_string(cloth->getreqstat(MS_DEX));
			rdexstr.insert(0, 3 - rdexstr.size(), '0');
			reqstat[MS_DEX][canequip[MS_DEX]].draw(pos + vector2d(98, 72));
			reqset[canequip[MS_DEX]].draw(rdexstr, 6, cha_left, pos + vector2d(145, 72));

			string rlukstr = to_string(cloth->getreqstat(MS_LUK));
			rlukstr.insert(0, 3 - rlukstr.size(), '0');
			reqstat[MS_LUK][canequip[MS_LUK]].draw(pos + vector2d(173, 64));
			reqset[canequip[MS_LUK]].draw(rlukstr, 6, cha_left, pos + vector2d(220, 64));

			string rintstr = to_string(cloth->getreqstat(MS_INT));
			rintstr.insert(0, 3 - rintstr.size(), '0');
			reqstat[MS_INT][canequip[MS_INT]].draw(pos + vector2d(173, 72));
			reqset[canequip[MS_INT]].draw(rintstr, 6, cha_left, pos + vector2d(220, 72));

			pos = pos + vector2d(0, 88);

			vector2d jobspos = pos + vector2d(8, 0);
			jobsbg.draw(jobspos);
			for (vector<char>::iterator jbit = okjobs.begin(); jbit != okjobs.end(); ++jbit)
			{
				jobs[canequip[MS_JOB]][*jbit].draw(jobspos);
			}

			line.draw(pos + vector2d(0, 30));

			pos = pos + vector2d(0, 32);

			category.draw(pos + vector2d(10, 0));

			pos = pos + vector2d(0, 18);

			if (cloth->getwspeed() > 0)
			{
				wepspeed.draw(pos + vector2d(10, 0));
				pos = pos + vector2d(0, 18);
			}

			for (map<equipstat, textlabel>::iterator stit = statlabels.begin(); stit != statlabels.end(); ++stit)
			{
				stit->second.draw(pos + vector2d(10, 0));
				pos = pos + vector2d(0, 18);
			}

			if (cloth->getslots() > 0)
			{
				slots.draw(pos + vector2d(10, 0));
				pos = pos + vector2d(0, 18); 
				hammers.draw(pos + vector2d(10, 0));
				pos = pos + vector2d(0, 18);
			}
		}
	}
}
