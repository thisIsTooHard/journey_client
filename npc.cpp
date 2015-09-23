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
#include "npc.h"
#include "nxfile.h"

namespace maplemap
{
	npc::npc(int id, int o, bool fl, short f, vector2d pos)
	{
		string strid = to_string(id);
		strid.insert(0, 7 - strid.size(), '0');
		strid.append(".img");

		node src = nx::nodes["Npc"][strid];

		string link = src["info"]["link"].tostr();
		if (link.size() > 0)
		{
			src = nx::nodes["Npc"][link];
		}

		map<string, vector<string>> linenames;
		for (node npcnode = src.begin(); npcnode != src.end(); npcnode++)
		{
			string state = npcnode.name();
			if (state == "info")
			{
				hidename = npcnode["hideName"].tobl();
				mouseonly = npcnode["talkMouseOnly"].tobl();
				scripted = npcnode["script"].size() > 0;
			}
			else
			{
				textures[state] = animation(npcnode);
			}

			node speak = npcnode["speak"];
			if (speak.size() > 0)
			{
				for (node speaknode = speak.begin(); speaknode != speak.end(); speaknode++)
				{
					linenames[state].push_back(speaknode.get_string());
				}
			}
		}

		node strsrc = nx::nodes["String"]["Npc.img"][to_string(id)];

		name = strsrc["name"].tostr();
		func = strsrc["func"].tostr();

		for (map<string, vector<string>>::iterator stit = linenames.begin(); stit != linenames.end(); ++stit)
		{
			string state = stit->first;
			vector<string> names = stit->second;
			for (vector<string>::iterator nit = names.begin(); nit != names.end(); ++nit)
			{
				lines[state].push_back(strsrc[*nit].tostr());
			}
		}

		ntag = textlabel(DWF_14BC, TXC_YELLOW, name, TXB_NAMETAG);
		ftag = textlabel(DWF_14BC, TXC_YELLOW, func, TXB_NAMETAG);

		oid = o;
		flip = fl;
		fh = f;
		position = pos;
		state = "stand";
	}

	void npc::draw(vector2d parentpos)
	{
		vector2d absp = parentpos + position;

		graphicobject::draw(&textures[state], absp, flip);

		if (!hidename)
		{
			ntag.draw(absp);
			ftag.draw(absp + vector2d(0, 18));
		}
	}

	void npc::setstate(string st)
	{
		if (state != st)
		{
			state = st;
			resetani();
		}
	}

	void npc::update()
	{
		graphicobject::update(&textures[state]);


	}
}
