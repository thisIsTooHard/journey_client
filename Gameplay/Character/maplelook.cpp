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
#include "maplelook.h"

namespace gameplay
{
	maplelook::maplelook(lookinfo i)
	{
		info = i;
		position = vector2d();
		action = "";
		actionframe = 0;
		frame = 0;
		elapsed = 0;
		faceleft = true;
		loaded = false;
	}

	void maplelook::init(map<string, map<char, short>> dl, map<string, map<char, bodyaction>> ba, map<string, map<char, map<charlayer, map<string, vector2d>>>> bhm)
	{
		delays = dl;
		bodyactions = ba;
		bodyheadmap = bhm;
		state = clothes["Weapon"].istwo_h() ? "stand2" : "stand1";
		loaded = true;
	}

	void maplelook::draw(ID2D1HwndRenderTarget* target, vector2d parentpos)
	{
		if (loaded)
		{
			vector2d absp = parentpos + position;

			if (!faceleft)
			{
				target->SetTransform(
					D2D1::Matrix3x2F::Scale(
					D2D1::Size(-1.0f, 1.0f),
					D2D1::Point2F(
					static_cast<float>(absp.x()),
					static_cast<float>(absp.y()))));
			}

			hair.draw(CL_HAIRBBODY, state, frame, absp);
			clothes["Cape"].draw(CL_CAPE, state, frame, absp);
			body.draw(CL_BODY, state, frame, absp);
			clothes["Shoes"].draw(CL_SHOES, state, frame, absp);
			clothes["Pants"].draw(CL_PANTS, state, frame, absp);
			clothes["Coat"].draw(CL_TOP, state, frame, absp);
			clothes["Longcoat"].draw(CL_MAIL, state, frame, absp);
			body.draw(CL_LHAND, state, frame, absp);
			clothes["Glove"].draw(CL_GLOVE, state, frame, absp);
			hair.draw(CL_HAIR, state, frame, absp);
			clothes["Earrings"].draw(CL_EARRINGS, state, frame, absp);
			body.draw(CL_HEAD, state, frame, absp);
			face.draw(absp - bodyheadmap[state][frame][CL_HEAD]["neck"] + bodyheadmap[state][frame][CL_BODY]["neck"] + bodyheadmap[state][frame][CL_HEAD]["brow"]);
			hair.draw(CL_HAIRSHADE, state, frame, absp);
			clothes["FaceAcc"].draw(CL_FACEACC, state, frame, absp);
			clothes["EyeAcc"].draw(CL_EYEACC, state, frame, absp);
			clothes["Shield"].draw(CL_SHIELD, state, frame, absp);
			clothes["Weapon"].draw(CL_WEAPON, state, frame, absp);
			body.draw(CL_ARM, state, frame, absp);
			clothes["Coat"].draw(CL_MAILARM, state, frame, absp);
			body.draw(CL_RHAND, state, frame, absp);
			hair.draw(CL_HAIROHEAD, state, frame, absp);
			clothes["Cap"].draw(CL_HAT, state, frame, absp);
			body.draw(CL_ARMOHAIR, state, frame, absp);
			clothes["Weapon"].draw(CL_WEAPONOHAND, state, frame, absp);
			clothes["Glove"].draw(CL_RGLOVE, state, frame, absp);
			clothes["Weapon"].draw(CL_WEAPONOGLOVE, state, frame, absp);
			body.draw(CL_HANDOWEP, state, frame, absp);

			if (!faceleft)
			{
				target->SetTransform(
					D2D1::Matrix3x2F::Scale(
					D2D1::Size(1.0f, 1.0f),
					D2D1::Point2F(
					static_cast<float>(absp.x()),
					static_cast<float>(absp.y()))));
			}
		}
	}

	bool maplelook::update()
	{
		bool aniend = false;

		if (loaded)
		{
			elapsed += 16;

			if (actions.empty())
			{
				short delay = delays[state][frame];

				if (elapsed > delay)
				{
					elapsed -= delay;
					frame = (delays[state].count(frame + 1)) ? frame + 1 : 0;

					if (frame == 0)
					{
						aniend = true;

						if (state == "stabO1")
						{
							state = "stand1";
						}
					}
				}
			}
			else
			{
				short delay = bodyactions[action][actionframe].delay;

				if (elapsed > delay)
				{
					elapsed -= delay;
					actionframe = bodyactions[action].count(actionframe + 1) ? actionframe + 1 : 0;

					if (actionframe > 0)
					{
						frame = bodyactions[action][actionframe].frame;
						state = bodyactions[action][actionframe].state;
					}
					else
					{
						actions.erase(actions.begin());
						if (actions.empty())
						{
							aniend = true;
							action = "";
							frame = 0;
							state = "stand1";
						}
						else
						{
							action = actions[0];
							state = bodyactions[action][actionframe].state;
							frame = bodyactions[action][actionframe].frame;
						}
					}
				}
			}

			face.update();
		}
		
		return aniend;
	}

	void maplelook::setstate(string st)
	{
		if (actions.empty())
		{
			if (clothes["Weapon"].istwo_h())
			{
				if (st == "stand1")
				{
					st = "stand2";
				}
				else if (st == "walk1")
				{
					st = "walk2";
				}
			}

			if (state != st)
			{
				frame = 0;
				elapsed = 0;
				state = st;
			}
		}
	}

	void maplelook::setactions(vector<string> acts)
	{
		if (acts.size() > 0)
		{
			elapsed = 0;
			actionframe = 0;
			actions = acts;
			action = acts[0];
			actions.erase(actions.begin());
			state = bodyactions[action][actionframe].state;
			frame = bodyactions[action][actionframe].frame;
		}
	}
}
