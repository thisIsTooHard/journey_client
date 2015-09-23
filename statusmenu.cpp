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
#include "statusmenu.h"
#include "Journey.h"

namespace io
{
	statusmenu::statusmenu()
	{
		app.getimgcache()->setmode(ict_sys);
		nl::nx::view_file("UI");

		node source = nl::nx::nodes["UI"]["StatusBar2.img"]["mainBar"]["System"];

		sprites.push_back(sprite(animation(source["backgrnd"]["0"]), vector2d(0, 0)));
		backfill = texture(source["backgrnd"]["1"]);
		sprites.push_back(sprite(animation(source["backgrnd"]["2"]), vector2d(0, 150)));

		buttons[BT_CHANGECH] = button(source["BtChannel"], 8, 20);
		buttons[BT_KEYCONFIG] = button(source["BtKeySetting"], 8, 46);
		buttons[BT_JOYPAD] = button(source["BtJoyPad"], 8, 72);
		buttons[BT_OPTIONS] = button(source["BtSystemOption"], 8, 98);
		buttons[BT_GOPTIONS] = button(source["BtGameOption"], 8, 124);
		buttons[BT_QUITGAME] = button(source["BtGameQuit"], 8, 150);

		nl::nx::unview_file("UI");
		app.getimgcache()->unlock();
		position = vector2d(721, 366);
		dimensions = vector2d(79, 176);
		active = true;
		dragged = false;
		buttoncd = 0;
	}

	void statusmenu::draw()
	{
		if (active)
		{
			backfill.draw(position + vector2d(0, 34), vector2d(0, 116));

			uielement::draw();
		}
	}

	void statusmenu::buttonpressed(short id)
	{
		switch (id)
		{
		case BT_QUITGAME:
			quit();
			break;
		case BT_KEYCONFIG:
			active = false;
			app.getui()->add(UI_KEYCONFIG);
			break;
		}
		buttons[id].setstate("mouseOver");
	}
}
