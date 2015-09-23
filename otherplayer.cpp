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
#include "otherplayer.h"

namespace gameplay
{
	otherplayer::otherplayer(maplelook lk, byte lv, short jb, string nm, vector2d pos)
	{
		look = lk;
		name = textlabel(DWF_14C, TXC_WHITE, nm, TXB_NAMETAG);
		level = lv;
		job = jb;

		fx = static_cast<float>(pos.x());
		fy = static_cast<float>(pos.y());
		hspeed = 0.0f;
		vspeed = 0.0f;

		elapsed = 0;
	}

	void otherplayer::addmoves(vector<movefragment> moves)
	{
		for (vector<movefragment>::iterator mvit = moves.begin(); mvit != moves.end(); ++mvit)
		{
			movements.push_back(*mvit);
		}
	}

	void otherplayer::draw(vector2d viewpos)
	{
		vector2d absp = viewpos + getposition();

		look.draw(absp);
		effects.draw(absp);
		name.draw(absp);
	}

	bool otherplayer::update()
	{
		bool aniend = look.update();

		if (movements.size() > 0)
		{
			movefragment move = *movements.begin();

			switch (move.type)
			{
			case MVT_ABSOLUTE:
				if (elapsed == 0)
				{
					fx = static_cast<float>(move.xpos);
					fy = static_cast<float>(move.ypos);
				}
				hspeed = static_cast<float>(move.xpps) / static_cast<float>(move.duration / 4);
				vspeed = static_cast<float>(move.ypps) / static_cast<float>(move.duration / 4);
				break;
			}

			switch (move.newstate)
			{
			case 2:
				look.setstate("walk");
				look.setfleft(false);
				break;
			case 3:
				look.setstate("walk");
				look.setfleft(true);
				break;
			case 4:
				look.setstate("stand");
				look.setfleft(false);
				break;
			case 5:
				look.setstate("stand");
				look.setfleft(true);
				break;
			case 6:
				look.setstate("jump");
				look.setfleft(false);
				break;
			case 7:
				look.setstate("jump");
				look.setfleft(true);
				break;
			default:
			{
					   int newmove = move.newstate;
					   int newstate = newmove;
			}
			}

			bool moveend = moveobject::update();

			elapsed += DPF;
			if (elapsed >= move.duration)
			{
				movements.erase(movements.begin());
				elapsed = 0;
			}
		}

		return false;
	}
}
