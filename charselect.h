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
#include "uielement.h"
#include "charset.h"
#include "nametag.h"
#include "account.h"

using namespace gameplay;

namespace io
{
	class charselect : public uielement
	{
	public:
		charselect(account*);
		~charselect() {}
		void draw();
		void update();
		void buttonpressed(short);
	private:
		vector<maplechar*> chars;
		vector<nametag> nametags;
		textlabel name;
		textlabel job;
		charset lvset;
		charset statset;
		char pic;
		char page;
		char selected;
	};
}

