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
#include "loginwait.h"
#include "Journey.h"

namespace io
{
	loginwait::loginwait()
	{
		app.getimgcache()->setmode(ict_login);

		node loading = nl::nx::nodes["UI"].resolve("Login.img/Notice/Loading/");

		sprites.push_back(sprite(animation(loading.resolve("backgrnd")), vector2d()));
		sprites.push_back(sprite(animation(loading.resolve("circle")), vector2d(125, 72)));

		app.getimgcache()->unlock();
		position = vector2d(292, 200);
		dimensions = vector2d(282, 144);
		active = true;
		dragged = false;
		buttoncd = 0;
	}
}
