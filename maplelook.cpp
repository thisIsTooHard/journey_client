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

	void maplelook::init(map<string, map<byte, short>> dl, map<string, map<byte, bodyaction>> ba)
	{
		delays = dl;
		bodyactions = ba;
		state = clothes["Weapon"].istwo_h() ? "stand2" : "stand1";
		anispeed = 1.0f;
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

			if (state == "ladder" || state == "rope")
			{
				body.draw(CL_BODY, state, frame, absp);
				clothes["Glove"].draw(CL_GLOVE, state, frame, absp);
				clothes["Shoes"].draw(CL_SHOES, state, frame, absp);
				clothes["Pants"].draw(CL_PANTS, state, frame, absp);
				clothes["Coat"].draw(CL_TOP, state, frame, absp);
				clothes["Longcoat"].draw(CL_MAIL, state, frame, absp);
				clothes["Cape"].draw(CL_CAPE, state, frame, absp);
				body.draw(CL_HEAD, state, frame, absp);
				clothes["Earrings"].draw(CL_EARRINGS, state, frame, absp);

				if (clothes.count("Cap"))
				{
					if (clothes["Cap"].getname() == "Transparent Hat" || clothes["Cap"].getname() == "")
					{
						hair.draw(CL_BACKHAIR, state, frame, absp);
					}
					else
					{
						hair.draw(CL_BACKHAIRBCAP, state, frame, absp);
						clothes["Cap"].draw(CL_HAT, state, frame, absp);
					}
				}
				else
				{
					hair.draw(CL_BACKHAIR, state, frame, absp);
				}

				clothes["Shield"].draw(CL_BACKSHIELD, state, frame, absp);
				clothes["Weapon"].draw(CL_BACKWEAPON, state, frame, absp);
			}
			else
			{
				hair.draw(CL_HAIRBBODY, state, frame, absp);
				clothes["Cape"].draw(CL_CAPE, state, frame, absp);
				clothes["Shield"].draw(CL_SHIELDBBODY, state, frame, absp);
				body.draw(CL_BODY, state, frame, absp);
				clothes["Shoes"].draw(CL_SHOES, state, frame, absp);
				clothes["Pants"].draw(CL_PANTS, state, frame, absp);
				clothes["Coat"].draw(CL_TOP, state, frame, absp);
				clothes["Longcoat"].draw(CL_MAIL, state, frame, absp);
				body.draw(CL_LHAND, state, frame, absp);
				clothes["Glove"].draw(CL_GLOVE, state, frame, absp);
				hair.draw(CL_HAIR, state, frame, absp);
				clothes["Shield"].draw(CL_SHIELDOHAIR, state, frame, absp);
				clothes["Earrings"].draw(CL_EARRINGS, state, frame, absp);
				body.draw(CL_HEAD, state, frame, absp);
				hair.draw(CL_HAIRSHADE, state, frame, absp);

				string expression = face.getexp();
				vector2d facepos = absp + face.getshift(state, frame);
				face.draw(facepos);
				clothes["FaceAcc"].draw(CL_FACEACC, (expression == "default") ? "blink" : expression, 0, facepos);
				clothes["EyeAcc"].draw(CL_EYEACC, state, frame, absp);
				clothes["Shield"].draw(CL_SHIELD, state, frame, absp);

				if (clothes.count("Cap"))
				{
					if (clothes["Cap"].getname() == "Transparent Hat" || clothes["Cap"].getname() == "")
					{
						hair.draw(CL_HAIROHEAD, state, frame, absp);
						hair.draw(CL_BACKHAIR, state, frame, absp);
					}
					else
					{
						hair.draw(CL_BACKHAIRBCAP, state, frame, absp);
						clothes["Cap"].draw(CL_HAT, state, frame, absp);
					}
				}
				else
				{
					hair.draw(CL_HAIROHEAD, state, frame, absp);
					hair.draw(CL_BACKHAIR, state, frame, absp);
				}

				if (clothes["Weapon"].istwo_h())
				{
					clothes["Coat"].draw(CL_MAILARM, state, frame, absp);
					body.draw(CL_ARM, state, frame, absp);
					clothes["Weapon"].draw(CL_WEAPON, state, frame, absp);
				}
				else
				{
					clothes["Weapon"].draw(CL_WEAPON, state, frame, absp);
					body.draw(CL_ARM, state, frame, absp);
					clothes["Coat"].draw(CL_MAILARM, state, frame, absp);
				}
				body.draw(CL_RHAND, state, frame, absp);

				body.draw(CL_ARMOHAIR, state, frame, absp);
				clothes["Weapon"].draw(CL_WEAPONOHAND, state, frame, absp);
				body.draw(CL_HANDOWEP, state, frame, absp);
				clothes["Glove"].draw(CL_RGLOVE, state, frame, absp);
				clothes["Weapon"].draw(CL_WEAPONOGLOVE, state, frame, absp);
			}

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

		if (loaded && anispeed > 0.0f)
		{
			elapsed += 16;

			if (action == "")
			{
				short delay = delays[state][frame] / anispeed;

				if (elapsed > delay)
				{
					elapsed -= delay;
					frame = (delays[state].count(frame + 1)) ? frame + 1 : 0;

					if (frame == 0)
					{
						aniend = true;

						if (state == "attack")
						{
							setstate("stand");
						}
					}
				}
			}
			else
			{
				short delay = bodyactions[action][actionframe].delay / anispeed;

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
						aniend = true;
						action = "";
						frame = 0;
						setstate("stand");
					}
				}
			}

			face.update();
		}
		
		return aniend;
	}

	void maplelook::setstate(string st)
	{
		setstate(st, 1.0f);
	}

	void maplelook::setstate(string st, float sp)
	{
		if (action == "")
		{
			if (st == "attack")
			{
				char atttype = clothes["Weapon"].getattack();

				switch (atttype)
				{
				case 1:
					st = (elapsed % 10 > 4) ? "stabO1" : "swingO1";
					break;
				case 2:
					st = (elapsed % 10 > 4) ? "stabT1" : "swingP1";
					break;
				case 5:
					st = (elapsed % 10 > 4) ? "stabT1" : "swingT1";
					break;
				}

				frame = 0;
				elapsed = 0;
				state = st;
				anispeed = sp;
			}
			else
			{
				if (st == "stand" || st == "walk")
				{
					char stnum = clothes["Weapon"].istwo_h() ? '2' : '1';
					st.push_back(stnum);
				}

				if (state != st)
				{
					frame = 0;
					elapsed = 0;
					state = st;
					anispeed = sp;
				}

				if (st == "ladder" || st == "rope")
				{
					anispeed = sp;
				}
			}
		}
	}

	void maplelook::setaction(string act, float sp)
	{
		if (act != "")
		{
			elapsed = 0;
			actionframe = 0;
			anispeed = sp;
			action = act;
			state = bodyactions[action][actionframe].state;
			frame = bodyactions[action][actionframe].frame;
		}
	}
}
