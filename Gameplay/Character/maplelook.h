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
#include "facetype.h"
#include "bodytype.h"
#include "hairstyle.h"
#include "clothing.h"

using namespace character;

namespace gameplay
{
	struct bodyaction
	{
		string state;
		char frame;
		short delay;
	};

	struct lookinfo
	{
		bool female;
		char skin;
		int faceid;
		int hairid;
		map<char, int> equips;
		map<char, int> maskedequips;
		vector<int> petids;
	};

	class maplelook
	{
	public:
		maplelook() {}
		~maplelook() {}
		maplelook(lookinfo);
		void init(map<string, map<char, short>>, map<string, map<char, bodyaction>>, map<string, map<char, map<charlayer, map<string, vector2d>>>>);
		void draw(ID2D1HwndRenderTarget*, vector2d);
		bool update();
		void setstate(string);
		void setactions(vector<string>);
		void setposition(vector2d p) { position = p; }
		void setfleft(bool f) { faceleft = f; }
		void addcloth(clothing c) { clothes[c.gettype()] = c; }
		void removecloth(string s) { clothes.erase(s); }
		void setface(facetype f) { face = f; }
		void sethair(hairstyle h) { hair = h; }
		void setbody(bodytype b) { body = b; }
		void setexpression(char c) { face.setexp(c); }
		bool isloaded() { return loaded; }
		string getstate() { return state; }
		lookinfo* getinfo() { return &info; }
		bodytype* getbody() { return &body; }
		facetype* getface() { return &face; }
		hairstyle* gethair() { return &hair; }
		clothing* getcloth(string s) { return &clothes[s]; }
	private:
		map<string, map<char, short>> delays;
		map<string, map<char, bodyaction>> bodyactions;
		map<string, map<char, map<charlayer, map<string, vector2d>>>> bodyheadmap;
		lookinfo info;
		bodytype body;
		facetype face;
		hairstyle hair;
		map<string, clothing> clothes;
		bool loaded;
		bool faceleft;
		vector2d position;
		vector<string> actions;
		string action;
		string state;
		char frame;
		char actionframe;
		short elapsed;
	};
}

