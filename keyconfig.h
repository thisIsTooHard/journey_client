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
#include "uielement.h"
#include "keyboard.h"
#include "inventory.h"
#include "keyicon.h"
#include "dragitemicon.h"

using namespace gameplay;

namespace io
{
	class keyconfig : public uielement
	{
	public:
		keyconfig(map<char, pair<keytype, int>>, inventory*);
		~keyconfig() {}
		void buttonpressed(short);
		void sendicon(icon*, vector2d);
		void oninfo(icon*);
		rectangle2d dragarea();
	private:
		map<char, pair<keytype, int>> keymap;
		map<char, texture> keytxt;
		map<keyaction, texture> actiontxt;
		vector2d getkeypos(char);
		vector2d getreservepos(keyaction);
	};
}

