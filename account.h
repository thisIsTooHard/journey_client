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
#include "maplestats.h"
#include "maplelook.h"

namespace gameplay
{
	struct maplechar
	{
		maplestats stats;
		maplelook look;
		pair<int, char> rank;
		pair<int, char> jobrank;

		maplelook* getlook() { return &look; }
		maplestats* getstats() { return &stats; }
		pair<int, char> getrank() { return rank; }
		pair<int, char> getjobrank() { return jobrank; }
	};

	class account
	{
	public:
		account() {}
		~account() {}
		void init(int, string, char, bool, bool, short);
		void selectchar(int);
		maplechar* addchar();
		void clear() { maplechars.clear(); }
		void setpicslots(char p, char s) { pic = p; slots = s; }
		bool isfemale() { return female; }
		char getslots() { return slots; }
		char getpic() { return pic; }
		size_t charcount() { return maplechars.size(); }
		maplechar* getplayer() { return &maplechars[selected]; }
		maplechar* getchar(size_t c) { return &maplechars[c]; }
		vector<maplechar>* getchars() { return &maplechars; }
	private:
		vector<maplechar> maplechars;
		string accname;
		int accid;
		char selected;
		bool female;
		bool muted;
		short pin;
		char gmlevel;
		char pic;
		char slots;
	};
}
