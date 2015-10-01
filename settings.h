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
#include "vector2d.h"
#include "inventory.h"

using namespace util;
using namespace gameplay;

namespace program
{
	struct configuration
	{
		bool fullscreen;
		byte bgmvolume;
		byte sfxvolume;
		bool saveid;
		string defaultacc;
		byte defaultworld;
		byte defaultchannel;
		byte defaultchar;
		bool chatopen;
		vector2d equipsinvpos;
		vector2d statsinfopos;
		vector2d inventorypos;
		vector2d questinfopos;
		vector2d skillinvpos;
		inventorytype definventory;
	};

	class settings
	{
	public:
		settings();
		~settings();
		configuration* getconfig() { return &config; }
	private:
		vector2d loadv2d(string);
		configuration config;
	};
}

