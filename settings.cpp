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
		saveid = false;
		defaultacc = "";
		defaultworld = 0;
		defaultchannel = 0;
		defaultchar = 0;
		chatopen = false;
		equipsinvpos = vector2d(100, 150);
		statsinfopos = vector2d(250, 150);
		inventorypos = vector2d(150, 150);
		questinfopos = vector2d(350, 150);

		ifstream config;
		string line;
		config.open("Settings");
		if (config.is_open()) {
			while (getline(config, line))
			{
				int split = line.find(":");
				string type = line.substr(0, split);
				string args = line.substr(split + 1);

				if (type.size() > 0 && args.size() > 0)
				{
					int itype = stoi(type);

					switch (itype)
					{
					case 0:
						fullscreen = args == "1";
						break;
					case 1:
						bgmvolume = stoi(args);
						bgmvolume = min(100, bgmvolume);
						bgmvolume = max(0, bgmvolume);
						break;
					case 2:
						sfxvolume = stoi(args);
						sfxvolume = min(100, sfxvolume);
						sfxvolume = max(0, sfxvolume);
						break;
					case 3:
						saveid = args == "1";
						break;
					case 4:
						defaultacc = args;
						break;
					case 5:
						defaultworld = stoi(args);
						break;
					case 6:
						defaultchannel = stoi(args);
						break;
					case 7:
						defaultchar = stoi(args);
						break;
					case 8:
					case 9:
					case 10:
					case 11:
						string xstr = args.substr(0, args.find(","));
						string ystr = args.substr(args.find(",") + 1);
						vector2d pos = vector2d(stoi(xstr), stoi(ystr));
						switch (itype)
						{
						case 8:
							equipsinvpos = pos;
							break;
						case 9:
							statsinfopos = pos;
							break;
						case 10:
							inventorypos = pos;
							break;
						case 11:
							questinfopos = pos;
							break;
						}
						break;
					}
				}
			}
		}
		config.close();
	}

	void settings::save(char no, string param)
	{

	}

	settings::~settings()
	{
		ofstream config;
		config.open("Settings");
		if (config.is_open())
		{
			config << "0:" + to_string(fullscreen) << endl;
			config << "1:" + to_string(bgmvolume) << endl;
			config << "2:" + to_string(sfxvolume) << endl;
			config << "3:" + to_string(saveid) << endl;
			config << "4:" + defaultacc << endl;
			config << "5:" + to_string(defaultworld) << endl;
			config << "6:" + to_string(defaultchannel) << endl;
			config << "7:" + to_string(defaultchar) << endl;
			config << "8:" + equipsinvpos.tostring() << endl;
			config << "9:" + statsinfopos.tostring() << endl;
			config << "10:" + inventorypos.tostring() << endl;
			config << "11:" + questinfopos.tostring() << endl;
			config.close();
		}
	}
}
