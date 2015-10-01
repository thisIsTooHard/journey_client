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
#include "dragitemicon.h"

namespace io
{
	dragitemicon::dragitemicon(itemicontype t, map<bool, texture> txt, int id, short slt, short qt, vector2d p)
	{
		type = t;
		textures = txt;
		iid = id;
		slot = slt;
		qty = qt;
		pos = p;

		raw = false;
		showcount = qty > 0;
		alpha = 1.0f;
	}

	void dragitemicon::draw(vector2d parentpos)
	{
		if (!drag)
		{
			itemicon::draw(pos + parentpos + vector2d(0, 32));
		}
	}

	void dragitemicon::dragdraw(vector2d cursor)
	{
		if (drag)
		{
			itemicon::draw(cursor + rel + vector2d(0, 32));
		}
	}

	void dragitemicon::ondrop()
	{
		switch (type)
		{
		default:
			resetdrag();
		}
	}

	void dragitemicon::setdrag(vector2d cursor, vector2d parentpos)
	{
		rel = pos + parentpos - cursor;
		drag = true;
		alpha = 0.5f;
	}

	void dragitemicon::resetdrag()
	{
		drag = false;
		alpha = 1.0f;
	}
}
