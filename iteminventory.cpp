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
#include "iteminventory.h"
#include "Journey.h"

namespace io
{
	iteminventory::iteminventory(inventory* inv)
	{
		page = config.getconfig()->definventory;
		invent = inv;

		topslot = 1;
		botslot = 24;

		loadicons();

		app.getimgcache()->setmode(ict_sys);

		node src = nx::nodes["UI"]["UIWindow2.img"]["Item"];

		sprites.push_back(sprite(src["backgrnd"], vector2d()));
		sprites.push_back(sprite(src["backgrnd2"], vector2d()));
		sprites.push_back(sprite(src["backgrnd3"], vector2d()));

		newitemslot = sprite(src["New"]["inventory"], vector2d());
		newitemtab = sprite(src["New"]["Tab0"], vector2d());
		newitemslot.setspeed(8);
		newitemtab.setspeed(6);

		node taben = src["Tab"]["enabled"];
		node tabdis = src["Tab"]["disabled"];

		buttons[BT_INVENT_EQUIP] = button(texture(tabdis["0"]), texture(taben["0"]), -2, 0);
		buttons[BT_INVENT_USE] = button(texture(tabdis["1"]), texture(taben["1"]), -2, 0);
		buttons[BT_INVENT_ETC] = button(texture(tabdis["2"]), texture(taben["2"]), -2, 0);
		buttons[BT_INVENT_SETUP] = button(texture(tabdis["3"]), texture(taben["3"]), -1, 0);
		buttons[BT_INVENT_CASH] = button(texture(tabdis["4"]), texture(taben["4"]), -2, 0);

		buttons[BT_INVENT_DROPMESO] = button(src["BtCoin"]);
		buttons[BT_INVENT_POINTS] = button(src["BtPoint0"]);
		buttons[BT_INVENT_GATHER] = button(src["BtGather"]);
		buttons[BT_INVENT_SORT] = button(src["BtSort"]);
		buttons[BT_INVENT_EXPAND] = button(src["BtFull"]);
		buttons[BT_INVENT_ITEMPOT] = button(src["BtPot3"]);
		buttons[BT_INVENT_UPGRADE] = button(src["BtUpgrade3"]);
		buttons[BT_INVENT_MAGNIFY] = button(src["BtAppraise3"]);
		buttons[BT_INVENT_BITCASE] = button(src["BtBits3"]);

		buttons[BT_INVENT_SORT].setactive(false);

		switch (page)
		{
		case IVT_EQUIP:
			buttons[BT_INVENT_EQUIP].setstate(BTS_PRESSED);
			break;
		case IVT_USE:
			buttons[BT_INVENT_USE].setstate(BTS_PRESSED);
			break;
		case IVT_SETUP:
			buttons[BT_INVENT_SETUP].setstate(BTS_PRESSED);
			break;
		case IVT_ETC:
			buttons[BT_INVENT_ETC].setstate(BTS_PRESSED);
			break;
		case IVT_CASH:
			buttons[BT_INVENT_CASH].setstate(BTS_PRESSED);
			break;
		}
			
		app.getimgcache()->unlock();

		meso = textlabel(DWF_12R, TXC_BLACK, "");

		position = config.getconfig()->inventorypos;
		dimensions = vector2d(172, 335);
		active = false;
		dragged = false;
		buttoncd = 0;

		newslot = 0;
		newtab = IVT_NONE;
	}

	void iteminventory::buttonpressed(short id)
	{
		inventorytype oldpage = page;
		switch (id)
		{
		case BT_INVENT_EQUIP:
			page = IVT_EQUIP;
			break;
		case BT_INVENT_USE:
			page = IVT_USE;
			break;
		case BT_INVENT_SETUP:
			page = IVT_SETUP;
			break;
		case BT_INVENT_ETC:
			page = IVT_ETC;
			break;
		case BT_INVENT_CASH:
			page = IVT_CASH;
			break;
		}

		if (page != oldpage)
		{
			topslot = 1;
			botslot = 24;

			loadicons();
			buttons[BT_INVENT_EQUIP - 1 + oldpage].setstate(BTS_NORMAL);
		}
	}

	void iteminventory::modify(inventorytype invtype, short slot, char mode, short arg)
	{
		if (page == invtype)
		{
			mapleitem* item = invent->getitem(invtype, slot);

			if (item)
			{
				switch (mode)
				{
				case 0:
					if (page == IVT_EQUIP)
					{
						clothing* cloth = cache.getequips()->getcloth(item->getid());
						if (cloth)
						{
							icons.add(slot, new dragitemicon(IICT_INVENT, cloth->geticons(), item->getid(), slot, 0, iconpos(slot)));
						}
					}
					else
					{
						itemdata* idata = cache.getitems()->getitem(item->getid());
						if (idata)
						{
							icons.add(slot, new dragitemicon(IICT_INVENT, idata->geticons(), item->getid(), 0, item->getcount(), iconpos(slot)));
						}
					}
					break;
				case 1:
					if (icons.contains(slot))
					{
						itemicon* iic = reinterpret_cast<itemicon*>(icons.get(slot));
						iic->setqty(item->getcount());
					}
					break;
				case 2:
					if (icons.contains(slot))
					{
						icons.changekey(slot, arg);
						icons.get(arg)->setposition(iconpos(arg));
					}
					break;
				case 3:
					icons.removekey(slot);
					break;
				}
			}
		}

		if (mode == 0 || mode == 1)
		{
			newslot = slot;
			newtab = invtype;
		}
		else if (newslot == slot && newtab == invtype)
		{
			newslot = 0;
			newtab = IVT_NONE;
		}
	}

	void iteminventory::draw()
	{
		uielement::draw();

		if (active)
		{
			if (newtab == page && newslot > 0)
			{
				if (newslot > 0)
				{
					newitemslot.draw(position + iconpos(newslot) + vector2d(0, 1));
				}
			}
			else if (newtab != IVT_NONE)
			{
				vector2d tabpos;
				switch (newtab)
				{
				case IVT_EQUIP:
					tabpos = vector2d(10, 28);
					break;
				case IVT_USE:
					tabpos = vector2d(42, 28);
					break;
				case IVT_ETC:
					tabpos = vector2d(74, 28);
					break;
				case IVT_SETUP:
					tabpos = vector2d(105, 28);
					break;
				case IVT_CASH:
					tabpos = vector2d(138, 28);
					break;
				default:
					tabpos = vector2d();
				}
				newitemtab.draw(position + tabpos);
			}

			meso.drawline(getmesostr(), position + vector2d(124, 262));
		}
	}

	void iteminventory::update()
	{
		uielement::update();

		newitemslot.update();
		newitemtab.update();
	}

	void iteminventory::sendicon(icon* ico, vector2d pos)
	{
		if (bounds().contains(pos))
		{

		}
		else
		{
			dragitemicon* dgi = reinterpret_cast<dragitemicon*>(ico);
			packet_c.moveitem(page, dgi->getslot(), 0, 1);
		}
	}

	void iteminventory::oninfo(icon* ico)
	{
		if (ico)
		{
			if (ico->gettype() == ICN_ITEM)
			{
				dragitemicon* dgi = reinterpret_cast<dragitemicon*>(ico);
				if (dgi->getslot() > 0)
				{
					app.getui()->showequipinfo(dgi->getid(), dgi->getslot(), false);
				}
				else
				{
					app.getui()->showiteminfo(dgi->getid());
				}
			}
		}
		else
		{
			app.getui()->showequipinfo(0, 0, false);
			app.getui()->showiteminfo(0);
		}
	}

	void iteminventory::loadicons()
	{
		icons.clear();

		for (spmit<short, mapleitem*> itit = invent->getinventory(page); itit.belowtop(); ++itit)
		{
			short slot = itit.getkey();
			if (slot >= topslot && slot <= botslot)
			{
				mapleitem* item = itit.get();
				int id = item->getid();

				if (page == IVT_EQUIP)
				{
					clothing* cloth = cache.getequips()->getcloth(id);
					if (cloth)
					{
						icons.add(slot, new dragitemicon(IICT_INVENT, cloth->geticons(), id, slot, 0, iconpos(slot)));
					}
				}
				else
				{
					itemdata* idata = cache.getitems()->getitem(id);
					if (idata)
					{
						icons.add(slot, new dragitemicon(IICT_INVENT, idata->geticons(), id, 0, item->getcount(), iconpos(slot)));
					}
				}
			}
		}
	}

	string iteminventory::getmesostr()
	{
		string meso = to_string(invent->getmeso());
		size_t pos = meso.size();
		while (pos > 3)
		{
			meso.insert(pos - 3, 1, ',');
			pos -= 3;
		}
		return meso;
	}

	vector2d iteminventory::iconpos(short slot)
	{
		return vector2d(11 + ((slot - 1) % 4) * 36, 51 + ((slot - 1) / 4) * 35);
	}

	rectangle2d iteminventory::dragarea()
	{
		return rectangle2d(position, position + vector2d(172, 20));
	}
}
