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
#include "hairstyle.h"
#include "nxfile.h"

namespace character
{
	hairstyle::hairstyle(int hairid, map<string, map<byte, map<charlayer, map<string, vector2d>>>>* bodyheadmap)
	{
		node hairnode = nx::nodes["Character"]["Hair"]["000" + to_string(hairid) + ".img"];

		for (node statenode = hairnode.begin(); statenode != hairnode.end(); statenode++)
		{
			string state = statenode.name();

			if (state == "default" || state == "backDefault" || state == "info")
				continue;

			for (node framenode = statenode.begin(); framenode != statenode.end(); framenode++)
			{
				byte frame = static_cast<byte>(stoi(framenode.name()));

				for (node partnode = framenode.begin(); partnode != framenode.end(); partnode++)
				{
					string part = partnode.name();
					charlayer z;

					if (part == "hair")
						z = CL_HAIR;
					else if (part == "hairBelowBody")
						z = CL_HAIRBBODY;
					else if (part == "hairOverHead")
						z = CL_HAIROHEAD;
					else if (part == "hairShade")
						z = CL_HAIRSHADE;
					else if (part == "backHair")
						z = CL_BACKHAIR;
					else if (part == "backHairBelowCap" || "backHairBelowCapWide")
						z = CL_BACKHAIRBCAP;

					if (partnode.istype(bitmapnode))
					{
						vector2d brow = vector2d();
						node brownode = partnode["map"]["brow"];
						if (brownode.istype(vectornode))
							brow = vector2d(static_cast<int>(brownode.x()), static_cast<int>(brownode.y()));

						vector2d shf = bodyheadmap->at(state)[frame][CL_HEAD]["brow"] - bodyheadmap->at(state)[frame][CL_HEAD]["neck"] + bodyheadmap->at(state)[frame][CL_BODY]["neck"] - brow;

						textures[z][state][frame] = texture(partnode);
						textures[z][state][frame].shift(shf);
					}
				}
			}
		}

		name = nx::nodes["String"]["Eqp.img"]["Eqp"]["Hair"][to_string(hairid)]["name"];

		switch (hairid % 10)
		{
		case 0:
			color = "Black";
			break;
		case 1:
			color = "Red";
			break;
		case 2:
			color = "Orange";
			break;
		case 3:
			color = "Blonde";
			break;
		case 4:
			color = "Green";
			break;
		case 5:
			color = "Blue";
			break;
		case 6:
			color = "Violet";
			break;
		case 7:
			color = "Brown";
			break;
		default:
			color = "";
		}
	}
}
