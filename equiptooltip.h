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
#include "tooltip.h"
#include "clothing.h"
#include "mapleequip.h"
#include "maplestats.h"
#include "charset.h"
#include "mapletext.h"

using namespace gameplay;
using namespace character;

namespace io
{
	class equiptooltip : public tooltip
	{
	public:
		equiptooltip() {}
		~equiptooltip() {}
		void init();
		void setequip(clothing*, mapleequip*, maplestats*);
		void draw(vector2d);
		void clear() { itemid = 0; slot = 0; }
		int getid() { return itemid; }
		short getslot() { return slot; }
	private:
		clothing* cloth;
		mapleequip* equip;
		int itemid;
		short slot;
		textlabel name;
		textlabel potflag;
		textlabel flag;
		textlabel category;
		textlabel wepspeed;
		textlabel slots;
		textlabel hammers;
		map<equipstat, textlabel> statlabels;
		int filllength;
		texture top;
		texture mid;
		texture line;
		texture bot;
		texture base;
		map<potrank, texture> potential;
		potrank rank;
		texture cover;
		texture shade;
		map<maplestat, map<bool, texture>> reqstat;
		map<maplestat, bool> canequip;
		map<bool, charset> reqset;
		texture jobsbg;
		map<bool, map<char, texture>> jobs;
		vector<char> okjobs;
	};
}

