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
#include "charcreation.h"
#include "Journey.h"

namespace io
{
	charcreation::charcreation(bool fem)
	{
		app.getimgcache()->setmode(ict_login);

		nl::node src = nl::nx::nodes["UI"]["Login.img"];
		nl::node crsrc = src["NewChar"];
		nl::node bgsrc = nl::nx::nodes["Map"]["Back"]["login.img"]["back"];

		sky = texture(bgsrc["2"]);
		cloud = texture(bgsrc["27"]);

		sprites.push_back(sprite(animation(bgsrc["15"]), vector2d(153, 685)));
		sprites.push_back(sprite(animation(bgsrc["16"]), vector2d(200, 400)));
		sprites.push_back(sprite(animation(bgsrc["17"]), vector2d(160, 263)));
		sprites.push_back(sprite(animation(bgsrc["18"]), vector2d(349, 1220)));
		sprites.push_back(sprite(animation(src["Common"]["frame"]), vector2d(400, 290)));

		nameboard = sprite(animation(crsrc["charName"]), vector2d(455, 115));

		lookboard.push_back(sprite(animation(crsrc["charSet"]), vector2d(450, 115)));
		lookboard.push_back(sprite(animation(crsrc["avatarSel"]["0"]["normal"]), vector2d(461, 217)));
		lookboard.push_back(sprite(animation(crsrc["avatarSel"]["1"]["normal"]), vector2d(461, 236)));
		lookboard.push_back(sprite(animation(crsrc["avatarSel"]["2"]["normal"]), vector2d(461, 255)));
		lookboard.push_back(sprite(animation(crsrc["avatarSel"]["3"]["normal"]), vector2d(461, 274)));
		lookboard.push_back(sprite(animation(crsrc["avatarSel"]["4"]["normal"]), vector2d(461, 293)));
		lookboard.push_back(sprite(animation(crsrc["avatarSel"]["5"]["normal"]), vector2d(461, 312)));
		lookboard.push_back(sprite(animation(crsrc["avatarSel"]["6"]["normal"]), vector2d(461, 331)));
		lookboard.push_back(sprite(animation(crsrc["avatarSel"]["7"]["normal"]), vector2d(461, 350)));
		lookboard.push_back(sprite(animation(crsrc["avatarSel"]["8"]["normal"]), vector2d(461, 369)));

		buttons[BT_CHARC_OK] = button(crsrc["BtYes"], 482, 292);
		buttons[BT_CHARC_CANCEL] = button(crsrc["BtNo"], 555, 292);

		buttons[BT_CHARC_FACEL] = button(crsrc["BtLeft"], 521, 216);
		buttons[BT_CHARC_FACER] = button(crsrc["BtRight"], 645, 216);
		buttons[BT_CHARC_HAIRL] = button(crsrc["BtLeft"], 521, 235);
		buttons[BT_CHARC_HAIRR] = button(crsrc["BtRight"], 645, 235);
		buttons[BT_CHARC_HAIRCL] = button(crsrc["BtLeft"], 521, 254);
		buttons[BT_CHARC_HAIRCR] = button(crsrc["BtRight"], 645, 254);
		buttons[BT_CHARC_SKINL] = button(crsrc["BtLeft"], 521, 273);
		buttons[BT_CHARC_SKINR] = button(crsrc["BtRight"], 645, 273);
		buttons[BT_CHARC_TOPL] = button(crsrc["BtLeft"], 521, 292);
		buttons[BT_CHARC_TOPR] = button(crsrc["BtRight"], 645, 292);
		buttons[BT_CHARC_BOTL] = button(crsrc["BtLeft"], 521, 311);
		buttons[BT_CHARC_BOTR] = button(crsrc["BtRight"], 645, 311);
		buttons[BT_CHARC_SHOESL] = button(crsrc["BtLeft"], 521, 330);
		buttons[BT_CHARC_SHOESR] = button(crsrc["BtRight"], 645, 330);
		buttons[BT_CHARC_WEPL] = button(crsrc["BtLeft"], 521, 349);
		buttons[BT_CHARC_WEPR] = button(crsrc["BtRight"], 645, 348);
		buttons[BT_CHARC_GENDERL] = button(crsrc["BtLeft"], 521, 368);
		buttons[BT_CHARC_GEMDERR] = button(crsrc["BtRight"], 645, 368);
		buttons[BT_CHARC_FACEL].setactive(false);
		buttons[BT_CHARC_FACER].setactive(false);
		buttons[BT_CHARC_HAIRL].setactive(false);
		buttons[BT_CHARC_HAIRR].setactive(false);
		buttons[BT_CHARC_HAIRCL].setactive(false);
		buttons[BT_CHARC_HAIRCR].setactive(false);
		buttons[BT_CHARC_SKINL].setactive(false);
		buttons[BT_CHARC_SKINR].setactive(false);
		buttons[BT_CHARC_TOPL].setactive(false);
		buttons[BT_CHARC_TOPR].setactive(false);
		buttons[BT_CHARC_BOTL].setactive(false);
		buttons[BT_CHARC_BOTR].setactive(false);
		buttons[BT_CHARC_SHOESL].setactive(false);
		buttons[BT_CHARC_SHOESR].setactive(false);
		buttons[BT_CHARC_WEPL].setactive(false);
		buttons[BT_CHARC_WEPR].setactive(false);
		buttons[BT_CHARC_GENDERL].setactive(false);
		buttons[BT_CHARC_GEMDERR].setactive(false);

		textfields[TXT_NAMECHAR] = textfield(TXT_NAMECHAR, DWF_14L, TXC_WHITE, "", vector2d(490, 217), 12);
		textfields[TXT_NAMECHAR].setfocus(true);
		app.getui()->settextfield(&textfields[TXT_NAMECHAR]);

		setlabel = textlabel(DWF_12C, TXC_BLACK, "");

		app.getimgcache()->unlock();

		nl::node mkinfo = nl::nx::nodes["Etc"]["MakeCharInfo.img"]["Info"];

		for (char i = 0; i < 2; i++)
		{
			bool f;
			nl::node mk_n;
			if (i == 0)
			{
				f = true;
				mk_n = mkinfo["CharFemale"];
			}
			else
			{
				f = false;
				mk_n = mkinfo["CharMale"];
			}

			for (nl::node subnode = mk_n.begin(); subnode != mk_n.end(); ++subnode)
			{
				int num = stoi(subnode.name());
				for (nl::node idnode = subnode.begin(); idnode != subnode.end(); ++idnode)
				{
					int value = idnode;
					switch (num)
					{
					case 0:
						faces[f].push_back(value);
						break;
					case 1:
						hairs[f].push_back(value);
						break;
					case 2:
						haircolors[f].push_back(static_cast<char>(value));
						break;
					case 3:
						skins[f].push_back(static_cast<char>(value));
						break;
					case 4:
						tops[f].push_back(value);
						break;
					case 5:
						bots[f].push_back(value);
						break;
					case 6:
						shoes[f].push_back(value);
						break;
					case 7:
						weapons[f].push_back(value);
						break;
					}
				}
			}
		}

		random_device rd;
		default_random_engine e1(rd());

		female = fem;

		uniform_int_distribution<size_t> hair_d(0, hairs[female].size() - 1);
		hair = hair_d(e1);
		uniform_int_distribution<size_t> face_d(0, faces[female].size() - 1);
		face = face_d(e1);
		uniform_int_distribution<size_t> skin_d(0, skins[female].size() - 1);
		skin = skin_d(e1);
		uniform_int_distribution<size_t> hairc_d(0, haircolors[female].size() - 1);
		haircolor = hairc_d(e1);
		uniform_int_distribution<size_t> top_d(0, tops[female].size() - 1);
		top = top_d(e1);
		uniform_int_distribution<size_t> bot_d(0, bots[female].size() - 1);
		bot = bot_d(e1);
		uniform_int_distribution<size_t> shoe_d(0, shoes[female].size() - 1);
		shoe = shoe_d(e1);
		uniform_int_distribution<size_t> weapon_d(0, weapons[female].size() - 1);
		weapon = weapon_d(e1);

		lookinfo info;

		info.female = female;
		info.skin = skins[female][skin];
		info.faceid = faces[female][face];
		info.hairid = hairs[female][hair] + haircolors[female][haircolor];
		info.equips[0] = tops[female][top];
		info.equips[1] = bots[female][bot];
		info.equips[2] = shoes[female][shoe];
		info.equips[3] = weapons[female][weapon];
		info.maskedequips = map<char, int>();
		info.petids = vector<int>();

		app.getimgcache()->setmode(ict_sys);

		newchar = maplelook(info);
		newchar.setposition(vector2d(360, 348));
		newchar.setfleft(false);
		cache.getequips()->loadcharlook(&newchar);

		app.getimgcache()->unlock();
		position = vector2d(0, 0);
		dimensions = vector2d(800, 600);
		active = true;
		dragged = false;
		buttoncd = 0;
		cloudfx = 200.0f;
		name = "";
	}

	void charcreation::buttonpressed(short id)
	{
		switch (id)
		{
		case BT_CHARC_OK:
			if (named)
			{
				app.getui()->disableactions();
				packet_c.createchar(name, 1, faces[female][face], hairs[female][hair], haircolors[female][haircolor], skins[female][skin], tops[female][top], bots[female][bot], shoes[female][shoe], weapons[female][weapon], female);
			}
			else
			{
				name = textfields[TXT_NAMECHAR].text();
				if (name.size() >= 4)
				{
					app.getui()->disableactions();
					app.getui()->settextfield(0);
					textfields[TXT_NAMECHAR].setfocus(false);
					packet_c.checkcharname(name);
				}
				else
				{
					app.getui()->add(UI_LOGINNOTICE, 10);
					buttons[id].setstate("normal");
				}
			}
			break;
		case BT_CHARC_CANCEL:
			if (named)
			{
				buttons[BT_CHARC_OK].setposition(vector2d(482, 292));
				buttons[BT_CHARC_CANCEL].setposition(vector2d(555, 292));
				buttons[BT_CHARC_FACEL].setactive(false);
				buttons[BT_CHARC_FACER].setactive(false);
				buttons[BT_CHARC_HAIRL].setactive(false);
				buttons[BT_CHARC_HAIRR].setactive(false);
				buttons[BT_CHARC_HAIRCL].setactive(false);
				buttons[BT_CHARC_HAIRCR].setactive(false);
				buttons[BT_CHARC_SKINL].setactive(false);
				buttons[BT_CHARC_SKINR].setactive(false);
				buttons[BT_CHARC_TOPL].setactive(false);
				buttons[BT_CHARC_TOPR].setactive(false);
				buttons[BT_CHARC_BOTL].setactive(false);
				buttons[BT_CHARC_BOTR].setactive(false);
				buttons[BT_CHARC_SHOESL].setactive(false);
				buttons[BT_CHARC_SHOESR].setactive(false);
				buttons[BT_CHARC_WEPL].setactive(false);
				buttons[BT_CHARC_WEPR].setactive(false);
				buttons[BT_CHARC_GENDERL].setactive(false);
				buttons[BT_CHARC_GEMDERR].setactive(false);
				buttons[BT_CHARC_CANCEL].setstate("normal");
				textfields[TXT_NAMECHAR].setactive(true);
				named = false;
			}
			else
			{
				active = false;
				app.getui()->settextfield(0);
				app.getui()->remove(UI_CHARSEL);
				app.getui()->add(UI_CHARSEL);
			}
			break;
		}

		if (id >= BT_CHARC_FACEL && id <= BT_CHARC_GEMDERR)
		{
			app.getimgcache()->setmode(ict_sys);
			switch (id)
			{
			case BT_CHARC_FACEL:
				face = (face > 0) ? face - 1 : faces[female].size() - 1;
				newchar.setface(cache.getequips()->getface(faces[female][face]));
				break;
			case BT_CHARC_FACER:
				face = (face < faces[female].size() - 1) ? face + 1 : 0;
				newchar.setface(cache.getequips()->getface(faces[female][face]));
				break;
			case BT_CHARC_HAIRL:
				hair = (hair > 0) ? hair - 1 : hairs[female].size() - 1;
				newchar.sethair(cache.getequips()->gethair(hairs[female][hair] + haircolors[female][haircolor]));
				break;
			case BT_CHARC_HAIRR:
				hair = (hair < hairs[female].size() - 1) ? hair + 1 : 0;
				newchar.sethair(cache.getequips()->gethair(hairs[female][hair] + haircolors[female][haircolor]));
				break;
			case BT_CHARC_HAIRCL:
				haircolor = (haircolor > 0) ? haircolor - 1 : haircolors[female].size() - 1;
				newchar.sethair(cache.getequips()->gethair(hairs[female][hair] + haircolors[female][haircolor]));
				break;
			case BT_CHARC_HAIRCR:
				haircolor = (haircolor < haircolors[female].size() - 1) ? haircolor + 1 : 0;
				newchar.sethair(cache.getequips()->gethair(hairs[female][hair] + haircolors[female][haircolor]));
				break;
			case BT_CHARC_SKINL:
				skin = (skin > 0) ? skin - 1 : skins[female].size() - 1;
				newchar.setbody(cache.getequips()->getbody(skins[female][skin]));
				break;
			case BT_CHARC_SKINR:
				skin = (skin < skins[female].size() - 1) ? skin + 1 : 0;
				newchar.setbody(cache.getequips()->getbody(skins[female][skin]));
				break;
			case BT_CHARC_TOPL:
				top = (top > 0) ? top - 1 : tops[female].size() - 1;
				newchar.addcloth(cache.getequips()->getcloth(tops[female][top]));
				break;
			case BT_CHARC_TOPR:
				top = (top < tops[female].size() - 1) ? top + 1 : 0;
				newchar.addcloth(cache.getequips()->getcloth(tops[female][top]));
				break;
			case BT_CHARC_BOTL:
				bot = (bot > 0) ? bot - 1 : bots[female].size() - 1;
				newchar.addcloth(cache.getequips()->getcloth(bots[female][bot]));
				break;
			case BT_CHARC_BOTR:
				bot = (bot < bots[female].size() - 1) ? bot + 1 : 0;
				newchar.addcloth(cache.getequips()->getcloth(bots[female][bot]));
				break;
			case BT_CHARC_SHOESL:
				shoe = (shoe > 0) ? shoe - 1 : shoes[female].size() - 1;
				newchar.addcloth(cache.getequips()->getcloth(shoes[female][shoe]));
				break;
			case BT_CHARC_SHOESR:
				shoe = (shoe < shoes[female].size() - 1) ? shoe + 1 : 0;
				newchar.addcloth(cache.getequips()->getcloth(shoes[female][shoe]));
				break;
			case BT_CHARC_WEPL:
				weapon = (weapon > 0) ? weapon - 1 : weapons[female].size() - 1;
				newchar.addcloth(cache.getequips()->getcloth(weapons[female][weapon]));
				break;
			case BT_CHARC_WEPR:
				weapon = (weapon < weapons[female].size() - 1) ? weapon + 1 : 0;
				newchar.addcloth(cache.getequips()->getcloth(weapons[female][weapon]));
				break;
			case BT_CHARC_GENDERL:
			case BT_CHARC_GEMDERR:
				female = !female;

				random_device rd;
				default_random_engine e1(rd());

				uniform_int_distribution<size_t> hair_d(0, hairs[female].size() - 1);
				hair = hair_d(e1);
				uniform_int_distribution<size_t> face_d(0, faces[female].size() - 1);
				face = face_d(e1);
				uniform_int_distribution<size_t> skin_d(0, skins[female].size() - 1);
				skin = skin_d(e1);
				uniform_int_distribution<size_t> hairc_d(0, haircolors[female].size() - 1);
				haircolor = hairc_d(e1);
				uniform_int_distribution<size_t> top_d(0, tops[female].size() - 1);
				top = top_d(e1);
				uniform_int_distribution<size_t> bot_d(0, bots[female].size() - 1);
				bot = bot_d(e1);
				uniform_int_distribution<size_t> shoe_d(0, shoes[female].size() - 1);
				shoe = shoe_d(e1);
				uniform_int_distribution<size_t> weapon_d(0, weapons[female].size() - 1);
				weapon = weapon_d(e1);

				newchar.setbody(cache.getequips()->getbody(skins[female][skin]));
				newchar.setface(cache.getequips()->getface(faces[female][face]));
				newchar.sethair(cache.getequips()->gethair(hairs[female][hair] + haircolors[female][haircolor]));
				newchar.addcloth(cache.getequips()->getcloth(tops[female][top]));
				newchar.addcloth(cache.getequips()->getcloth(bots[female][bot]));
				newchar.addcloth(cache.getequips()->getcloth(shoes[female][shoe]));
				newchar.addcloth(cache.getequips()->getcloth(weapons[female][weapon]));
				break;
			}
			app.getimgcache()->unlock();
			buttons[id].setstate("mouseOver");
		}
	}

	void charcreation::sendbool(bool nameused)
	{
		if (!named)
		{
			if (nameused)
			{
				name = "";
			}
			else
			{
				named = true;
				buttons[BT_CHARC_OK].setposition(vector2d(486, 445));
				buttons[BT_CHARC_CANCEL].setposition(vector2d(560, 445));
				buttons[BT_CHARC_FACEL].setactive(true);
				buttons[BT_CHARC_FACER].setactive(true);
				buttons[BT_CHARC_HAIRL].setactive(true);
				buttons[BT_CHARC_HAIRR].setactive(true);
				buttons[BT_CHARC_HAIRCL].setactive(true);
				buttons[BT_CHARC_HAIRCR].setactive(true);
				buttons[BT_CHARC_SKINL].setactive(true);
				buttons[BT_CHARC_SKINR].setactive(true);
				buttons[BT_CHARC_TOPL].setactive(true);
				buttons[BT_CHARC_TOPR].setactive(true);
				buttons[BT_CHARC_BOTL].setactive(true);
				buttons[BT_CHARC_BOTR].setactive(true);
				buttons[BT_CHARC_SHOESL].setactive(true);
				buttons[BT_CHARC_SHOESR].setactive(true);
				buttons[BT_CHARC_WEPL].setactive(true);
				buttons[BT_CHARC_WEPR].setactive(true);
				buttons[BT_CHARC_GENDERL].setactive(true);
				buttons[BT_CHARC_GEMDERR].setactive(true);
				textfields[TXT_NAMECHAR].setactive(false);
			}
			buttons[BT_CHARC_OK].setstate("normal");
		}
	}

	void charcreation::draw()
	{
		if (active)
		{
			for (char i = 0; i < 2; i++)
			{
				for (int k = 0; k < 800; k += sky.getdimension().x())
				{
					sky.draw(vector2d(k, (400 * i) - 100));
				}
			}

			cloud.draw(vector2d(static_cast<int>(cloudfx)-cloud.getdimension().x(), 300));
			cloud.draw(vector2d(static_cast<int>(cloudfx), 300));
			cloud.draw(vector2d(static_cast<int>(cloudfx)+cloud.getdimension().x(), 300));

			if (!named)
			{
				nameboard.draw(position);
			}
			else
			{
				for (vector<sprite>::iterator lbit = lookboard.begin(); lbit != lookboard.end(); ++lbit)
				{
					lbit->draw(position);
				}
			}
		}

		uielement::draw();

		if (active)
		{
			newchar.draw(position);

			if (named)
			{
				setlabel.draw(newchar.getface()->getname(), vector2d(591, 214));
				setlabel.draw(newchar.gethair()->getname(), vector2d(591, 233));
				setlabel.draw(newchar.gethair()->getcolor(), vector2d(591, 252));
				setlabel.draw(newchar.getbody()->getname(), vector2d(591, 271));
				setlabel.draw(newchar.getcloth(EQL_COAT)->getname(), vector2d(591, 290));
				setlabel.draw(newchar.getcloth(EQL_PANTS)->getname(), vector2d(591, 309));
				setlabel.draw(newchar.getcloth(EQL_SHOES)->getname(), vector2d(591, 328));
				setlabel.draw(newchar.getcloth(EQL_WEAPON)->getname(), vector2d(591, 347));
				setlabel.draw(female? "Female" : "Male", vector2d(591, 366));
			}
		}
	}

	void charcreation::update()
	{
		uielement::update();

		if (active)
		{
			newchar.update();

			if (cloudfx < cloud.getdimension().x())
			{
				cloudfx += 0.5f;
			}
			else
			{
				cloudfx = 200.0f;
			}
		}
	}
}
