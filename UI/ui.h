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
#include "stdfax.h"
#include "playfield.h"
#include "uielement.h"
#include "elements.h"
#include "nxprovider.h"
#include "cursor.h"
#include "keyboard.h"
#include "equipinventory.h"

using namespace std;
using namespace util;

namespace io
{
	class ui
	{
	public:
		ui() {}
		~ui() {}
		void init(IWICImagingFactory*, IDWriteFactory*);
		void draw(ID2D1HwndRenderTarget*);
		void update();
		void enableactions();
		void disableactions();
		void add(char);
		void add(char, char);
		void remove(char);
		void sendmouse(vector2d);
		void sendmouse(char, vector2d);
		void sendkey(WPARAM, bool);
		void settextfield(textfield*);
		uielement* getelement(char);
		textfield* getactivetext();
		keyboard* getkeyboard();
		playfield* getfield() { return &field; }
		nxprovider* getprovider() { return &provider; }
	private:
		nxprovider provider;
		playfield field;
		map<char, uielement*> elements;
		SRWLOCK uilock;
		textfield* activetext;
		cursor mouse;
		keyboard keys;
		bool shift;
		bool actionsenabled;
	};
}
