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
#include "skillinventory.h"
#include "Journey.h"

namespace io
{
	skillinventory::skillinventory(skillbook* skl, maplestats* sts)
	{
		skills = skl;
		stats = sts;

		page = 0;

		app.getimgcache()->setmode(ict_sys);

		node src = nx::nodes["UI"]["UIWindow2.img"]["Skill"];
		node main = src["main"];

		sprites.push_back(sprite(animation(main["backgrnd"]), vector2d()));
		sprites.push_back(sprite(animation(main["backgrnd2"]), vector2d()));
		sprites.push_back(sprite(animation(main["backgrnd3"]), vector2d()));

		entry[false] = texture(main["skill0"]);
		entry[true] = texture(main["skill1"]);

		buttons[BT_SKILL_JOB0] = button(texture(main["Tab"]["disabled"]["0"]), texture(main["Tab"]["enabled"]["0"]), 0, 0);
		buttons[BT_SKILL_JOB1] = button(texture(main["Tab"]["disabled"]["1"]), texture(main["Tab"]["enabled"]["1"]), 0, 0);
		buttons[BT_SKILL_JOB2] = button(texture(main["Tab"]["disabled"]["2"]), texture(main["Tab"]["enabled"]["2"]), 0, 0);
		buttons[BT_SKILL_JOB3] = button(texture(main["Tab"]["disabled"]["3"]), texture(main["Tab"]["enabled"]["3"]), 0, 0);
		buttons[BT_SKILL_JOB4] = button(texture(main["Tab"]["disabled"]["4"]), texture(main["Tab"]["enabled"]["4"]), 0, 0);

		buttons[BT_SKILL_JOB0].setstate(BTS_PRESSED);

		short job = stats->getstat(MS_JOB);
		if (job < 100)
		{
			joblevel = 0;
			buttons[BT_SKILL_JOB1].setactive(false);
			buttons[BT_SKILL_JOB2].setactive(false);
			buttons[BT_SKILL_JOB3].setactive(false);
			buttons[BT_SKILL_JOB4].setactive(false);
		}
		else if (job % 100 == 0)
		{
			joblevel = 1;
			buttons[BT_SKILL_JOB2].setactive(false);
			buttons[BT_SKILL_JOB3].setactive(false);
			buttons[BT_SKILL_JOB4].setactive(false);
		}
		else if (job % 10 == 0)
		{
			joblevel = 2;
			buttons[BT_SKILL_JOB3].setactive(false);
			buttons[BT_SKILL_JOB4].setactive(false);
		}
		else if (job % 10 == 1)
		{
			joblevel = 3;
			buttons[BT_SKILL_JOB4].setactive(false);
		}
		else
		{
			joblevel = 4;
		}

		buttons[BT_SKILL_MACRO] = button(main["BtMacro"]);
		buttons[BT_SKILL_MOUNT] = button(main["BtRide"]);
		buttons[BT_SKILL_GUILD] = button(main["BtGuildSkill"]);

		app.getimgcache()->unlock();

		bookname = textlabel(DWF_14C, TXC_WHITE, "");

		position = config.getconfig()->skillinvpos;
		dimensions = vector2d(174, 299);
		active = true;
		dragged = false;
		buttoncd = 0;
	}

	void skillinventory::draw()
	{
		uielement::draw();

		if (active)
		{
			bookname.drawline(stats->getjobname(getjobbypage()), position + vector2d(104, 56));
		}
	}

	void skillinventory::buttonpressed(short id)
	{
		char oldpage = page;
		switch (id)
		{
		case BT_SKILL_JOB0:
			page = 0;
			break;
		case BT_SKILL_JOB1:
			page = 1;
			break;
		case BT_SKILL_JOB2:
			page = 2;
			break;
		case BT_SKILL_JOB3:
			page = 3;
			break;
		case BT_SKILL_JOB4:
			page = 4;
			break;
		}

		if (page != oldpage)
		{
			buttons[BT_SKILL_JOB0 + oldpage].setstate(BTS_NORMAL);
		}
	}

	short skillinventory::getjobbypage()
	{
		short job = stats->getstat(MS_JOB);
		switch (page)
		{
		case 1:
			return 100 * (job / 100);
		case 2:
			return 10 * (job / 10);
		case 3:
			return job - 1;
		case 4:
			return job;
		default:
			return 0;
		}
	}

	rectangle2d skillinventory::dragarea()
	{
		return rectangle2d(position, position + vector2d(174, 20));
	}
}
