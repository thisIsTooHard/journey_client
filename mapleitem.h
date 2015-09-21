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

using namespace std;

namespace gameplay
{
	class mapleitem
	{
	public:
		mapleitem() {}
		~mapleitem() {}
		mapleitem(int, short, short, char, bool, int64_t, int64_t, string, short);
		mapleitem(int, short, char, bool, int64_t, int64_t, string, char, short, char);
		bool canrecharge();
		int getid() { return itemid; }
		short getcount() { return count; }
		short getpos() { return pos; }
	protected:
		int itemid;
		short count;
		short pos;
		char type;
		bool cash;
		int64_t uniqueid;
		int64_t expire;
		string owner;
		short flag;
		string petname;
		char petlevel;
		short closeness;
		char fullness;
	};
}

