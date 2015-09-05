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

using namespace gameplay;

namespace character
{
	class clothing : public charsprites
	{
	public:
		clothing(int, map<string, map<char, map<charlayer, map<string, vector2d>>>>*);
		clothing() {}
		~clothing() {}
		string gettype() { return type; }
		string getname() { return name; }
		string getdesc() { return desc; }
		bool istwo_h() { return (type == "Weapon") ? twohanded : false; }
	private:
		pair<texture, texture> icon;
		string type;
		string name;
		string desc;
		bool cash;
		bool tradeable;
		int price;
		byte slots;
		short reqlevel;
		short reqjob;
		short reqstr;
		short reqdex;
		short reqint;
		short reqluk;
		map<equipstat, short> defstats;
		string afterimage;
		string sfx;
		byte attackspeed;
		byte attack;
		bool twohanded;
	};
}

