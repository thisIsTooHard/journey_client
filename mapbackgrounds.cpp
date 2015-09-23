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
#include "mapbackgrounds.h"
#include "Journey.h"

namespace gameplay
{
	mapbackgrounds::mapbackgrounds(node bgnodes)
	{
		node back = nx::nodes["Map"]["Back"];

		vector2d mapwalls = cache.getmap()->getinfo()->getwalls();
		vector2d mapborders = cache.getmap()->getinfo()->getborders();

		for (node backnode = bgnodes.begin(); backnode != bgnodes.end(); ++backnode)
		{
			if (!backnode["bS"].get_string().empty())
			{
				if (backnode["front"].get_bool())
				{
					foregrounds.push_back(background(backnode, back, mapwalls, mapborders));
				}
				else
				{
					backgrounds.push_back(background(backnode, back, mapwalls, mapborders));
				}
			}
		}
	}

	void mapbackgrounds::drawbackgrounds(vector2d viewpos)
	{
		for (vector<background>::iterator back = backgrounds.begin(); back != backgrounds.end(); ++back)
		{
			back->draw(viewpos);
		}
	}

	void mapbackgrounds::drawforegrounds(vector2d viewpos)
	{
		for (vector<background>::iterator fore = foregrounds.begin(); fore != foregrounds.end(); ++fore)
		{
			fore->draw(viewpos);
		}
	}

	void mapbackgrounds::update()
	{
		for (vector<background>::iterator back = backgrounds.begin(); back != backgrounds.end(); ++back)
		{
			back->update();
		}
		for (vector<background>::iterator fore = foregrounds.begin(); fore != foregrounds.end(); ++fore)
		{
			fore->update();
		}
	}
}