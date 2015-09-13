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
#include "collision.h"
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
		BT_CASHSHOP,
		BT_TRADE,
		BT_MENU,
		BT_SYSOP,
		BT_CHANNEL,
		BT_CHARINFO,
		BT_STATS,
		BT_QUEST,
		BT_INVENTORY,
		BT_SKILL,
		BT_FARM,
		BT_KEYMAP,
		BT_CALLGM,
		BT_CHAT,
		BT_EQUIPS,
		BT_PETEQUIP,
		BT_CHANGECH,
		BT_KEYCONFIG,
		BT_OPTIONS,
		BT_JOYPAD,
		BT_GOPTIONS,
		BT_QUITGAME,
		BT_KEYS_CANCEL,
		BT_KEYS_CLEAR,
		BT_KEYS_OK,
		BT_KEYS_DEFAULT,
		BT_KEYS_QUICK
	};

	enum textfieldid : short
	{
		TXT_ACC,
		TXT_PASS,
		TXT_NAMECHAR
	};

	class uielement
	{
	public:
		uielement() {}
		virtual ~uielement() {}
		virtual void buttonpressed(short) {}
		virtual void draw(ID2D1HwndRenderTarget*);
		virtual void update();
		virtual void sendicon(dragicon*, vector2d);
		virtual void sendbool(bool b) {}
		mousestate sendmouse(vector2d, mousestate);
		virtual pair<vector2d, vector2d> bounds() { return pair<vector2d, vector2d>(position, dimensions); }
		void setbutton(short i, string s) { if (buttons.count(i)) buttons[i].setstate(s); }
		void togglehide() { active = !active; }
		void deactivate() { active = false; }
		bool isactive() { return active; }
	protected:
		map<short, button> buttons;
		map<short, textfield> textfields;
		vector<dragicon> dragicons;
		vector<sprite> sprites;
		vector2d position;
		vector2d dimensions;
		bool active;
	};
}

