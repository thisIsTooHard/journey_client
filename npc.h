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
#include "graphicobject.h"
#include "textlabel.h"
#include "randomizer.h"

using namespace graphics;

namespace maplemap
{
	class npc : public graphicobject
	{
	public:
		npc() {}
		~npc() {}
		npc(int, int, bool, short, vector2d);
		void draw(vector2d);
		void setstate(string);
		void update();
		vector2d getdim() { return textures[state].getdimension(0); }
	private:
		map<string, animation> textures;
		vector<string> states;
		randomizer random;
		map<string, vector<string>> lines;
		textlabel ntag;
		textlabel ftag;
		string state;
		string name;
		string func;
		short oid;
		int id;
		bool flip;
		bool hidename;
		bool scripted;
		bool mouseonly;
		short fh;
		vector2d position;
		short elapsed_s;
	};
}

