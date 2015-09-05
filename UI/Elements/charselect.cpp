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
	charselect::charselect(char cslots, vector<maplechar>* chars)
	{
		app.getimgcache()->setmode(ict_login);
		nl::nx::view_file("UI");

		node login = nl::nx::nodes["UI"].resolve("Login.img");
		node charsel = login.resolve("CharSelect");

		size_t charcount = chars->size();

		sprites.push_back(sprite(animation(login.resolve("Title/worldsel")), vector2d()));
		sprites.push_back(sprite(animation(login.resolve("Common/frame")), vector2d(400, 290)));
		sprites.push_back(sprite(animation(login.resolve("Common/selectWorld")), vector2d(580, 42)));
		sprites.push_back(sprite(animation(charsel.resolve("selectedWorld/icon/15")), vector2d(580, 42)));
		sprites.push_back(sprite(animation(charsel.resolve("selectedWorld/name/15")), vector2d(580, 42)));
		sprites.push_back(sprite(animation(charsel.resolve("selectedWorld/ch/" + to_string(app.getui()->getfield()->getchannel()))), vector2d(580, 42)));
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
			buttons[BT_PAGEL].setstate("disabled");
			buttons[BT_PAGER].setstate("disabled");
		}

		size_t createcount = min(cslots, 8);

		for (size_t i = chars->size(); i < createcount; i++)
		{
			sprites.push_back(sprite(animation(charsel.resolve("buyCharacter")), vector2d(130 + (120 * (i % 4)), 250 + (200 * (i > 3)))));
		}

		node nametagnode = charsel["nameTag"];
		pair<vector<texture>, vector<texture>> nttextures;
		nttextures.first.push_back(texture(nametagnode.resolve("0/0")));
		nttextures.first.push_back(texture(nametagnode.resolve("0/1")));
		nttextures.first.push_back(texture(nametagnode.resolve("0/2")));
		nttextures.second.push_back(texture(nametagnode.resolve("1/0")));
		nttextures.second.push_back(texture(nametagnode.resolve("1/1")));
		nttextures.second.push_back(texture(nametagnode.resolve("1/2")));

		size_t charbtcount = min(charcount, 8);

		for (size_t i = 0; i < charbtcount; i++)
		{
			nametag charname = nametag(app.getfonts()->getfont(DWF_CENTER), txc_white, nttextures, chars->at(i).getstats()->getname(), vector2d(55 + (120 * (i % 4)), 250 + (200 * (i > 3))), (i == 0));
			nametags.push_back(charname);
			buttons.insert(make_pair(BT_CHAR0 + i, button(105 + (120 * (i % 4)), 170 + (200 * (i > 3)), 50, 80)));
			buttons[BT_CHAR0].setstate("pressed");
		}

		app.getimgcache()->unlock();
		app.getimgcache()->setmode(ict_sys);

		lvset = charset(charsel.resolve("lv"));
		statset = charset(nl::nx::nodes["UI"].resolve("StatusBar2.img/mainBar/gauge/number"));

		rankmove['+'] = texture(charsel["icon"]["up"]);
		rankmove['='] = texture(charsel["icon"]["same"]);
		rankmove['-'] = texture(charsel["icon"]["down"]);

		nl::nx::unview_file("UI");
		nl::nx::view_file("Character");

		selected = config.getdefchar();
		page = selected % 8;

		for (size_t i = 0; i < chars->size(); i++)
		{
			maplelook* plook = chars->at(i).getlook();
			app.getlookfactory()->loadcharlook(plook);

			maplelook look = chars->at(i).copylook();
			look.setposition(vector2d(130 + (120 * (i % 4)), 250 + (200 * (i > 3))));
			look.setfleft(false);
			if (i == selected)
			{
				look.setstate("walk1");
			}
			looks.push_back(look);
			stats.push_back(chars->at(i).copystats());
			rankinfo.push_back(make_pair(chars->at(i).getrank(), chars->at(i).getjobrank()));
		}

		nl::nx::unview_file("Character");
		app.getimgcache()->unlock();

		name = textlabel(app.getfonts()->getfont(DWF_LARGE), txc_white, stats[selected].getname());
		job = textlabel(app.getfonts()->getfont(dwf_small_r), txc_white, stats[selected].getjobname());

		position = vector2d(0, 0);
		dimensions = vector2d(800, 600);
		active = true;
	}

	void charselect::draw(ID2D1HwndRenderTarget* target)
	{
		uielement::draw(target);

		if (active)
		{
			for (vector<maplelook>::iterator itspr = looks.begin(); itspr != looks.end(); itspr++)
			{
				itspr->draw(target, position);
			}
			for (vector<nametag>::iterator itspr = nametags.begin(); itspr != nametags.end(); itspr++)
			{
				itspr->draw(target, position);
			}

			name.draw(target, vector2d(664, 270));
			job.draw(target, vector2d(732, 305));

			statset.draw(to_string(rankinfo[selected].first.first), cha_right, vector2d(732, 335));
			statset.draw(to_string(rankinfo[selected].second.first), cha_right, vector2d(732, 355));

			lvset.draw('l', vector2d(648, 262));
			lvset.draw(to_string(stats[selected].getstat(LEVEL)), 12, cha_left, vector2d(655, 262));

			statset.draw(to_string(stats[selected].getstat(STR)), cha_right, vector2d(655, 385));
			statset.draw(to_string(stats[selected].getstat(DEX)), cha_right, vector2d(655, 407));
			statset.draw(to_string(stats[selected].getstat(INT_)), cha_right, vector2d(732, 385));
			statset.draw(to_string(stats[selected].getstat(LUK)), cha_right, vector2d(732, 407));
		}
	}

	void charselect::update()
	{
		uielement::update();

		if (active)
		{
			for (vector<maplelook>::iterator itspr = looks.begin(); itspr != looks.end(); itspr++)
			{
				itspr->update();
			}
		}
	}

	void charselect::buttonpressed(short id)
	{
		if (id >= BT_CHAR0 && id <= BT_CHAR7)
		{
			selected = id - BT_CHAR0;
			looks[selected].setstate("walk1");
			nametags[selected].setstate(true);
			name.settext(stats[selected].getname());
			job.settext(stats[selected].getjobname());

			for (map<short, button>::iterator itbt = buttons.begin(); itbt != buttons.end(); itbt++)
			{
				if (itbt->first != id && itbt->first >= BT_CHAR0 && itbt->first <= BT_CHAR7 && itbt->second.getstate() == "pressed")
				{
					char deselected = itbt->first - BT_CHAR0;
					itbt->second.setstate("normal");
					looks[deselected].setstate("stand1");
					nametags[deselected].setstate(false);
				}
			}
			return;
		}

		int cid = stats[selected].getid();

		switch (id)
		{
		case BT_DELCHAR:
			packet_c.deletechar("2705", cid);
			break;
		case BT_SELCHAR:
			app.getui()->disableactions();
			app.getui()->getfield()->getaccount()->selectchar(cid);
			packet_c.selectchar(cid);
			break;
		case BT_PAGEL:
		case BT_PAGER:
			buttons[id].setstate("mouseOver");
			break;
		case BT_NEWCHAR:
			active = false;
			app.getui()->add(UI_CREATECHAR);
			break;
		}
	}
}
