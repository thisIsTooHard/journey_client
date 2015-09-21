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
#include "facetype.h"
#include "nxfile.h"

namespace character
{
	facetype::facetype(int faceid)
	{
		node facenode = nx::nodes["Character"]["Face"]["000" + to_string(faceid) + ".img"];

		for (node expnode = facenode.begin(); expnode != facenode.end(); expnode++)
		{
			string state = expnode.name();

			if (state == "default")
			{
				node bmpnode = expnode["face"];

				node brow = bmpnode["map"]["brow"];

				textures[state][0] = texture(bmpnode);
				textures[state][0].shift(vector2d(-brow.x(), -brow.y()));
				delays[state][0] = 2500;
			}
			else if (state != "info")
			{
				for (node framenode = expnode.begin(); framenode != expnode.end(); framenode++)
				{
					string framename = framenode.name();

					if (framename != "delay")
					{
						char frame = static_cast<char>(stoi(framenode.name()));

						node bmpnode = framenode["face"];

						if (bmpnode.istype(bitmapnode))
						{
							node brow = bmpnode["map"]["brow"];
							textures[state][frame] = texture(bmpnode);
							textures[state][frame].shift(vector2d(-brow.x(), -brow.y()));

							node delay = framenode["delay"];
							if (delay.istype(integernode))
							{
								delays[state][frame] = static_cast<short>(delay.get_integer());
							}
							else
							{
								delays[state][frame] = 2500;
							}
						}
					}
					else
					{
						delays[state][0] = static_cast<short>(framenode.get_integer());
					}
				}
			}
		}

		name = nx::nodes["String"]["Eqp.img"]["Eqp"]["Face"][to_string(faceid)]["name"];
	}

	void facetype::draw(string exp, byte frame, vector2d pos)
	{
		textures[exp][frame].draw(pos);
	}
}
