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
#include "worldselect.h"
#include "Journey.h"

namespace io
{
	worldselect::worldselect(char num, vector<char> chl)
	{
		app.getimgcache()->setmode(ict_login);

		node back = nx::nodes["Map"]["Back"]["login.img"]["back"];
		node login = nx::nodes["UI"]["Login.img"];
		node worlds = login["WorldSelect"]["BtWorld"]["release"];
		node channels = login["WorldSelect"]["BtChannel"];

		byte defworld = config.getconfig()->defaultworld;
		byte defch = config.getconfig()->defaultchannel;
		if (defworld > 0)
		{
			defworld = 0;
		}
		if (defch >= num)
		{
			defch = 0;
		}

		sprites.push_back(sprite(animation(back.resolve("11")), vector2d(370, 300)));
		sprites.push_back(sprite(animation(worlds.resolve("layer:bg")), vector2d(650, 45)));
		sprites.push_back(sprite(animation(login.resolve("Common/frame")), vector2d(400, 290)));

		buttons[BT_WORLDSEL0] = button(worlds["button:15"], 650, 20);
		buttons[BT_WORLDSEL0].setstate(BTS_PRESSED);

		sprites.push_back(sprite(animation(worlds["button:16"]["normal"]), vector2d(650, 74)));

		for (char i = 14; i >= 0; i--)
		{
			sprites.push_back(sprite(animation(worlds["button:" + to_string(i)]["normal"]), vector2d(650, 47)));
		}

		sprites.push_back(sprite(animation(channels["layer:bg"]), vector2d(200, 170)));
		sprites.push_back(sprite(animation(channels["release"]["layer:15"]), vector2d(200, 170)));

		for (char i = 0; i < num; i++)
		{
			short buttonid = BT_CHANNELSEL0 + i;

			buttons[buttonid] = button(texture(channels["button:" + to_string(i)]["normal"]["0"]), texture(channels["button:" + to_string(i)]["keyFocused"]["0"]), 200, 170);
			if (i == defch)
			{
				buttons[buttonid].setstate(BTS_PRESSED);
			}
		}

		buttons[BT_GOWORLD] = button(channels["button:GoWorld"], 200, 170);

		chltxt = texture(channels["gauge"]);

		chloads = chl;
		worldid = defworld;
		channelid = defch;

		app.getimgcache()->unlock();
		position = vector2d(0, 0);
		dimensions = vector2d(800, 600);
		active = true;
		dragged = false;
		buttoncd = 0;
	}

	void worldselect::draw()
	{
		uielement::draw();

		if (active)
		{
			int i = 0;
			for (vector<char>::iterator chit = chloads.begin(); chit != chloads.end(); ++chit)
			{
				char chl = *chit;
				if (chl > 100)
				{
					chl = 100;
				}
				else if (chl < 10)
				{
					chl = 10;
				}
				int fill = (chl * chltxt.getdimension().x()) / 100;
				//chltxt.draw(vector2d(228 + (i % 6) * 71, 262 + (i / 6) * 30), vector2d(fill, 0));
				i++;
			}
		}
	}

	void worldselect::buttonpressed(short id)
	{
		if (id >= BT_WORLDSEL0 && id <= BT_WORLDSEL19)
		{
			buttons[BT_WORLDSEL0 + worldid].setstate(BTS_NORMAL);
			worldid = id - BT_WORLDSEL0;
		}
		else if (id >= BT_CHANNELSEL0 && id <= BT_CHANNELSEL16)
		{
			buttons[BT_CHANNELSEL0 + channelid].setstate(BTS_NORMAL);
			channelid = id - BT_CHANNELSEL0;
		}
		else if (id == BT_GOWORLD)
		{
			app.getui()->disableactions();
			app.getui()->getfield()->getlogin()->worldid = worldid;
			app.getui()->getfield()->getlogin()->channelid = channelid;
			config.getconfig()->defaultworld = worldid;
			config.getconfig()->defaultchannel = channelid;
			packet_c.charlrequest(worldid, channelid);
		}
	}
}
