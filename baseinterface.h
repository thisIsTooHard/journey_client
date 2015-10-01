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
#include "charset.h"
#include "nametag.h"
#include "safemap.h"
#include "chatballoon.h"

namespace io
{
	struct dmgeffect
	{
		int number;
		char type;
		float fx;
		float fy;
		float alpha;
	};

	struct statusinfo
	{
		bool white;
		string text;
		float alpha;
	};

	class baseinterface : public uielement
	{
	public:
		baseinterface() {}
		~baseinterface() {}
		void init();
		void addstatusinfo(bool, string);
		void showdamage(vector<pair<int, char>>, vector2d);
		void drawmobhp(char, vector2d);
		void addnpcbutton(int, vector2d, vector2d);
		void addchatballoon(int, char, string);
		void draw(vector2d);
		void update();
		mousestate sendmouse();
	private:
		safemap<int, chatballoon> chatballoons;
		safemap<int, button> npcbuttons;
		map<string, texture> mobhpbar;
		vector<dmgeffect> dmgeffects;
		vector<statusinfo> statusinfos;
		charset dmgset;
		charset critset;
		charset playerdmgset;
		nametag npctag;
		textlabel infotextw;
		textlabel infotexty;
		SRWLOCK dmglock;
	};
}

