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
#include "maplelook.h"

using namespace gameplay;

namespace io
{
	class charcreation : public uielement
	{
	public:
		charcreation(bool);
		~charcreation() {}
		void draw();
		void update();
		void buttonpressed(short);
		void sendbool(bool);
	private:
		texture sky;
		texture cloud;
		float cloudfx;
		sprite nameboard;
		vector<sprite> lookboard;
		maplelook newchar;
		map<bool, vector<char>> skins;
		map<bool, vector<char>> haircolors;
		map<bool, vector<int>> faces;
		map<bool, vector<int>> hairs;
		map<bool, vector<int>> tops;
		map<bool, vector<int>> bots;
		map<bool, vector<int>> shoes;
		map<bool, vector<int>> weapons;
		bool named;
		string name;
		bool female;
		size_t skin;
		size_t haircolor;
		size_t face;
		size_t hair;
		size_t top;
		size_t bot;
		size_t shoe;
		size_t weapon;
		textlabel setlabel;
	};
}

