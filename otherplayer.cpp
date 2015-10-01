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
	otherplayer::otherplayer(maplelook lk, int i, byte lv, short jb, string nm, vector2d pos)
	{
		look = lk;
		id = i;
		level = lv;
		job = jb;

		name = textlabel(DWF_14C, TXC_WHITE, nm);
		name.setback(TXB_NAMETAG);

		fx = static_cast<float>(pos.x());
		fy = static_cast<float>(pos.y());
		hspeed = 0.0f;
		vspeed = 0.0f;

		elapsed = 0;
		state = PST_STAND;
	}

	void otherplayer::addmoves(vector<movefragment> moves)
	{
		movements = moves;
	}

	void otherplayer::draw(vector2d viewpos)
	{
		updatemoves();
		vector2d absp = viewpos + getposition();

		look.draw(absp);
		effects.draw(absp);
		name.draw(absp);
	}

	bool otherplayer::update()
	{
		look.update();
		return false;
	}

	void otherplayer::updatemoves()
	{
		if (movements.size() > 0)
		{
			movefragment move = movements[0];
			fx = static_cast<float>(move.xpos);
			fy = static_cast<float>(move.ypos);
			resolvestate(static_cast<playerstate>(move.newstate));

			/*if (movements.size() > 1)
			{
				moveobject::update();
				movefragment next = movements[1];
				hspeed = (static_cast<float>(next.xpos) - fx);
				vspeed = (static_cast<float>(next.ypos) - fy);
			}
			else
			{
				hspeed = static_cast<float>(move.xpps) / 20;
				vspeed = static_cast<float>(move.ypps) / 20;
				moveobject::update();
			}*/

			movements.erase(movements.begin());
		}
	}

	void otherplayer::resolvestate(playerstate pst)
	{
		if (pst % 2 == 0)
		{
			look.setfleft(false);
		}
		else
		{
			pst = static_cast<playerstate>(pst - 1);
			look.setfleft(true);
		}

		switch (pst)
		{
		case PST_STAND:
			look.setstate("stand");
			break;
		case PST_WALK:
			look.setstate("walk");
			break;
		case PST_PRONE:
			look.setstate("prone");
			break;
		case PST_FALL:
			look.setstate("jump");
			break;
		case PST_LADDER:
			look.setstate("ladder");
			break;
		case PST_ROPE:
			look.setstate("rope");
			break;
		case PST_SIT:
			look.setstate("sit");
			break;
		case PST_SWIM:
			look.setstate("fly");
			break;
		case PST_ALERT:
			look.setstate("alert");
			break;
		case PST_DIED:
			look.setstate("dead");
			break;
		//default:
			//throw new runtime_error("Unhandled State!");
		}
	}
}
