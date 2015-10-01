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
#include "textlabel.h"

using namespace std;
using namespace graphics;

namespace program
{
	class fontcache
	{
	public:
		fontcache() {}
		~fontcache();
		void init(IDWriteFactory*);
		IDWriteTextFormat* getfont(dwfonts);
		IDWriteFactory* getdwrite_f() { return dwrite_f; }
	private:
		IDWriteFactory* dwrite_f;
		map<dwfonts, IDWriteTextFormat*> fonts;
	};
}

