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
		config.fullscreen = false;
		config.bgmvolume = 50;
		config.sfxvolume = 50;
		config.saveid = false;
		config.defaultacc = "";
		config.defaultworld = 0;
		config.defaultchannel = 0;
		config.defaultchar = 0;
		config.chatopen = false;
		config.equipsinvpos = vector2d(100, 150);
		config.statsinfopos = vector2d(250, 150);
		config.inventorypos = vector2d(150, 150);
		config.questinfopos = vector2d(350, 150);
		config.skillinvpos = vector2d(400, 150);
		config.definventory = IVT_EQUIP;

		ifstream configtxt;
		string line;
		configtxt.open("Settings");
		if (configtxt.is_open()) {
			while (getline(configtxt, line))
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
						config.fullscreen = args == "1";
						break;
					case 1:
						config.bgmvolume = stoi(args);
						if (config.bgmvolume > 100)
						{
							config.bgmvolume = 100;
						}
						else if (config.bgmvolume < 0)
						{
							config.bgmvolume = 0;
						}
						break;
					case 2:
						config.sfxvolume = stoi(args);
						if (config.sfxvolume > 100)
						{
							config.sfxvolume = 100;
						}
						else if (config.sfxvolume < 0)
						{
							config.sfxvolume = 0;
						}
						break;
					case 3:
						config.saveid = args == "1";
						break;
					case 4:
						config.defaultacc = args;
						break;
					case 5:
						config.defaultworld = stoi(args);
						break;
					case 6:
						config.defaultchannel = stoi(args);
						break;
					case 7:
						config.defaultchar = stoi(args);
						break;
					case 8:
						config.equipsinvpos = loadv2d(args);
						break;
					case 9:
						config.statsinfopos = loadv2d(args);
						break;
					case 10:
						config.inventorypos = loadv2d(args);
						break;
					case 11:
						config.questinfopos = loadv2d(args);
						break;
					case 12:
						config.definventory = static_cast<inventorytype>(stoi(args));
						break;
					case 13:
						config.skillinvpos = loadv2d(args);
						break;
					}
				}
			}
		}
		configtxt.close();
	}

	vector2d settings::loadv2d(string args)
	{
		string xstr = args.substr(0, args.find(","));
		string ystr = args.substr(args.find(",") + 1);
		return vector2d(stoi(xstr), stoi(ystr));
	}

	settings::~settings()
	{
		ofstream configtxt;
		configtxt.open("Settings");
		if (configtxt.is_open())
		{
			configtxt << "0:" + to_string(config.fullscreen) << endl;
			configtxt << "1:" + to_string(config.bgmvolume) << endl;
			configtxt << "2:" + to_string(config.sfxvolume) << endl;
			configtxt << "3:" + to_string(config.saveid) << endl;
			configtxt << "4:" + config.defaultacc << endl;
			configtxt << "5:" + to_string(config.defaultworld) << endl;
			configtxt << "6:" + to_string(config.defaultchannel) << endl;
			configtxt << "7:" + to_string(config.defaultchar) << endl;
			configtxt << "8:" + config.equipsinvpos.tostring() << endl;
			configtxt << "9:" + config.statsinfopos.tostring() << endl;
			configtxt << "10:" + config.inventorypos.tostring() << endl;
			configtxt << "11:" + config.questinfopos.tostring() << endl;
			configtxt << "12:" + to_string(static_cast<int>(config.definventory)) << endl;
			configtxt << "13:" + config.skillinvpos.tostring() << endl;
			configtxt.close();
		}
	}
}
