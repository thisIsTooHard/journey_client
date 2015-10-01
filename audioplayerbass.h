/////////////////////////////////////////////////////////////////////////////
// This file is part of the Journey MMORPG client                           //
// Copyright � 2015 SYJourney                                               //
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
#include "bass.h"
#include <string>
#include <map>
#include <vector>

using namespace std;

namespace program
{
	class audioplayerbass
	{
	public:
		audioplayerbass() {}
		~audioplayerbass();
		bool init(HWND);
		void playbgm(void*, size_t);
		void cachesound(void*, size_t, size_t);
		void playsound(size_t);
		void setvolume0(int);
		void setvolume1(int);
	private:
		HSTREAM bgm;
		map<size_t, HSAMPLE> soundcache;
	};
}

