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
#include "maplechar.h"

using namespace std;

namespace gameplay
{
	class account
	{
	public:
		account() {}
		~account() {}
		void init(int, string, char, bool, bool, short);
		void selectchar(int);
		void clear() { maplechars.clear(); }
		char getslots() { return slots; }
		bool isfemale() { return female; }
		char getpic() { return pic; }
		size_t charcount() { return maplechars.size(); }
		void addchar(maplechar m) { maplechars.push_back(m); }
		void setpicslots(char p, char s) { pic = p; slots = s; }
		maplechar* getplayer() { return &maplechars[selected]; }
		vector<maplechar>* getchars() { return &maplechars; }
	private:
		vector<maplechar> maplechars;
		int accid;
		string accname;
		char gmlevel;
		bool female;
		bool muted;
		short pin;
		char pic; //0 - pic needed, 1 - has pic, 2 - no pic needed
		char slots;
		char selected;
	};
}
