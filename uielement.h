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
#include "cursor.h"
#include "button.h"
#include "textfield.h"
#include "dragicon.h"
#include "sprite.h"

using namespace std;
using namespace util;

namespace io
{
	enum uielements : char
	{
		UI_LOGIN,
		UI_LOGINNOTICE,
		UI_LOGINWAIT,
		UI_WORLDSELECT,
		UI_CHARSEL,
		UI_CHARDELCONFIRM,
		UI_CREATECHAR,
		UI_BASEINTERFACE,
		UI_STATUSBAR,
		UI_CHATBAR,
		UI_SYSTEM,
		UI_KEYCONFIG,
		UI_STATSINFO,
		UI_QUESTS,
		UI_INVENTORY,
		UI_EQUIPS
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

	class uielement
	{
	public:
		uielement() {}
		virtual ~uielement() {}
		virtual void buttonpressed(short) {}
		virtual void draw();
		virtual void update();
		virtual void sendicon(dragicon*, vector2d);
		virtual void oniteminfo(dragicon* d) {}
		virtual void sendbool(bool b) {}
		virtual void sendchar(char c) {}
		virtual void sendshort(short s) {}
		virtual void sendint(int i) {}
		virtual void sendlong(int64_t l) {}
		virtual void sendstring(string s) {}
		mousestate sendmouse(vector2d, mousestate);
		virtual rectangle2d bounds() { return rectangle2d(position, position + dimensions); }
		virtual rectangle2d dragarea() { return rectangle2d(position, position); }
		void setbutton(short i, string s) { if (buttons.count(i)) buttons[i].setstate(s); }
		void togglehide() { active = !active; }
		void deactivate() { active = false; }
		bool isactive() { return active; }
		bool isdragged() { return dragged; }
	protected:
		map<short, button> buttons;
		map<textid, textfield> textfields;
		vector<dragicon> dragicons;
		vector<sprite> sprites;
		vector2d position;
		vector2d dimensions;
		vector2d cursorrel;
		bool active;
		bool dragged;
		short buttoncd;
	};
}

