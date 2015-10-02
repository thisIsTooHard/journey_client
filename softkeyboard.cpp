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
#include "softkeyboard.h"
#include "Journey.h"

namespace io
{
	softkeyboard::softkeyboard(char md)
	{
		mode = static_cast<sftkb_mode>(md);

		app.getimgcache()->setmode(ict_sys);

		node src = nx::nodes["UI"]["Login.img"]["Common"]["SoftKey"];

		backgrounds.push_back(texture(src["backgrnd"]));
		backgrounds.push_back(texture(src["backgrnd2"]));
		backgrounds.push_back(texture(src["backgrnd3"]));

		node keys = src["BtNum"];

		buttons[BT_SOFTKEY_0] = button(keys["0"]);
		buttons[BT_SOFTKEY_1] = button(keys["1"]);
		buttons[BT_SOFTKEY_2] = button(keys["2"]);
		buttons[BT_SOFTKEY_3] = button(keys["3"]);
		buttons[BT_SOFTKEY_4] = button(keys["4"]);
		buttons[BT_SOFTKEY_5] = button(keys["5"]);
		buttons[BT_SOFTKEY_6] = button(keys["6"]);
		buttons[BT_SOFTKEY_7] = button(keys["7"]);
		buttons[BT_SOFTKEY_8] = button(keys["8"]);
		buttons[BT_SOFTKEY_9] = button(keys["9"]);

		buttons[BT_SOFTKEY_NEXT] = button(src["BtNext"]);
		buttons[BT_SOFTKEY_BACK] = button(src["BtDel"]);
		buttons[BT_SOFTKEY_OK] = button(src["BtOK"], 72, 235);
		buttons[BT_SOFTKEY_CANCEL] = button(src["BtCancel"], 13, 235);

		buttons[BT_SOFTKEY_OK].setstate(BTS_DISABLED);
		buttons[BT_SOFTKEY_BACK].setstate(BTS_DISABLED);

		app.getimgcache()->unlock();

		entry = textlabel(DWF_12L, TXC_BLACK, "");
		entered = "";

		shufflekeys();

		position = vector2d(330, 160);
		dimensions = vector2d(140, 280);
		active = true;
		dragged = false;
		buttoncd = 0;
	}

	void softkeyboard::draw()
	{
		uielement::draw();

		if (active)
		{
			entry.drawline(entered, position + vector2d(15, 41));
		}
	}

	void softkeyboard::buttonpressed(short id)
	{
		switch (id)
		{
		case BT_SOFTKEY_0:
		case BT_SOFTKEY_1:
		case BT_SOFTKEY_2:
		case BT_SOFTKEY_3:
		case BT_SOFTKEY_4:
		case BT_SOFTKEY_5:
		case BT_SOFTKEY_6:
		case BT_SOFTKEY_7:
		case BT_SOFTKEY_8:
		case BT_SOFTKEY_9:
			if (entered.size() < 8)
			{
				entered.append(to_string(id));
				shufflekeys();
				buttons[id].setstate(BTS_NORMAL);
			}
			break;
		case BT_SOFTKEY_BACK:
			if (entered.size() > 0)
			{
				entered.pop_back();
				buttons[BT_SOFTKEY_BACK].setstate(BTS_MOUSEOVER);
			}
			break;
		case BT_SOFTKEY_CANCEL:
			active = false;
			break;
		case BT_SOFTKEY_OK:
			if (entered.size() > 5)
			{
				int cid = app.getui()->getfield()->getlogin()->charid;
				switch (mode)
				{
				case SFTKB_CHARSELECT:
					app.getui()->disableactions();
					packet_c.selectcharpic(cid, entered);
					active = false;
					break;
				case SFTKB_REGISTER:
					app.getui()->disableactions();
					packet_c.registerpic(cid, entered);
					active = false;
					break;
				}
			}
			break;
		}

		switch (entered.size())
		{
		case 0:
			buttons[BT_SOFTKEY_BACK].setstate(BTS_DISABLED);
			break;
		case 1:
			buttons[BT_SOFTKEY_BACK].setstate(BTS_NORMAL);
			break;
		case 5:
			buttons[BT_SOFTKEY_OK].setstate(BTS_DISABLED);
			break;
		case 6:
			buttons[BT_SOFTKEY_OK].setstate(BTS_NORMAL);
			break;
		case 7:
			if (entered.size() == 8)
			{
				for (char i = 0; i < 10; i++)
				{
					buttons[i].setstate(BTS_NORMAL);
				}
			}
			break;
		case 8:
			for (char i = 0; i < 10; i++)
			{
				buttons[i].setstate(BTS_DISABLED);
			}
			break;
		}
	}

	void softkeyboard::shufflekeys()
	{
		vector<char> reserve;
		for (char i = 0; i < 10; i++)
		{
			reserve.push_back(i);
		}
		for (char i = 0; i < 10; i++)
		{
			size_t rand = random.nextint(reserve.size() - 1);
			vector2d pos = keypos(reserve[rand]);
			buttons[BT_SOFTKEY_0 + i].setposition(pos);
			reserve.erase(reserve.begin() + rand);
		}
	}

	vector2d softkeyboard::keypos(char num)
	{
		return vector2d(12 + (num % 3) * 39, 94 + (num / 3) * 35);
	}
}
