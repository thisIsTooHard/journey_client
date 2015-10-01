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
#include "cursor.h"
#include "button.h"
#include "textfield.h"
#include "sprite.h"
#include "icon.h"
#include "safeptrmap.h"

namespace io
{
	enum uielements : char
	{
		UI_LOGIN,
		UI_LOGINNOTICE,
		UI_LOGINWAIT,
		UI_SOFTKEYBOARD,
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
		UI_EQUIPS,
		UI_SKILLS
	};

	class uielement
	{
	public:
		virtual ~uielement() {}
		virtual void draw();
		virtual void update();
		mousestate sendmouse(vector2d, mousestate);
		virtual void sendicon(icon* i, vector2d v) { i->resetdrag(); }
		virtual void buttonpressed(short) {}
		virtual void oninfo(icon* i) {}
		virtual void sendbool(bool b) {}
		virtual void sendchar(char c) {}
		virtual void sendshort(short s) {}
		virtual void sendint(int i) {}
		virtual void sendlong(int64_t l) {}
		virtual void sendstring(string s) {}
		virtual rectangle2d bounds() { return rectangle2d(position, position + dimensions); }
		virtual rectangle2d dragarea() { return rectangle2d(position, position); }
		void setbutton(short i, buttonstate s) { if (buttons.count(i)) buttons[i].setstate(s); }
		void togglehide() { active = !active; }
		void deactivate() { active = false; }
		bool isactive() { return active; }
		bool isdragged() { return dragged; }
	protected:
		safeptrmap<short, icon*> icons;
		map<short, button> buttons;
		map<textid, textfield> textfields;
		vector<sprite> sprites;
		vector<texture> backgrounds;
		vector2d position;
		vector2d dimensions;
		vector2d cursorrel;
		bool active;
		bool dragged;
		short buttoncd;
	};
}

