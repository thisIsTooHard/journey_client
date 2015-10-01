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
#include "charselect.h"
#include "Journey.h"

namespace io
{
	charselect::charselect(account* acc)
	{
		app.getimgcache()->setmode(ict_login);

		node login = nl::nx::nodes["UI"].resolve("Login.img");
		node charsel = login.resolve("CharSelect");

		char cslots = acc->getslots();
		size_t charcount = acc->getchars()->size();

		for (size_t i = 0; i < charcount; i++)
		{
			chars.push_back(acc->getchar(i));
		}

		sprites.push_back(sprite(animation(login.resolve("Title/worldsel")), vector2d()));
		sprites.push_back(sprite(animation(login.resolve("Common/frame")), vector2d(400, 290)));
		sprites.push_back(sprite(animation(login.resolve("Common/selectWorld")), vector2d(580, 42)));
		sprites.push_back(sprite(animation(charsel.resolve("selectedWorld/icon/15")), vector2d(580, 42)));
		sprites.push_back(sprite(animation(charsel.resolve("selectedWorld/name/15")), vector2d(580, 42)));
		sprites.push_back(sprite(animation(charsel.resolve("selectedWorld/ch/" + to_string(app.getui()->getfield()->getlogin()->channelid))), vector2d(580, 42)));
		sprites.push_back(sprite(animation(charsel.resolve("charInfo")), vector2d(662, 355)));

		buttons.insert(make_pair(BT_ARBEIT, button(charsel.resolve("arbeit"), 580, 115)));
		buttons.insert(make_pair(BT_CHARCARD, button(charsel.resolve("characterCard"), 665, 115)));
		buttons.insert(make_pair(BT_NEWCHAR, button(charsel.resolve("BtNew"), 200, 495)));
		buttons.insert(make_pair(BT_DELCHAR, button(charsel.resolve("BtDelete"), 320, 495)));
		buttons.insert(make_pair(BT_SELCHAR, button(charsel.resolve("BtSelect"), 586, 427)));

		buttons.insert(make_pair(BT_PAGEL, button(charsel["pageL"], 100, 490)));
		buttons.insert(make_pair(BT_PAGER, button(charsel["pageR"], 490, 490)));

		if (charcount + cslots < 9)
		{
			buttons[BT_PAGEL].setstate(BTS_DISABLED);
			buttons[BT_PAGER].setstate(BTS_DISABLED);
		}

		size_t createcount = cslots;
		if (createcount > 8)
		{
			createcount = 8;
		}

		for (size_t i = charcount; i < createcount; i++)
		{
			sprites.push_back(sprite(animation(charsel["buyCharacter"]), vector2d(130 + (120 * (i % 4)), 250 + (200 * (i > 3)))));
		}

		map<bool, vector<texture>> nttextures;
		nttextures[false].push_back(texture(charsel["nameTag"]["0"]["0"]));
		nttextures[false].push_back(texture(charsel["nameTag"]["0"]["1"]));
		nttextures[false].push_back(texture(charsel["nameTag"]["0"]["2"]));
		nttextures[true].push_back(texture(charsel["nameTag"]["1"]["0"]));
		nttextures[true].push_back(texture(charsel["nameTag"]["1"]["1"]));
		nttextures[true].push_back(texture(charsel["nameTag"]["1"]["2"]));

		size_t charbtcount = charcount;
		if (charbtcount > 8)
		{
			charbtcount = 8;
		}

		selected = config.getconfig()->defaultchar;
		if (selected >= charcount)
		{
			selected = 0;
		}
		page = selected % 8;

		for (size_t i = 0; i < charbtcount; i++)
		{
			nametags.push_back(nametag(DWF_14C, TXC_WHITE, nttextures, chars[i]->getstats()->getname(), vector2d(133 + (120 * (i % 4)), 250 + (200 * (i > 3))), (i == selected)));
			buttons[BT_CHAR0 + i] = button(vector2d(105 + (120 * (i % 4)), 170 + (200 * (i > 3))), vector2d(50, 80));
		}
		buttons[BT_CHAR0 + selected].setstate(BTS_PRESSED);

		app.getimgcache()->unlock();
		app.getimgcache()->setmode(ict_sys);

		lvset = charset(charsel["lv"]);
		statset = charset(nx::nodes["UI"]["StatusBar2.img"]["mainBar"]["gauge"]["number"]);

		app.getimgcache()->unlock();

		size_t displaycount = charcount;
		if (displaycount > 8)
		{
			displaycount = 8;
		}

		for (size_t i = 0; i < displaycount; i++)
		{
			maplelook* look = chars[i]->getlook();
			cache.getequips()->loadcharlook(look);
			look->setposition(vector2d(130 + (120 * (i % 4)), 250 + (200 * (i > 3))));
			look->setfleft(false);
			if (i == selected)
			{
				look->setstate("walk");
			}
		}

		if (chars.size() > 0)
		{
			maplestats* stats = chars[selected]->getstats();
			name = textlabel(DWF_20C, TXC_WHITE, stats->getname());
			job = textlabel(DWF_12R, TXC_WHITE, stats->getjobname());
		}

		pic = acc->getpic();

		position = vector2d(0, 0);
		dimensions = vector2d(800, 600);
		active = true;
		dragged = false;
		buttoncd = 0;
	}

	void charselect::draw()
	{
		uielement::draw();

		if (active)
		{
			for (vector<maplechar*>::iterator chit = chars.begin(); chit != chars.end(); ++chit)
			{
				(*chit)->getlook()->draw(position);
			}
			for (vector<nametag>::iterator ntit = nametags.begin(); ntit != nametags.end(); ++ntit)
			{
				ntit->draw(position);
			}

			if (chars.size() > 0)
			{
				maplestats* stats = chars[selected]->getstats();

				name.draw(stats->getname(), vector2d(664, 268));
				job.draw(stats->getjobname(), vector2d(732, 305));

				statset.draw(to_string(chars[selected]->getrank().first), cha_right, vector2d(732, 335));
				statset.draw(to_string(chars[selected]->getjobrank().first), cha_right, vector2d(732, 355));

				int lvx = lvset.draw(to_string(stats->getstat(MS_LEVEL)), cha_center, vector2d(685, 262));
				lvset.draw('l', vector2d(655 - lvx/2, 262));

				statset.draw(to_string(stats->getstat(MS_STR)), cha_right, vector2d(655, 385));
				statset.draw(to_string(stats->getstat(MS_DEX)), cha_right, vector2d(655, 407));
				statset.draw(to_string(stats->getstat(MS_INT)), cha_right, vector2d(732, 385));
				statset.draw(to_string(stats->getstat(MS_LUK)), cha_right, vector2d(732, 407));
			}
		}
	}

	void charselect::update()
	{
		uielement::update();

		if (active)
		{
			for (vector<maplechar*>::iterator chit = chars.begin(); chit != chars.end(); ++chit)
			{
				(*chit)->getlook()->update();
			}
		}
	}

	void charselect::buttonpressed(short id)
	{
		if (id >= BT_CHAR0 && id <= BT_CHAR7)
		{
			buttons[BT_CHAR0 + selected].setstate(BTS_NORMAL);
			chars[selected]->getlook()->setstate("stand");
			nametags[selected].setstate(false);

			selected = id - BT_CHAR0;
			buttons[id].setstate(BTS_PRESSED);
			chars[selected]->getlook()->setstate("walk");
			nametags[selected].setstate(true);
			return;
		}

		int cid = (chars.size() > 0) ? chars[selected]->getstats()->getid() : -1;

		switch (id)
		{
		case BT_DELCHAR:
			if (cid != -1)
			{
				packet_c.deletechar("2705", cid);
			}
			break;
		case BT_SELCHAR:
			if (cid != -1)
			{
				logininfo* login = app.getui()->getfield()->getlogin();
				login->charid = cid;
				login->getacc()->selectchar(cid);
				config.getconfig()->defaultchar = selected;
				switch (pic)
				{
				case 0:
					buttons[id].setstate(BTS_MOUSEOVER);
					app.getui()->add(UI_SOFTKEYBOARD, 0);
					break;
				case 1:
					buttons[id].setstate(BTS_MOUSEOVER);
					app.getui()->add(UI_SOFTKEYBOARD, 1);
					break;
				case 2:
					app.getui()->disableactions();
					packet_c.selectchar(cid);
					break;
				}
			}
			else
			{
				buttons[id].setstate(BTS_MOUSEOVER);
			}
			break;
		case BT_PAGEL:
		case BT_PAGER:
			buttons[id].setstate(BTS_MOUSEOVER);
			break;
		case BT_NEWCHAR:
			active = false;
			app.getui()->add(UI_CREATECHAR);
			break;
		}
	}
}
