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
#include "stdfax.h"
#include "texture.h"

using namespace util;
using namespace std;
using namespace graphics;

namespace io
{
	enum buttontypes : char
	{
		BTT_REGULAR,
		BTT_ONESPRITE,
		BTT_AREA
	};

	enum buttonstate : char
	{
		BTS_NORMAL,
		BTS_DISABLED,
		BTS_MOUSEOVER,
		BTS_PRESSED,
		BTS_SELECT
	};

	enum buttonid : short
	{
		BT_LOGIN,
		BT_NEW,
		BT_HOMEPAGE,
		BT_PWDLOST,
		BT_QUIT,
		BT_LOGINBANOK,
		BT_LOGINNOTICEOK,
		BT_LOGINLOST,
		BT_SAVEID,
		BT_WORLDSEL0,
		BT_WORLDSEL1,
		BT_WORLDSEL2,
		BT_WORLDSEL3,
		BT_WORLDSEL4,
		BT_WORLDSEL5,
		BT_WORLDSEL6,
		BT_WORLDSEL7,
		BT_WORLDSEL8,
		BT_WORLDSEL9,
		BT_WORLDSEL10,
		BT_WORLDSEL11,
		BT_WORLDSEL12,
		BT_WORLDSEL13,
		BT_WORLDSEL14,
		BT_WORLDSEL15,
		BT_WORLDSEL16,
		BT_WORLDSEL17,
		BT_WORLDSEL18,
		BT_WORLDSEL19,
		BT_CHANNELSEL0,
		BT_CHANNELSEL1,
		BT_CHANNELSEL2,
		BT_CHANNELSEL3,
		BT_CHANNELSEL4,
		BT_CHANNELSEL5,
		BT_CHANNELSEL6,
		BT_CHANNELSEL7,
		BT_CHANNELSEL8,
		BT_CHANNELSEL9,
		BT_CHANNELSEL10,
		BT_CHANNELSEL11,
		BT_CHANNELSEL12,
		BT_CHANNELSEL13,
		BT_CHANNELSEL14,
		BT_CHANNELSEL15,
		BT_CHANNELSEL16,
		BT_GOWORLD,
		BT_ARBEIT,
		BT_CHARCARD,
		BT_DELCHAR,
		BT_NEWCHAR,
		BT_SELCHAR,
		BT_DELCHARCA,
		BT_DELCHARCON,
		BT_PAGEL,
		BT_PAGER,
		BT_CHARC_OK,
		BT_CHARC_CANCEL,
		BT_CHARC_FACEL,
		BT_CHARC_FACER,
		BT_CHARC_HAIRL,
		BT_CHARC_HAIRR,
		BT_CHARC_HAIRCL,
		BT_CHARC_HAIRCR,
		BT_CHARC_SKINL,
		BT_CHARC_SKINR,
		BT_CHARC_TOPL,
		BT_CHARC_TOPR,
		BT_CHARC_BOTL,
		BT_CHARC_BOTR,
		BT_CHARC_SHOESL,
		BT_CHARC_SHOESR,
		BT_CHARC_WEPL,
		BT_CHARC_WEPR,
		BT_CHARC_GENDERL,
		BT_CHARC_GEMDERR,
		BT_CHAR0,
		BT_CHAR1,
		BT_CHAR2,
		BT_CHAR3,
		BT_CHAR4,
		BT_CHAR5,
		BT_CHAR6,
		BT_CHAR7,
		BT_BAR_CASHSHOP,
		BT_BAR_TRADE,
		BT_BAR_MENU,
		BT_BAR_SYSOP,
		BT_BAR_CHANNEL,
		BT_BAR_WHISPER,
		BT_BAR_CALLGM,
		BT_BAR_CHARINFO,
		BT_BAR_STATS,
		BT_BAR_QUEST,
		BT_BAR_INVENTORY,
		BT_BAR_SKILL,
		BT_BAR_FARM,
		BT_BAR_KEYMAP,
		BT_BAR_EQUIPS,
		BT_BAR_OPENCHAT,
		BT_BAR_CLOSECHAT,
		BT_BAR_CHATTARGET,
		BT_BAR_SCROLLUP,
		BT_BAR_SCROLLDOWN,
		BT_INVENT_EQUIP,
		BT_INVENT_USE,
		BT_INVENT_SETUP,
		BT_INVENT_ETC,
		BT_INVENT_CASH,
		BT_INVENT_DROPMESO,
		BT_INVENT_POINTS,
		BT_INVENT_EXPAND,
		BT_INVENT_GATHER,
		BT_INVENT_SORT,
		BT_INVENT_ITEMPOT,
		BT_INVENT_UPGRADE,
		BT_INVENT_MAGNIFY,
		BT_INVENT_BITCASE,
		BT_SKILL_JOB0,
		BT_SKILL_JOB1,
		BT_SKILL_JOB2,
		BT_SKILL_JOB3,
		BT_SKILL_JOB4,
		BT_SKILL_MACRO,
		BT_SKILL_GUILD,
		BT_SKILL_MOUNT,
		BT_SKILL_UP,
		BT_PETEQUIP,
		BT_CHANGECH,
		BT_KEYCONFIG,
		BT_OPTIONS,
		BT_JOYPAD,
		BT_GOPTIONS,
		BT_QUITGAME,
		BT_STATS_AUTO,
		BT_STATS_HP,
		BT_STATS_MP,
		BT_STATS_STR,
		BT_STATS_DEX,
		BT_STATS_LUK,
		BT_STATS_INT,
		BT_STATS_DETAILOPEN,
		BT_STATS_DETAILCLOSE,
		BT_KEYS_CANCEL,
		BT_KEYS_CLEAR,
		BT_KEYS_OK,
		BT_KEYS_DEFAULT,
		BT_KEYS_QUICK
	};

	class button
	{
	public:
		button(node);
		button(node, int, int);
		button(texture, texture, int, int);
		button(vector2d, vector2d);
		button() {}
		~button() {}
		void draw(vector2d);
		rectangle2d bounds(vector2d);
		void setstate(buttonstate s) { state = s; }
		void setposition(vector2d p) { position = p; }
		void setactive(bool a) { active = a; }
		bool isactive() { return active; }
		buttonstate getstate() { return state; }
	private:
		map<buttonstate, texture> textures;
		buttonstate state;
		vector2d position;
		vector2d dimension;
		char bttype;
		bool active;
	};
}

