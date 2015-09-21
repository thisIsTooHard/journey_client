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
#include "charsprites.h"
#include "mapleequip.h"
#include "maplestats.h"

using namespace gameplay;

namespace character
{
	enum equiplayer
	{
		EQL_NONE,
		EQL_CAP,
		EQL_FACEACC,
		EQL_EYEACC,
		EQL_EARRINGS,
		EQL_COAT,
		EQL_LONGCOAT,
		EQL_PANTS,
		EQL_SHOES,
		EQL_GLOVES,
		EQL_SHIELD,
		EQL_CAPE,
		EQL_WEAPON,
		EQL_RING,
		EQL_PENDANT,
		EQL_BELT,
		EQL_MEDAL
	};

	class clothing : public charsprites
	{
	public:
		clothing(int, map<string, map<byte, map<charlayer, map<string, vector2d>>>>*);
		clothing();
		~clothing() {}
		string getdisplayspeed();
		string getdisplaystat(equipstat);
		float getwmultiplier();
		equiplayer getlayer() { return layer; }
		string gettype() { return iscash() ? "CASH" : type; }
		string getname() { return name; }
		string getdesc() { return desc; }
		short getreqstat(maplestat ms) { return reqstats.count(ms) ? reqstats[ms] : 0; }
		short getdefstat(equipstat es) { return defstats.count(es) ? defstats[es] : 0; }
		bool iscash() { return cash; }
		bool istransparent() { return transparent; }
		bool isweapon() { return layer == EQL_WEAPON; }
		bool istwo_h() { return isweapon() ? twohanded : false; }
		byte getwspeed() { return isweapon() ? attackspeed : 0; }
		byte getattack() { return isweapon() ? attack : 0; }
		weapontype getweptype() { return isweapon() ? weptype : WEP_NONE; }
		byte getslots() { return slots; }
		int getid() { return itemid; }
		texture geticon(bool r) { return icon[r]; }
		map<bool, texture> geticons() { return icon; }
	private:
		map<bool, texture> icon;
		int itemid;
		equiplayer layer;
		string type;
		string name;
		string desc;
		bool cash;
		bool tradeable;
		bool transparent;
		int price;
		byte slots;
		map<maplestat, short> reqstats;
		map<equipstat, short> defstats;
		string afterimage;
		string sfx;
		byte attackspeed;
		byte attack;
		weapontype weptype;
		bool twohanded;
	};
}

