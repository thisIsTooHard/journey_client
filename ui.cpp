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
#include "softkeyboard.h"
#include "worldselect.h"
#include "charselect.h"
#include "charcreation.h"
#include "statusbar.h"
#include "statusmenu.h"
#include "keyconfig.h"
#include "statsinfo.h"
#include "equipinventory.h"
#include "iteminventory.h"
#include "skillinventory.h"
#include "Journey.h"

namespace io
{
	void ui::init()
	{
		app.getimgcache()->setmode(ict_sys);
		base.init();
		field.init();
		mouse.init();
		equipinfo.init();
		iteminfo.init();
		cache.init();
		app.getimgcache()->unlock();

		focused = 0;
		activetext = 0;
		activeicon = 0;
		activeinfo = 0;

		add(UI_LOGIN);

		active = true;
		shift = false;
		actionsenabled = true;
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
			case UI_INVENTORY:
			case UI_KEYCONFIG:
			case UI_SKILLS:
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
		case UI_SOFTKEYBOARD:
			toadd = new softkeyboard(param);
			focused = toadd;
			break;
		case UI_WORLDSELECT:
			toadd = new worldselect(field.getlogin()->getworld(0)->getchannels(), field.getlogin()->getworld(0)->getchloads());
			break;
		case UI_CHARSEL:
			//audio_p.playsound(MSN_CHARSEL);
			toadd = new charselect(field.getlogin()->getacc());
			break;
		case UI_CREATECHAR:
			toadd = new charcreation(field.getlogin()->getacc()->isfemale());
			break;
		case UI_CHATBAR:
			toadd = new chatbar();
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
			toadd = new statsinfo(field.getplayer()->getstats(), field.getplayer()->getinventory());
			break;
		case UI_EQUIPS:
			toadd = new equipinventory(field.getplayer());
			break;
		case UI_INVENTORY:
			toadd = new iteminventory(field.getplayer()->getinventory());
			break;
		case UI_SKILLS:
			toadd = new skillinventory(field.getplayer()->getskills(), field.getplayer()->getstats());
			break;
		}
		elements.add(type, toadd);
	}

	void ui::remove(uielements type)
	{
		if (activetext)
		{
			activetext->setfocus(false);
		}

		if (activeicon)
		{
			activeicon->resetdrag();
		}

		if (activeinfo)
		{
			activeinfo->setactive(false);
		}

		activetext = 0;
		activeinfo = 0;
		activeicon = 0;

		elements.removekey(type);
	}

	void ui::draw()
	{
		field.draw();
		base.draw(field.getviewpos());
		if (active)
		{
			for (spmit<uielements, uielement*> elit = elements.getit(); elit.belowtop(); ++elit)
			{
				elit->draw();
			}
			if (activeicon)
			{
				activeicon->dragdraw(mouse.getposition());
			}
			if (activeinfo)
			{
				activeinfo->draw(mouse.getposition());
			}
		}
		mouse.draw();
	}

	void ui::update()
	{
		field.update();
		base.update();
		if (active)
		{
			for (spmit<uielements, uielement*> elit = elements.getit(); elit.belowtop(); ++elit)
			{
				elit->update();
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
					case VK_TAB:
						switch (activetext->getid())
						{
						case TXT_ACC:

							break;
						}
						break;
					case VK_RETURN:
						switch (activetext->getid())
						{
						case TXT_ACC:
						case TXT_PASS:
							elements.get(UI_LOGIN)->buttonpressed(BT_LOGIN);
							break;
						case TXT_CHAT:
							packet_c.general_chat(activetext->gettext(), true);
							activetext->settext("");
							break;
						}
						break;
					case VK_SPACE:
						switch (activetext->getid())
						{
						case TXT_CHAT:
							activetext->sendchar(' ');
							break;
						}
						break;
					}
				}
				else
				{
					bool allowspecial = activetext->getid() == TXT_CHAT;

					if (keycode > 47 && keycode < 64)
					{
						char letter = static_cast<char>(keycode);
						if (!shift)
						{
							activetext->sendchar(letter);
						}
						else if (allowspecial)
						{
							letter -= 15;
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
				case VK_TAB:
					app.togglefullscreen();
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
							char elemtype = 0;
							switch (action)
							{
							case KA_CHARSTATS:
								elemtype = UI_STATSINFO;
								break;
							case KA_EQUIPS:
								elemtype = UI_EQUIPS;
								break;
							case KA_INVENTORY:
								elemtype = UI_INVENTORY;
								break;
							case KA_SKILL:
								elemtype = UI_SKILLS;
								break;
							}
							if (elemtype > 0)
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
							if (down)
							{
								field.getplayer()->trysit();
							}
							break;
						case KA_ATTACK:
							if (down)
							{
								field.useattack(0);
							}
							break;
						case KA_PICKUP:
							if (down)
							{
								field.pickup();
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

		if (param == MST_CLICKING && (mouse.getstate() == MST_CANCLICK || mouse.getstate() == MST_IDLE))
		{
			cache.getsounds()->play(MSN_MSCLICK);
		}

		if (focused)
		{
			if (focused->isactive())
			{
				if (focused->bounds().contains(pos))
				{
					mouse.setstate(focused->sendmouse(pos, param));
				}
				else
				{
					mouse.setstate(param);

					if (mouse.getstate() == MST_CANCLICK || mouse.getstate() == MST_CANGRAB)
					{
						mouse.setstate(MST_IDLE);
					}

					if (activeinfo)
					{
						activeinfo = 0;
						equipinfo.clear();
					}

					if (activetext && param == MST_CLICKING)
					{
						activetext->setfocus(false);
						activetext = 0;
					}
				}
				return;
			}
			else
			{
				focused = 0;
			}
		}

		if (activeicon)
		{
			if (param == MST_IDLE)
			{
				uielement* front = 0;
				for (spmit<uielements, uielement*> elit = elements.getit(); elit.belowtop(); ++elit)
				{
					if (elit->bounds().contains(pos) && elit->isactive())
					{
						front = elit.get();
					}
				}

				if (front)
				{
					front->sendicon(activeicon, pos);
				}
				else
				{
					if (activeicon->gettype() == ICN_ITEM)
					{
						dragitemicon* dgi = reinterpret_cast<dragitemicon*>(activeicon);
						switch (dgi->getiitype())
						{
						case IICT_INVENT:
							elements.get(UI_INVENTORY)->sendicon(dgi, pos);
							break;
						case IICT_EQUIP:
							elements.get(UI_EQUIPS)->sendicon(dgi, pos);
							break;
						case IICT_KEY:
							activeicon->ondrop();
							break;
						}
					}
					else
					{
						activeicon->ondrop();
					}
				}
				activeicon = 0;
			}
		}

		uielement* front = 0;
		if (actionsenabled)
		{
			for (spmit<uielements, uielement*> elit = elements.getit(); elit.belowtop(); ++elit)
			{
				if (elit->isdragged())
				{
					front = elit.get();
					break;
				}

				if (elit->bounds().contains(pos) && elit->isactive())
				{
					if (front)
					{
						front->sendmouse(pos, MST_IDLE);
					}

					front = elit.get();
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

			if (activeinfo)
			{
				activeinfo = 0;
				equipinfo.clear();
			}

			if (activetext && param == MST_CLICKING)
			{
				activetext->setfocus(false);
				activetext = 0;
			}
		}
	}

	void ui::showiteminfo(int itemid)
	{
		if (itemid > 0)
		{
			if (itemid != equipinfo.getid())
			{
				itemdata* item = cache.getitems()->getitem(itemid);
				if (item)
				{
					iteminfo.setitem(item);
					activeinfo = &iteminfo;
				}
			}
		}
		else
		{
			activeinfo = 0;
			iteminfo.clear();
		}
	}

	void ui::showequipinfo(int itemid, short slot, bool equipped)
	{
		if (itemid > 0)
		{
			if (itemid != equipinfo.getid() && slot != equipinfo.getslot())
			{
				clothing* cloth = cache.getequips()->getcloth(itemid);
				mapleequip* equip = field.getplayer()->getinventory()->getequip(equipped ? IVT_EQUIPPED : IVT_EQUIP, slot);
				if (cloth && equip)
				{
					equipinfo.setequip(cloth, equip, field.getplayer()->getstats());
					activeinfo = &equipinfo;
				}
			}
		}
		else
		{
			activeinfo = 0;
			equipinfo.clear();
		}
	}

	void ui::sendchat(int cid, bool gm, string txt)
	{
		if (txt.size() > 0)
		{
			string fulltext = "";
			vplayer* vpl = field.getchar(cid);
			if (vpl)
			{
				string fulltext = vpl->getname();
				fulltext.append(": ");
				fulltext.append(txt);

				chatbar* chat = getelement<chatbar>(UI_CHATBAR);
				if (chat)
				{
					chat->sendtext(fulltext, gm);
				}
				base.addchatballoon(cid, 0, fulltext);
			}
		}
	}
}
