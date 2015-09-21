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
		state_f = "default";
		elapsed_f = 0;
		frame_f = 0;
		faceleft = true;
		loaded = false;
	}

	void maplelook::init(bodydrawinfo* bdi)
	{
		bodyinfo = bdi;
		state = clothes[EQL_WEAPON]->istwo_h() ? "stand2" : "stand1";
		anispeed = 1.0f;
		loaded = true;
	}

	void maplelook::addcloth(clothing* cloth)
	{
		if (cloth)
		{
			addcloth(cloth, cloth->getlayer());
		}
	}

	void maplelook::addcloth(clothing* cloth, equiplayer layer)
	{
		clothes[layer] = cloth;
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
				body->draw(CL_BODY, state, frame, absp);
				clothes[EQL_GLOVES]->draw(CL_GLOVE, state, frame, absp);
				clothes[EQL_SHOES]->draw(CL_SHOES, state, frame, absp);
				clothes[EQL_PANTS]->draw(CL_PANTS, state, frame, absp);
				clothes[EQL_COAT]->draw(CL_TOP, state, frame, absp);
				clothes[EQL_LONGCOAT]->draw(CL_MAIL, state, frame, absp);
				clothes[EQL_CAPE]->draw(CL_CAPE, state, frame, absp);
				body->draw(CL_HEAD, state, frame, absp);
				clothes[EQL_EARRINGS]->draw(CL_EARRINGS, state, frame, absp);

				if (clothes.count(EQL_CAP))
				{
					if (clothes[EQL_CAP]->istransparent())
					{
						hair->draw(CL_BACKHAIR, state, frame, absp);
					}
					else
					{
						hair->draw(CL_BACKHAIRBCAP, state, frame, absp);
						clothes[EQL_CAP]->draw(CL_HAT, state, frame, absp);
					}
				}
				else
				{
					hair->draw(CL_BACKHAIR, state, frame, absp);
				}

				clothes[EQL_SHIELD]->draw(CL_BACKSHIELD, state, frame, absp);
				clothes[EQL_WEAPON]->draw(CL_BACKWEAPON, state, frame, absp);
			}
			else
			{
				hair->draw(CL_HAIRBBODY, state, frame, absp);
				clothes[EQL_CAPE]->draw(CL_CAPE, state, frame, absp);
				clothes[EQL_SHIELD]->draw(CL_SHIELDBBODY, state, frame, absp);
				body->draw(CL_BODY, state, frame, absp);
				clothes[EQL_SHOES]->draw(CL_SHOES, state, frame, absp);
				clothes[EQL_PANTS]->draw(CL_PANTS, state, frame, absp);
				clothes[EQL_COAT]->draw(CL_TOP, state, frame, absp);
				clothes[EQL_LONGCOAT]->draw(CL_MAIL, state, frame, absp);
				body->draw(CL_LHAND, state, frame, absp);
				clothes[EQL_GLOVES]->draw(CL_GLOVE, state, frame, absp);
				hair->draw(CL_HAIR, state, frame, absp);
				clothes[EQL_SHIELD]->draw(CL_SHIELDOHAIR, state, frame, absp);
				clothes[EQL_EARRINGS]->draw(CL_EARRINGS, state, frame, absp);
				body->draw(CL_HEAD, state, frame, absp);
				hair->draw(CL_HAIRSHADE, state, frame, absp);

				vector2d facepos = absp + bodyinfo->facepos[state][frame];
				face->draw(state_f, frame_f, facepos);
				clothes[EQL_FACEACC]->draw(CL_FACEACC, (state_f == "default") ? "blink" : state_f, 0, facepos);
				clothes[EQL_EYEACC]->draw(CL_EYEACC, state, frame, absp);
				clothes[EQL_SHIELD]->draw(CL_SHIELD, state, frame, absp);

				if (clothes.count(EQL_CAP))
				{
					if (clothes[EQL_CAP]->istransparent())
					{
						hair->draw(CL_HAIROHEAD, state, frame, absp);
						hair->draw(CL_BACKHAIR, state, frame, absp);
					}
					else
					{
						hair->draw(CL_BACKHAIRBCAP, state, frame, absp);
						clothes[EQL_CAP]->draw(CL_HAT, state, frame, absp);
					}
				}
				else
				{
					hair->draw(CL_HAIROHEAD, state, frame, absp);
					hair->draw(CL_BACKHAIR, state, frame, absp);
				}

				if (clothes[EQL_WEAPON]->istwo_h())
				{
					clothes[EQL_COAT]->draw(CL_MAILARM, state, frame, absp);
					body->draw(CL_ARM, state, frame, absp);
					clothes[EQL_WEAPON]->draw(CL_WEAPON, state, frame, absp);
				}
				else
				{
					clothes[EQL_WEAPON]->draw(CL_WEAPON, state, frame, absp);
					body->draw(CL_ARM, state, frame, absp);
					clothes[EQL_COAT]->draw(CL_MAILARM, state, frame, absp);
				}
				body->draw(CL_RHAND, state, frame, absp);

				body->draw(CL_ARMOHAIR, state, frame, absp);
				clothes[EQL_WEAPON]->draw(CL_WEAPONOHAND, state, frame, absp);
				body->draw(CL_HANDOWEP, state, frame, absp);
				clothes[EQL_GLOVES]->draw(CL_RGLOVE, state, frame, absp);
				clothes[EQL_WEAPON]->draw(CL_WEAPONOGLOVE, state, frame, absp);
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
				short delay = bodyinfo->delays[state][frame] / anispeed;

				if (elapsed > delay)
				{
					elapsed -= delay;
					frame = (bodyinfo->delays[state].count(frame + 1)) ? frame + 1 : 0;

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
				short delay = bodyinfo->actions[action][actionframe].delay / anispeed;

				if (elapsed > delay)
				{
					elapsed -= delay;
					actionframe = bodyinfo->actions[action].count(actionframe + 1) ? actionframe + 1 : 0;

					if (actionframe > 0)
					{
						frame = bodyinfo->actions[action][actionframe].frame;
						state = bodyinfo->actions[action][actionframe].state;
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

			elapsed_f += 16;

			short delay_f = face->getdelay(state_f, frame_f);
			if (elapsed_f > delay_f)
			{
				elapsed_f -= delay_f;
				frame_f = (frame_f < face->getlastf(state_f)) ? frame_f + 1 : 0;
				if (frame_f == 0)
				{
					if (state_f == "default")
					{
						state_f = "blink";
					}
					else
					{
						state_f = "default";
					}
				}
			}
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
				char atttype = clothes[EQL_WEAPON]->getattack();

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
					char stnum = clothes[EQL_WEAPON]->istwo_h() ? '2' : '1';
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
			state = bodyinfo->actions[action][actionframe].state;
			frame = bodyinfo->actions[action][actionframe].frame;
		}
	}

	void maplelook::setexpression(char id)
	{
		string exp;
		switch (id)
		{
		case 0:
			exp = "hit";
			break;
		case 1:
			exp = "smile";
			break;
		case 2:
			exp = "troubled";
			break;
		case 3:
			exp = "cry";
			break;
		case 4:
			exp = "angry";
			break;
		case 5:
			exp = "bewildered";
			break;
		case 6:
			exp = "stunned";
			break;
		}

		if (exp != state_f)
		{
			frame_f = 0;
			elapsed_f = 0;
			state_f = exp;
		}
	}
}
