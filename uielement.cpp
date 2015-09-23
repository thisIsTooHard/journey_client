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

	void uielement::draw()
	{
		if (active)
		{
			for (vector<sprite>::iterator itspr = sprites.begin(); itspr != sprites.end(); ++itspr)
			{
				itspr->draw(position);
			}
			for (map<short, button>::iterator itbt = buttons.begin(); itbt != buttons.end(); ++itbt)
			{
				itbt->second.draw(position);
			}
			for (map<textid, textfield>::iterator ittxt = textfields.begin(); ittxt != textfields.end(); ++ittxt)
			{
				ittxt->second.draw(position);
			}
			for (vector<dragicon>::iterator itdg = dragicons.begin(); itdg != dragicons.end(); ++itdg)
			{
				itdg->draw(position);
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
			for (map<textid, textfield>::iterator ittxt = textfields.begin(); ittxt != textfields.end(); ++ittxt)
			{
				ittxt->second.update();
			}

			if (buttoncd > 0)
			{
				buttoncd -= DPF;
			}
		}
	}

	mousestate uielement::sendmouse(vector2d pos, mousestate state)
	{
		if (active)
		{
			mousestate ret = state;
			bool iteminfo = false;

			for (vector<dragicon>::iterator dgit = dragicons.begin(); dgit != dragicons.end(); ++dgit)
			{
				if (dgit->bounds(position).contains(pos))
				{
					if (!dgit->dragged())
					{
						switch (state)
						{
						case MST_IDLE:
						case MST_CANCLICK:
						case MST_CANCLICK2:
						case MST_CANGRAB:
							ret = MST_CANGRAB;
							if (dgit->gettype() == DIT_ITEM || dgit->gettype() == DIT_ITEMKEY)
							{
								oniteminfo(dgit._Ptr);
								iteminfo = true;
							}
							break;
						case MST_CLICKING:
							dgit->setdrag(pos, position);
							app.getui()->seticon(dgit._Ptr);
							ret = MST_GRABBING;
							break;
						}
					}

					return ret;
				}
			}

			if (!iteminfo && state != MST_IDLE)
			{
				oniteminfo(0);
			}

			bool anycoll = false;
			for (map<short, button>::iterator itbt = buttons.begin(); itbt != buttons.end(); ++itbt)
			{
				string btst = itbt->second.getstate();
				if (itbt->second.bounds(position).contains(pos) && itbt->second.isactive())
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
							if (buttoncd <= 0)
							{
								itbt->second.setstate("pressed");
								buttonpressed(itbt->first);
								buttoncd = 60;
							}
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
			for (map<textid, textfield>::iterator txtit = textfields.begin(); txtit != textfields.end(); txtit++)
			{
				if (txtit->second.isactive())
				{
					if (txtit->second.bounds(position).contains(pos))
					{
						switch (state)
						{
						case MST_CLICKING:
							txtit->second.setfocus(true);
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
							txtit->second.setfocus(false);
							if (!anytext)
							{
								app.getui()->settextfield(0);
							}
							break;
						}
					}
				}
			}

			if (!anycoll)
			{
				if (dragged)
				{
					if (state == MST_CLICKING)
					{
						position = pos + cursorrel;
					}
					else
					{
						dragged = false;
					}
				}
				else
				{
					switch (state)
					{
					case MST_CANCLICK:
					case MST_CANGRAB:
						ret = MST_IDLE;
						break;
					case MST_CLICKING:
						if (dragarea().contains(pos))
						{
							cursorrel = position - pos;
							dragged = true;
						}
						break;
					}
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
