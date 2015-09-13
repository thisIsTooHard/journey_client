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
#include "settings.h"
#include <fstream>

namespace program
{
	settings::settings()
	{
		fullscreen = false;
		bgmvolume = 50;
		sfxvolume = 50;
		saveacc = false;
		defaultacc = "";
		defaultworld = 0;
		defaultchannel = 0;
		defaultchar = 0;
		equipsinvpos = vector2d(100, 200);
		statsinfopos = vector2d(250, 300);
		inventorypos = vector2d(150, 250);
		questinfopos = vector2d(350, 150);

		ifstream config;
		string line;
		config.open("Settings");
		if (config.is_open()) {
			while (getline(config, line))
			{
				switch (line[0])
				{
				case '0':
					fullscreen = stoi(line.substr(1)) == 1;
					break;
				case '1':
					bgmvolume = stoi(line.substr(1));
					if (bgmvolume > 100)
						bgmvolume = 100;
					else if (bgmvolume < 0)
						bgmvolume = 0;
					break;
				case '2':
					sfxvolume = stoi(line.substr(1));
					if (sfxvolume > 100)
						sfxvolume = 100;
					else if (sfxvolume < 0)
						sfxvolume = 0;
					break;
				case '3':
					saveacc = stoi(line.substr(1)) == 1;
					break;
				case '4':
					defaultacc = line.substr(1);
					break;
				case '5':
					defaultworld = stoi(line.substr(1));
					break;
				case '6':
					defaultchannel = stoi(line.substr(1));
					break;
				case '7':
					defaultchar = stoi(line.substr(1));
					break;
				case '8':
					statsinfopos = vector2d(stoi(line.substr(1)), statsinfopos.y());
					break;
				case '9':
					statsinfopos = vector2d(statsinfopos.x(), stoi(line.substr(1)));
					break;
				}
			}
		}
		config.close();
	}

	void settings::save(char no, string param)
	{

	}
}
