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
#include "texture.h"
#include "textlabel.h"

using namespace graphics;

namespace io
{
	enum tooltiptype
	{
		TTT_DESC,
		TTT_ITEM,
		TTT_EQUIP
	};

	class tooltip
	{
	public:
		tooltip(string, tooltiptype, vector2d);
		tooltip() {}
		virtual ~tooltip() {}
		virtual void draw(vector2d);
		virtual void update() {}
		void setactive(bool a) { active = a; }
		void setpos(vector2d p) { position = p; }
	protected:
		vector<texture> textures;
		textlabel info;
		vector2d position;
		bool active;
	};
}

