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
#include "playereffects.h"

using namespace graphics;
using namespace gameplay;

namespace data
{
	struct skillinfo
	{
		float damage;
		float chance;
		float crit;
		short duration;
		short hpcost;
		short mpcost;
		char attacks;
		char mobs;
		pair<vector2d, vector2d> range;
	};

	class skilldata
	{
	public:
		skilldata(int);
		skilldata() {}
		~skilldata() {}
		string getaction(bool);
		void addeffects(playereffects*, bool, float, bool);
		bool isattack() { return offensive; }
		skillinfo getlevel(int l) { return levels[l]; }
		texture geticon(char c) { return icon[c]; }
		map<char, texture>* geticons() { return &icon; }
	private:
		map<char, texture> icon;
		map<int, skillinfo> levels;
		vector<animation> skill_e;
		vector<animation> affected;
		vector<string> actions;
		string prepare;
		short prepare_t;
		bool offensive;
	};
}

