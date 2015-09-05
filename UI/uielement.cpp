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
#include "uielement.h"
#include "Journey.h"

namespace io
{
	void uielement::sendicon(dragicon* icon, vector2d pos)
	{
		icon->resetdrag();
	}

	void uielement::draw(ID2D1HwndRenderTarget* target)
	{
		if (active)
		{
			for (vector<sprite>::iterator itspr = sprites.begin(); itspr != sprites.end(); ++itspr)
			{
				itspr->draw(target, position);
			}
			for (map<short, button>::iterator itbt = buttons.begin(); itbt != buttons.end(); ++itbt)
			{
				itbt->second.draw(target, position);
			}
			for (vector<dragicon>::iterator itdg = dragicons.begin(); itdg != dragicons.end(); ++itdg)
			{
				itdg->draw(target, position);
			}
		}
	}

	void uielement::update()
	{
		if (active)
		{
			for (vector<sprite>::iterator itspr = sprites.begin(); itspr != sprites.end(); ++itspr)
			{
				itspr->update();
			}
		}
	}

	mousestate uielement::sendmouse(vector2d pos, mousestate state)
	{
		if (active)
		{
			mousestate ret = state;
			bool drag = false;

			for (vector<dragicon>::iterator dgit = dragicons.begin(); dgit != dragicons.end(); ++dgit)
			{
				if (colliding(pos, dgit->bounds(), position))
				{
					drag = true;

					if (!dgit->dragged())
					{
						switch (state)
						{
						case MST_IDLE:
						case MST_CANCLICK:
						case MST_CANCLICK2:
							ret = MST_CANGRAB;
							break;
						case MST_CLICKING:
							dgit->setdrag(pos, position);
							app.getui()->seticon(dgit._Ptr);
							ret = MST_GRABBING;
							break;
						}
					}
				}

				if (drag)
				{
					return ret;
				}
			}

			bool anycoll = false;
			for (map<short, button>::iterator itbt = buttons.begin(); itbt != buttons.end(); ++itbt)
			{
				string btst = itbt->second.getstate();
				if (util::colliding(pos, itbt->second.bounds(), position) && itbt->second.isactive())
				{
					anycoll = true;
					switch (state)
					{
					case MST_IDLE:
					case MST_CANCLICK:
						if (btst == "normal")
						{
							itbt->second.setstate("mouseOver");
							ret = MST_CANCLICK;
						}
						break;
					case MST_CLICKING:
						if (btst == "normal" || btst == "mouseOver")
						{
							itbt->second.setstate("pressed");
							buttonpressed(itbt->first);
							ret = MST_CANCLICK;
						}
					}
				}
				else
				{
					switch (state)
					{
					case MST_IDLE:
					case MST_CANCLICK:
						if (btst == "mouseOver")
						{
							itbt->second.setstate("normal");
						}
						break;
					}
				}
			}

			bool anytext = false;
			for (map<short, textfield>::iterator txtit = textfields.begin(); txtit != textfields.end(); txtit++)
			{
				if (util::colliding(pos, txtit->second.bounds(), position))
				{
					switch (state)
					{
					case MST_CLICKING:
						txtit->second.setstate("active");
						app.getui()->settextfield(&txtit->second);
						anytext = true;
						break;
					}
				}
				else
				{
					switch (state)
					{
					case MST_CLICKING:
						txtit->second.setstate("inactive");
						if (!anytext)
						{
							app.getui()->settextfield(0);
						}
						break;
					}
				}
			}

			if (!anycoll)
			{
				switch (state)
				{
				case MST_CANCLICK:
				case MST_CANGRAB:
					ret = MST_IDLE;
					break;
				}
			}

			return ret;
		}
		else
		{
			return state;
		}
	}
}
