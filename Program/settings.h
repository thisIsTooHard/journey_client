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
#include "stdfax.h"
#include "vector2d.h"

using namespace std;
using namespace util;

namespace program
{
	class settings
	{
	private:
		bool fullscreen;
		byte bgmvolume;
		byte sfxvolume;
		bool saveacc;
		string defaultacc;
		byte defaultworld;
		byte defaultchannel;
		byte defaultchar;
		vector2d equipsinvpos;
		vector2d statsinfopos;
		vector2d inventorypos;
		vector2d questinfopos;
	public:
		settings();
		~settings() {}
		void save(char, string);
		bool getfullscreen() { return fullscreen; }
		byte getbgmvolume() { return bgmvolume; }
		byte getsfxvolume() { return sfxvolume; }
		bool accsaved() { return saveacc; }
		string getdefaultacc() { return defaultacc; }
		byte getdefworld() { return defaultworld; }
		byte getdefch() { return defaultchannel; }
		byte getdefchar() { return defaultchar; }
		vector2d geteqspos() { return equipsinvpos; }
		vector2d getstatspos() { return statsinfopos; }
		vector2d getinvpos() { return inventorypos; }
		vector2d getquestspos() { return questinfopos; }
	};
}

