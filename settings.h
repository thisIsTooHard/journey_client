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
	enum configtype
	{
		CFT_FULLSCREEN,
		CFT_SFXVOLUME,
		CFT_BGMVOLUME,
		CFT_SAVEID,
		CFT_DEFAULTID,
		CFT_DEFAULTWORLD,
		CFT_DEFAULTCHANNEL,
		CFT_DEFAULTCHAR,
		CFT_CHATOPEN,
		CFT_UIPOS_EQUIPS,
		CFT_UIPOS_STATS,
		CFT_UIPOS_INVENT,
		CFT_UIPOS_QUESTS
	};

	class settings
	{
	public:
		settings();
		~settings();
		void save(char, string);
		void setsaveid(bool s) { saveid = s; }
		void setdefacc(string a) { defaultacc = a; }
		void setdefworld(byte v) { defaultworld = v; }
		void setdefchannel(byte v) { defaultchannel = v; }
		void setdefchar(byte v) { defaultchar = v; }
		void setchatopen(bool o) { chatopen = o; }
		bool getfullscreen() { return fullscreen; }
		byte getbgmvolume() { return bgmvolume; }
		byte getsfxvolume() { return sfxvolume; }
		bool getsaveid() { return saveid; }
		string getdefaultacc() { return defaultacc; }
		byte getdefworld() { return defaultworld; }
		byte getdefch() { return defaultchannel; }
		byte getdefchar() { return defaultchar; }
		bool getchatopen() { return chatopen; }
		vector2d geteqspos() { return equipsinvpos; }
		vector2d getstatspos() { return statsinfopos; }
		vector2d getinvpos() { return inventorypos; }
		vector2d getquestspos() { return questinfopos; }
	private:
		map<configtype, string> configs;
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
	};
}

