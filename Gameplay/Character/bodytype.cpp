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
#include "bodytype.h"
#include "nxfile.h"

namespace character
{
	bodytype::bodytype(char skin, map<string, map<char, map<charlayer, map<string, vector2d>>>>* bodyheadmap)
	{
		string sk;
		if (skin < 10)
		{
			sk.append("0");
		}
		sk.append(to_string(skin));
		node bodynode = nx::nodes["Character"].resolve("000020" + sk + ".img");
		node headnode = nx::nodes["Character"].resolve("000120" + sk + ".img");

		for (node animnode = bodynode.begin(); animnode != bodynode.end(); animnode++)
		{
			string state = animnode.name();

			if (animnode.resolve("0").size() != 0)
			{
				for (node framenode = animnode.begin(); framenode != animnode.end(); framenode++)
				{
					char frame = stoi(framenode.name());

					for (node partnode = framenode.begin(); partnode != framenode.end(); partnode++)
					{
						string part = partnode.name();

						if (part != "delay" && part != "face")
						{
							charlayer z;
							string zs = partnode.resolve("z").get_string();
							if (zs == "armOverHair")
								z = CL_ARMOHAIR;
							else if (zs == "handOverHair")
								z = CL_RHAND;
							else if (zs == "body")
								z = CL_BODY;
							else if (zs == "handBelowWeapon")
								z = CL_LHAND;
							else if (zs == "arm")
								z = CL_ARM;
							else
								continue;

							vector2d shf = bodyheadmap->at(state)[frame][CL_BODY]["navel"] - bodyheadmap->at(state)[frame][z]["navel"];

							textures[z][state][frame] = texture(partnode);
							textures[z][state][frame].shift(shf);
						}

						node headsfnode = headnode.resolve(state + "/" + to_string(frame) + "/head");
						if (headsfnode.istype(bitmapnode))
						{
							vector2d shf = bodyheadmap->at(state)[frame][CL_BODY]["neck"] - bodyheadmap->at(state)[frame][CL_HEAD]["neck"];

							textures[CL_HEAD][state][frame] = texture(headsfnode);
							textures[CL_HEAD][state][frame].shift(shf);
						}
					}
				}
			}
		}

		switch (skin)
		{
		case 0:
			name = "Light";
			break;
		case 1:
			name = "Tan";
			break;
		case 2:
			name = "Dark";
			break;
		case 3:
			name = "Pale";
			break;
		case 4:
			name = "Blue";
			break;
		case 5:
			name = "Green";
			break;
		case 9:
			name = "Grey";
			break;
		case 10:
			name = "Pink";
			break;
		case 11:
			name = "Red";
			break;
		default:
			name = "";
		}
	}
}
