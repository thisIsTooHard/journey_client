/////////////////////////////////////////////////////////////////////////////
// This file is part of the Journey MMORPG client                           //
// Copyright � 2015 SYJourney                                               //
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
#include "safeptrmap.h"
#include "playfield.h"
#include "uielement.h"
#include "cursor.h"
#include "keyboard.h"
#include "baseinterface.h"
#include "itemtooltip.h"
#include "equiptooltip.h"

using namespace std;
using namespace util;
using namespace gameplay;

namespace io
{
	class ui
	{
	public:
		ui() {}
		~ui();
		void init();
		void draw();
		void update();
		void add(uielements t) { add(t, 0); }
		void add(uielements, char);
		void remove(uielements);
		void sendkey(WPARAM, bool);
		void sendmouse(mousestate, vector2d);
		void showiteminfo(int);
		void showequipinfo(int, short, bool);
		void sendchat(int, bool, string);
		void setactive(bool a) { active = a; }
		void sendmouse(vector2d p) { sendmouse(mouse.getstate(), p); }
		void enableactions() { actionsenabled = true; }
		void disableactions() { actionsenabled = false; }
		void settextfield(textfield* t) { activetext = t; }
		void seticon(icon* a) { activeicon = a; }
		uielement* getelement(uielements t) { return elements.get(t); }
		keyboard* getkeyboard() { return &keys; }
		playfield* getfield() { return &field; }
		baseinterface* getbase() { return &base; }

		template <class E>
		E* getelement(uielements t)
		{
			if (elements.contains(t))
			{
				return reinterpret_cast<E*>(elements.get(t));
			}
			else
			{
				return 0;
			}
		}
	private:
		safeptrmap<uielements, uielement*> elements;
		playfield field;
		baseinterface base;
		cursor mouse;
		keyboard keys;
		equiptooltip equipinfo;
		itemtooltip iteminfo;
		uielement* focused;
		textfield* activetext;
		icon* activeicon;
		tooltip* activeinfo;
		bool shift;
		bool active;
		bool actionsenabled;
	};
}

