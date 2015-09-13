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
#include "ui.h"
#include "login.h"
#include "loginwait.h"
#include "loginnotice.h"
#include "worldselect.h"
#include "charselect.h"
#include "charcreation.h"
#include "statusbar.h"
#include "statusmenu.h"
#include "keyconfig.h"
#include "statsinfo.h"
#include "equipinventory.h"

namespace io
{
	void ui::init(imagecache* img)
	{
		mouse.init(img);
		base.init();
		field.init();

		//field.playbgm("Sound\\BgmUI.img\\BgmUI.img\\Title.mp3");

		activetext = 0;
		activeicon = 0;
		shift = false;
		actionsenabled = true;
		active = true;
	}

	ui::~ui()
	{
		elements.clear();
	}

	void ui::add(uielements type, char param)
	{
		if (elements.contains(type))
		{
			switch (type)
			{
			case UI_STATSINFO:
			case UI_EQUIPS:
			case UI_SYSTEM:
			case UI_KEYCONFIG:
				elements.pushtotop(type);
				elements.get(type)->togglehide();
				return;
			}
		}

		uielement* toadd = 0;
		switch (type)
		{
		case UI_LOGIN:
			toadd = new login();
			break;
		case UI_LOGINNOTICE:
			toadd = new loginnotice(param);
			break;
		case UI_LOGINWAIT:
			toadd = new loginwait();
			break;
		case UI_WORLDSELECT:
			toadd = new worldselect(field.getworlds()->at(0).getchannels(), field.getworlds()->at(0).getchloads());
			break;
		case UI_CHARSEL:
			toadd = new charselect(field.getaccount());
			break;
		case UI_CREATECHAR:
			toadd = new charcreation(field.getaccount()->isfemale());
			break;
		case UI_STATUSBAR:
			toadd = new statusbar(field.getplayer()->getstats());
			break;
		case UI_SYSTEM:
			toadd = new statusmenu();
			break;
		case UI_KEYCONFIG:
			toadd = new keyconfig(keys.getkeys(), field.getplayer()->getinventory());
			break;
		case UI_STATSINFO:
			toadd = new statsinfo(field.getplayer()->getstats());
			break;
		case UI_EQUIPS:
			toadd = new equipinventory(field.getplayer()->getinventory());
			break;
		}
		elements.add(type, toadd);
	}

	void ui::remove(uielements type)
	{
		elements.removekey(type);
	}

	void ui::draw(ID2D1HwndRenderTarget* target)
	{
		field.draw(target);
		base.draw(target, field.getviewpos());
		if (active)
		{
			for (int i = 0; i < elements.getend(); i++)
			{
				elements.getnext(i)->draw(target);
			}

			if (activeicon)
			{
				activeicon->dragdraw(target, mouse.getposition());
			}
		}
		mouse.draw(target);
	}

	void ui::update()
	{
		field.update();
		base.update();
		if (active)
		{
			for (int i = 0; i < elements.getend(); i++)
			{
				elements.getnext(i)->update();
			}
		}
		mouse.update();
	}

	void ui::sendkey(WPARAM keycode, bool down)
	{
		if (actionsenabled)
		{
			if (activetext)
			{
				if (down)
				{
					switch (keycode)
					{
					case VK_SHIFT:
						shift = true;
						break;
					case VK_BACK:
						activetext->sendchar(0);
						break;
					}
				}
				else
				{
					if (keycode > 47 && keycode < 64)
					{
						char letter = static_cast<char>(keycode);
						if (!shift)
						{
							activetext->sendchar(letter);
						}
					}
					else if (keycode > 64 && keycode < 91)
					{
						char letter = static_cast<char>(keycode);
						if (!shift)
						{
							letter += 32;
						}
						activetext->sendchar(letter);
					}

					switch (keycode)
					{
					case VK_SHIFT:
						shift = false;
						break;
					case VK_LEFT:
						activetext->sendchar(1);
						break;
					case VK_RIGHT:
						activetext->sendchar(2);
						break;
					}
				}
			}
			else
			{
				switch (keycode)
				{
				case VK_LEFT:
					field.getplayer()->key_left(down);
					break;
				case VK_RIGHT:
					field.getplayer()->key_right(down);
					break;
				case VK_UP:
					actionsenabled = field.moveup(down);
					break;
				case VK_DOWN:
					field.getplayer()->key_down(down);
					break;
				default:
					pair<keytype, int> mapping = keys.getaction(static_cast<char>(keycode));
					keytype type = mapping.first;
					int action = mapping.second;
					switch (type)
					{
					case KT_SKILL:
						if (down)
						{
							field.useattack(action);
						}
						break;
					case KT_ITEM:
						field.useitem(action);
						break;
					case KT_CASH:
						break;
					case KT_MENU:
						if (down)
						{
							char elemtype = -1;
							switch (action)
							{
							case KA_CHARSTATS:
								elemtype = UI_STATSINFO;
								break;
							case KA_EQUIPS:
								elemtype = UI_EQUIPS;
								break;
							}

							if (elemtype != -1)
							{
								add(static_cast<uielements>(elemtype));
							}
						}
						break;
					case KT_ACTION:
						switch (action)
						{
						case KA_JUMP:
							field.getplayer()->key_jump(down);
							break;
						case KA_SIT:
							break;
						case KA_ATTACK:
							if (down)
							{
								field.useattack(0);
							}
							break;
						}
						break;
					case KT_FACE:
						field.getplayer()->setexpression(action - 100);
						break;
					case KT_MACRO:
						break;
					}
				}
			}
		}
	}

	void ui::sendmouse(mousestate param, vector2d pos)
	{
		mouse.setposition(pos);

		if (activeicon)
		{
			if (param == MST_IDLE)
			{
				uielement* front = 0;
				for (int i = 0; i < elements.getend(); i++)
				{
					uielement* elit = elements.getnext(i);
					if (util::colliding(pos, elit->bounds()) && elit->isactive())
					{
						front = elit;
					}
				}

				if (front)
				{
					front->sendicon(activeicon, pos);
					activeicon = 0;
				}
				else
				{
					activeicon->resetdrag();
				}
			}
		}

		uielement* front = 0;
		if (actionsenabled)
		{
			for (int i = 0; i < elements.getend(); i++)
			{
				uielement* elit = elements.getnext(i);
				if (util::colliding(pos, elit->bounds()) && elit->isactive())
				{
					if (front)
					{
						front->sendmouse(pos, MST_IDLE);
					}

					front = elit;
				}
			}
		}

		if (front)
		{
			mouse.setstate(front->sendmouse(pos, param));
		}
		else
		{
			mouse.setstate(param);

			if (mouse.getstate() == MST_CANCLICK || mouse.getstate() == MST_CANGRAB)
			{
				mouse.setstate(MST_IDLE);
			}
		}
	}
}
