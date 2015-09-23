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
#include "nametag.h"

using namespace character;
using namespace io;

namespace gameplay
{
	struct bodyaction
	{
		string state;
		byte frame;
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

	struct bodydrawinfo
	{
		map<string, map<byte, short>> delays;
		map<string, map<byte, bodyaction>> actions;
		map<string, map<byte, vector2d>> facepos;
		map<string, map<byte, map<charlayer, map<string, vector2d>>>> posmap;
	};

	enum movetype
	{
		MVT_NONE,
		MVT_ABSOLUTE,
		MVT_RELATIVE,
		MVT_CHAIR,
		MVT_JUMPDOWN
	};

	struct movefragment
	{
		movetype type;
		byte command;
		short xpos;
		short ypos;
		short xpps;
		short ypps;
		short unk;
		short fh;
		byte newstate;
		short duration;
	};

	class maplelook
	{
	public:
		maplelook() {}
		~maplelook() {}
		maplelook(lookinfo);
		void init(bodydrawinfo*);
		void addcloth(clothing*);
		void addcloth(clothing*, equiplayer);
		void draw(vector2d);
		bool update();
		void setstate(string);
		void setstate(string, float);
		void setaction(string, float);
		void setexpression(char);
		void setposition(vector2d p) { position = p; }
		void setfleft(bool f) { faceleft = f; }
		void removecloth(equiplayer l) { clothes.erase(l); }
		void setface(facetype* f) { face = f; }
		void sethair(hairstyle* h) { hair = h; }
		void setbody(bodytype* b) { body = b; }
		bool isloaded() { return loaded; }
		string getstate() { return state; }
		weapontype getweptype() { return clothes[EQL_WEAPON]->getweptype(); }
		lookinfo* getinfo() { return &info; }
		bodytype* getbody() { return body; }
		facetype* getface() { return face; }
		hairstyle* gethair() { return hair; }
		clothing* getcloth(equiplayer l) { return clothes[l]; }
	private:
		lookinfo info;
		bodydrawinfo* bodyinfo;
		bodytype* body;
		facetype* face;
		hairstyle* hair;
		map<equiplayer, clothing*> clothes;
		string name;
		bool loaded;
		bool faceleft;
		vector2d position;
		string action;
		string state;
		byte frame;
		byte actionframe;
		short elapsed;
		float anispeed;
		string state_f;
		short elapsed_f;
		byte frame_f;
	};
}

