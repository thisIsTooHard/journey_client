//////////////////////////////////////////////////////////////////////////////
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
#include "audio.h"
#include <map>

using namespace nl;
using namespace std;

namespace data
{
	enum maplesound
	{
		MSN_MSCLICK,
		MSN_MSOVER,
		MSN_MSGRAB,
		MSN_MSENDGRAB,
		MSN_CHARSEL,
		MSN_GAMEIN,
		MSN_JUMP,
		MSN_DROP,
		MSN_PICKUP,
		MSN_PORTAL,
		MSN_LEVELUP,
		MSN_DEAD,
		MSN_TRANSFORM,
		MSN_QUESTCLEAR,
		MSN_QUESTALERT,
		MSN_CARDGET,
		MSN_SCROLLSUCCESS,
		MSN_SCROLLFAIL
	};

	class soundcache
	{
	public:
		soundcache() {}
		~soundcache() {}
		void init();
		void play(maplesound);
		size_t cache(node);
	private:
		map<maplesound, size_t> sounds;
	};
}

