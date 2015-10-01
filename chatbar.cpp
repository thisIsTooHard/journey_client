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
#include "chatbar.h"
#include "Journey.h"

namespace io
{
	chatbar::chatbar()
	{
		app.getimgcache()->setmode(ict_sys);

		node mainbar = nx::nodes["UI"]["StatusBar2.img"]["mainBar"];
		node chat = nx::nodes["UI"]["StatusBar2.img"]["chat"];

		open = config.getconfig()->chatopen;

		buttons[BT_BAR_OPENCHAT] = button(mainbar["chatOpen"]);
		buttons[BT_BAR_CLOSECHAT] = button(mainbar["chatClose"]);
		buttons[BT_BAR_SCROLLUP] = button(mainbar["scrollUp"]);
		buttons[BT_BAR_SCROLLDOWN] = button(mainbar["scrollDown"]);
		buttons[BT_BAR_CHATTARGET] = button(mainbar["chatTarget"]["base"]);
		buttons[BT_BAR_CHATTARGET].setactive(open);

		buttons[open ? BT_BAR_OPENCHAT : BT_BAR_CLOSECHAT].setactive(false);

		chatspace[false] = texture(mainbar["chatSpace"]);
		chatspace[true] = texture(mainbar["chatEnter"]);
		chatenter = texture(mainbar["chatSpace2"]);
		chatcover = texture(mainbar["chatCover"]);

		chattargets[CHT_ALL] = texture(mainbar["chatTarget"]["all"]);
		chattargets[CHT_BUDDY] = texture(mainbar["chatTarget"]["friend"]);
		chattargets[CHT_GUILD] = texture(mainbar["chatTarget"]["guild"]);
		chattargets[CHT_ALLIANCE] = texture(mainbar["chatTarget"]["association"]);
		chattargets[CHT_PARTY] = texture(mainbar["chatTarget"]["party"]);
		chattargets[CHT_SQUAD] = texture(mainbar["chatTarget"]["expedition"]);

		textfields[TXT_CHAT] = textfield(TXT_CHAT, DWF_12L, TXC_BLACK, "", vector2d(-430, -60), 64);
		textfields[TXT_CHAT].setactive(open);

		closedtext = textlabel(DWF_12L, TXC_WHITE, "");

		app.getimgcache()->unlock();

		position = vector2d(512, 590);
		dimensions = vector2d(500, 80);
		active = true;
		dragged = false;
		buttoncd = 0;
		chattarget = CHT_ALL;
	}

	void chatbar::buttonpressed(short id)
	{
		switch (id)
		{
		case BT_BAR_OPENCHAT:
			open = true;
			buttons[BT_BAR_OPENCHAT].setactive(false);
			buttons[BT_BAR_CLOSECHAT].setactive(true);
			buttons[BT_BAR_CHATTARGET].setactive(true);
			textfields[TXT_CHAT].setactive(true);
			config.getconfig()->chatopen = true;
			break;
		case BT_BAR_CLOSECHAT:
			open = false;
			buttons[BT_BAR_OPENCHAT].setactive(true);
			buttons[BT_BAR_CLOSECHAT].setactive(false);
			buttons[BT_BAR_CHATTARGET].setactive(false);
			textfields[TXT_CHAT].setactive(false);
			config.getconfig()->chatopen = false;
			break;
		}
		buttons[id].setstate(BTS_NORMAL);
	}

	void chatbar::draw()
	{
		if (active)
		{
			chatspace[open].draw(position);
			chatenter.draw(position);
		}

		uielement::draw();

		if (active)
		{
			if (open)
			{
				chattargets[chattarget].draw(position + vector2d(0, 2));
				chatcover.draw(position);
			}
			else if (lines.size() > 0)
			{
				closedtext.drawline(lines.back(), position + vector2d(-500, -60));
			}
		}
	}

	void chatbar::sendtext(string text, bool gm)
	{
		lines.push_back(text);
	}

	void chatbar::update()
	{
		uielement::update();
	}

	rectangle2d chatbar::bounds()
	{
		vector2d absp = position - vector2d(512, 84);
		return rectangle2d(absp, absp + dimensions);
	}
}
