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
#include "loginnotice.h"
#include "Journey.h"

namespace io
{
	loginnotice::loginnotice(char param)
	{
		app.getimgcache()->setmode(ict_login);

		node notice = nl::nx::nodes["UI"]["Login.img"]["Notice"];

		string back;
		switch (param)
		{
		case 16:
			back = "backgrnd/1";
			buttons[BT_LOGINBANOK] = button(notice.resolve("BtYes"), 100, 100);
			break;
		case 22: //This is TOS, TO DO
			break;
		case 93:
			back = "backgrnd/1";
			buttons[BT_LOGINNOTICEOK] = button(notice.resolve("BtYes"), 100, 100);
			break;
		default:
			back = "backgrnd/0";
			buttons[BT_LOGINNOTICEOK] = button(notice.resolve("BtYes"), 100, 100);
		}

		sprites.push_back(sprite(animation(notice.resolve(back)), vector2d()));
		sprites.push_back(sprite(animation(notice.resolve("text/" + to_string(param))), vector2d(17, 13)));

		app.getimgcache()->unlock();
		position = vector2d(292, 200);
		dimensions = vector2d(362, 219);
		type = param;
		active = true;
		dragged = false;
		buttoncd = 0;
	}

	void loginnotice::buttonpressed(short id)
	{
		switch (id)
		{
		case BT_LOGINBANOK:
			quit();
			return;
		case BT_LOGINNOTICEOK:
			uielement* login = app.getui()->getelement(UI_LOGIN);
			if (login)
			{
				login->setbutton(BT_LOGIN, BTS_NORMAL);
			}
			active = false;
			return;
		}
	}
}
