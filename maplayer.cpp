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
#include "maplayer.h"

namespace gameplay
{
	maplayer::maplayer(node source)
	{
		node tilesrc = nx::nodes["Map"]["Tile"][source["info"]["tS"] + ".img"];
		node objsrc = nx::nodes["Map"]["Obj"];
		for (node layernode = source.begin(); layernode != source.end(); layernode++)
		{
			if (layernode.name() == "obj")
			{
				for (node objnode = layernode.begin(); objnode != layernode.end(); ++objnode)
				{
					vector2d position = vector2d(objnode["x"], objnode["y"]);
					node bmpnode = objsrc[objnode["oS"] + ".img"][objnode["l0"]][objnode["l1"]][objnode["l2"]];
					int z = objnode["z"];
					objs[z].push_back(sprite(animation(bmpnode), position, true, objnode.resolve("f").get_bool()));
				}
			}
			else if (layernode.name() == "tile")
			{
				for (node tilenode = layernode.begin(); tilenode != layernode.end(); ++tilenode)
				{
					node bmpnode = tilesrc[tilenode["u"]][to_string(tilenode["no"].get_integer())];

					tile toadd;
					toadd.pos = vector2d(tilenode["x"], tilenode["y"]);
					toadd.txt = texture(bmpnode);
					int z = bmpnode["z"].istype(integernode) ? bmpnode["z"] : tilenode["zM"];

					tiles[z].push_back(toadd);
				}
			}
		}

	}

	void maplayer::draw(vector2d viewpos)
	{
		for (map<char, vector<sprite>>::iterator lyit = objs.begin(); lyit != objs.end(); ++lyit)
		{
			for (vector<sprite>::iterator objit = lyit->second.begin(); objit != lyit->second.end(); ++objit)
			{
				objit->draw(viewpos);
			}
		}

		for (map<char, vector<tile>>::iterator lyit = tiles.begin(); lyit != tiles.end(); ++lyit)
		{
			for (vector<tile>::iterator tlit = lyit->second.begin(); tlit != lyit->second.end(); ++tlit)
			{
				tlit->draw(viewpos);
			}
		}
	}

	void maplayer::update()
	{
		for (map<char, vector<sprite>>::iterator obj = objs.begin(); obj != objs.end(); ++obj)
		{
			for (vector<sprite>::iterator objit = obj->second.begin(); objit != obj->second.end(); ++objit)
			{
				objit->update();
			}
		}
	}
}
