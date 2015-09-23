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

namespace io
{
	enum chattarget
	{
		CHT_ALL,
		CHT_BUDDY,
		CHT_GUILD,
		CHT_ALLIANCE,
		CHT_PARTY,
		CHT_SQUAD
	};

	class chatbar : public uielement
	{
	public:
		chatbar();
		~chatbar() {}
		void draw();
		void update();
		void sendchat(string);
		void buttonpressed(short);
		rectangle2d bounds();
	private:
		map<bool, texture> chatspace;
		map<chattarget, texture> chattargets;
		texture chatenter;
		texture chatcover;
		textlabel closedtext;
		vector<string> lines;
		bool open;
		chattarget chattarget;
	};
}

