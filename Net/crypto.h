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

using namespace std;

namespace net
{
	const char jrkey[13] = { 33, 101, 54, 27, 11, 7, 78, 62, 119, 120, 47, 85, 93 };

	class crypto
	{
	private:
		char* recvIv;
		char* sendIv;
		char version;
		char localisation;
	public:
		crypto() {}
		~crypto() {}
		crypto(char, char*, char*, char);
		void clear();
		char* sendencrypt(char*, int);
		void updateiv();
	};
}

