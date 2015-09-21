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
#include "login.h"
#include "Journey.h"

namespace io
{
	login::login()
	{
		app.getimgcache()->setmode(ict_login);
		nl::nx::view_file("UI");

		node title = nl::nx::nodes["UI"]["Login.img"]["Title"];
		node common = nl::nx::nodes["UI"]["Login.img"]["Common"];

		sprites.push_back(sprite(animation(title["11"]), vector2d(410, 300)));
		sprites.push_back(sprite(animation(title["35"]), vector2d(410, 260)));
		sprites.push_back(sprite(animation(title["Logo"]), vector2d(410, 130)));
		sprites.push_back(sprite(animation(title["signboard"]), vector2d(410, 300)));
		sprites.push_back(sprite(animation(common["frame"]), vector2d(400, 290)));

		buttons[BT_LOGIN] = button(title["BtLogin"], 475, 248);
		buttons[BT_NEW] = button(title["BtNew"], 309, 320);
		buttons[BT_HOMEPAGE] = button(title["BtHomePage"], 382, 320);
		buttons[BT_PWDLOST] = button(title["BtPasswdLost"], 470, 300);
		buttons[BT_QUIT] = button(title["BtQuit"], 455, 320);
		buttons[BT_LOGINLOST] = button(title["BtLoginIDLost"], 395, 300);
		buttons[BT_SAVEID] = button(title["BtLoginIDSave"], 325, 300);

		string defaultacc = config.getdefaultacc();
		saveid = config.getsaveid();

		saveidcheck[false] = texture(title["check"]["0"]);
		saveidcheck[true] = texture(title["check"]["1"]);

		textfields[TXT_ACC] = textfield(TXT_ACC, DWF_14L, TXC_WHITE, defaultacc, vector2d(315, 249), 12);
		textfields[TXT_ACC].setbg(texture(title["ID"]), -5, 0);

		textfields[TXT_PASS] = textfield(TXT_PASS, DWF_14L, TXC_WHITE, "", vector2d(315, 275), 12);
		textfields[TXT_PASS].setbg(texture(title["PW"]), -5, 0);

		if (saveid)
		{
			textfields[TXT_PASS].setfocus(true);
			app.getui()->settextfield(&textfields[TXT_PASS]);
		}
		else
		{
			textfields[TXT_ACC].setfocus(true);
			app.getui()->settextfield(&textfields[TXT_ACC]);
		}

		nl::nx::unview_file("UI");
		app.getimgcache()->unlock();
		position = vector2d(0, 0);
		dimensions = vector2d(800, 600);
		active = true;
		dragged = false;
		buttoncd = 0;
	}

	void login::draw(ID2D1HwndRenderTarget* target)
	{
		uielement::draw(target);

		if (active)
		{
			saveidcheck[saveid].draw(position + vector2d(313, 304));
		}
	}

	void login::buttonpressed(short id)
	{
		switch (id)
		{
		case BT_LOGIN:
			app.getui()->disableactions();
			app.getui()->settextfield(0);
			textfields[TXT_ACC].setfocus(false);
			textfields[TXT_PASS].setfocus(false);
			app.getui()->add(UI_LOGINWAIT);
			packet_c.c_login(textfields[TXT_ACC].text(), textfields[TXT_PASS].text());
			return;
		case BT_QUIT:
			quit();
			return;
		case BT_SAVEID:
			saveid = !saveid;
			config.setsaveid(saveid);
			buttons[BT_SAVEID].setstate("mouseOver");
			return;
		}
	}
}
