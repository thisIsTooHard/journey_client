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
#include "keyconfig.h"
#include "Journey.h"

namespace io
{
	keyconfig::keyconfig(map<char, pair<keytype, int>> keys, inventory* invent)
	{
		keymap = keys;

		app.getimgcache()->setmode(ict_sys);
		nl::nx::view_file("UI");

		nl::node src = nl::nx::nodes["UI"]["UIWindow2.img"]["KeyConfig"];

		sprites.push_back(sprite(animation(src["backgrnd"]), vector2d()));
		sprites.push_back(sprite(animation(src["backgrnd2"]), vector2d()));
		sprites.push_back(sprite(animation(src["backgrnd3"]), vector2d()));

		buttons[BT_KEYS_CANCEL] = button(src["BtCancel"], 0, 0);
		buttons[BT_KEYS_CLEAR] = button(src["BtDelete"], 0, 0);
		buttons[BT_KEYS_DEFAULT] = button(src["BtDefault"], 0, 0);
		buttons[BT_KEYS_OK] = button(src["BtOK"], 0, 0);
		buttons[BT_KEYS_QUICK] = button(src["BtQuickSlot"], 0, 0);

		nl::node keys_n = src["key"];
		nl::node icons_n = src["icon"];

		map<keyaction, keyaction> reserve;
		for (keyaction k = KA_EQUIPS; k <= KA_EQUIPENHANCE2; k = static_cast<keyaction>(k + 1))
		{
			reserve[k] = k;
		}
		for (keyaction k = KA_PICKUP; k <= KA_JUMP; k = static_cast<keyaction>(k + 1))
		{
			reserve[k] = k;
		}
		for (keyaction k = KA_FACE1; k <= KA_FACE7; k = static_cast<keyaction>(k + 1))
		{
			reserve[k] = k;
		}

		for (map<char, pair<keytype, int>>::iterator keyit = keymap.begin(); keyit != keymap.end(); ++keyit)
		{
			char key = keyit->first;
			keytype type = keyit->second.first;
			int action = keyit->second.second;
			vector2d pos = getkeypos(key);
			texture txt;

			switch (type)
			{
			case KT_ACTION:
			case KT_MENU:
			case KT_FACE:
				reserve.erase(static_cast<keyaction>(action));
				txt = texture(icons_n[to_string(action)]);
				if (txt.isloaded())
				{
					dragicons.push_back(dragicon(txt, key, static_cast<keyaction>(action), texture(keys_n[to_string(keyit->first)]), pos));
				}
				break;
			case KT_CASH:
			case KT_ITEM:
				dragicons.push_back(dragicon(itemicon(action, true, invent->countitem(action)), texture(keys_n[to_string(keyit->first)]), pos));
				break;
			case KT_SKILL:
				dragicons.push_back(dragicon(skillicon(action), texture(keys_n[to_string(keyit->first)]), pos));
				break;
			}
		}

		for (map<keyaction, keyaction>::iterator rsit = reserve.begin(); rsit != reserve.end(); ++rsit)
		{
			dragicons.push_back(dragicon(texture(icons_n[to_string(rsit->first)]), 0, rsit->first, texture(), getreservepos(rsit->first)));
		}

		nl::nx::unview_file("UI");
		app.getimgcache()->unlock();
		position = vector2d(89, 73);
		dimensions = vector2d(622, 374);
		active = true;
	}

	void keyconfig::buttonpressed(short id)
	{
		switch (id)
		{
		case BT_KEYS_CANCEL:
			active = false;
			buttons[BT_KEYS_CANCEL].setstate("normal");
			break;
		case BT_KEYS_OK:

			break;
		case BT_KEYS_CLEAR:
			if (dragicons.size() > 0)
			{
				vector<dragicon> newicons;
				for (vector<dragicon>::iterator drit = dragicons.begin(); drit != dragicons.end(); ++drit)
				{
					switch (drit->gettype())
					{
					case dit_keyconfig:
						drit->setposition(getreservepos(drit->getaction()));
						drit->setkeyicon(texture());
						newicons.push_back(*drit);
						break;
					}
				}
				dragicons = newicons;
			}
			buttons[BT_KEYS_CLEAR].setstate("normal");
			break;
		}
	}

	void keyconfig::sendicon(dragicon* icon, vector2d pos)
	{
		switch (icon->gettype())
		{
		case dit_keyconfig:
			if (pos.y() > position.y() + 265)
			{
				char keybind = icon->getkey();
				if (keybind > -1)
				{
					keymap[keybind] = make_pair(KT_NONE, 0);
					icon->setposition(getreservepos(icon->getaction()));
					icon->setkeyicon(texture());
				}
				icon->resetdrag();

			}
			else
			{
				char keybind = icon->getkey();
				icon->resetdrag();
			}
			break;
		}
	}

	vector2d keyconfig::getkeypos(char key)
	{
		vector2d ret = vector2d();

		if (key >= 2 && key <= 13)
		{
			ret = vector2d((key * 34) - 23, 66);
		}
		else if (key >= 16 && key <= 27)
		{
			ret = vector2d(61 + ((key - 16) * 34), 99);
		}
		else if (key >= 30 && key <= 40)
		{
			ret = vector2d(78 + ((key - 30) * 34), 132);
		}
		else if (key >= 44 && key <= 52)
		{
			ret = vector2d(95 + ((key - 44) * 34), 165);
		}
		else if (key >= 59 && key <= 70)
		{
			ret = vector2d(78 + ((key - 59) * 34) + (((key - 59) / 4) * 8), 28);
		}
		else
		{
			switch (key)
			{
			case 29:
				ret = vector2d(18, 198);
				break;
			case 41:
				ret = vector2d(11, 66);
				break;
			case 42:
				ret = vector2d(35, 165);
				break;
			case 43:
				ret = vector2d(469, 99);
				break;
			case 56:
				ret = vector2d(119, 198);
				break;
			case 57:
				ret = vector2d(225, 198);
				break;
			case 71:
				ret = vector2d(543, 66);
				break;
			case 73:
				ret = vector2d(576, 66);
				break;
			case 79:
				ret = vector2d(543, 99);
				break;
			case 81:
				ret = vector2d(576, 99);
				break;
			case 82:
				ret = vector2d(510, 66);
				break;
			case 83:
				ret = vector2d(510, 99);
				break;
			}
		}

		return ret;
	}

	vector2d keyconfig::getreservepos(keyaction ka)
	{
		vector2d ret = vector2d();

		if (ka >= 0 && ka <= 41)
		{
			ret = vector2d(7 + ((ka % 18) * 34), 269 + ((ka / 18) * 34));
		}
		else if (ka >= 50 && ka <= 54)
		{
			ret = vector2d(7 + (((ka - 8) % 18) * 34), 269 + (((ka - 8) / 18) * 34));
		}
		else if (ka >= 100 && ka <= 106)
		{
			ret = vector2d(7 + (((ka - 53) % 18) * 34), 269 + (((ka - 53) / 18) * 34));
		}

		return ret;
	}
}
