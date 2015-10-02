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
#include "equipinventory.h"
#include "Journey.h"

namespace io
{
	equipinventory::equipinventory(player* plc)
	{
		iconpositions[1] = vector2d(43, 25);
		iconpositions[2] = vector2d(43, 91);
		iconpositions[3] = vector2d(43, 68);
		iconpositions[4] = vector2d(109, 91);
		iconpositions[5] = vector2d(43, 124);
		iconpositions[6] = vector2d(43, 157);
		iconpositions[7] = vector2d(76, 190);
		iconpositions[8] = vector2d(10, 157);
		iconpositions[9] = vector2d(142, 124);
		iconpositions[10] = vector2d(142, 124);
		iconpositions[11] = vector2d(109, 124);
		iconpositions[12] = vector2d(109, 157);
		iconpositions[13] = vector2d(142, 157);
		iconpositions[15] = vector2d(109, 91);
		iconpositions[16] = vector2d(142, 91);
		iconpositions[17] = vector2d(76, 124);
		iconpositions[18] = vector2d(142, 91); //tamed mob
		iconpositions[19] = vector2d(76, 124); //saddle
		iconpositions[49] = vector2d(10, 58);
		iconpositions[50] = vector2d(76, 157);

		app.getimgcache()->setmode(ict_sys);

		node source = nl::nx::nodes["UI"]["UIWindow2.img"]["Equip"]["character"];
		node petsource = nl::nx::nodes["UI"]["UIWindow2.img"]["Equip"]["pet"];

		sprites.push_back(sprite(animation(source["backgrnd"]), vector2d()));
		sprites.push_back(sprite(animation(source["backgrnd2"]), vector2d()));
		sprites.push_back(sprite(animation(source["backgrnd3_Kanna"]), vector2d()));
		sprites.push_back(sprite(animation(source["cashPendant"]), vector2d()));
		sprites.push_back(sprite(animation(source["charmPocket"]), vector2d()));
		sprites.push_back(sprite(animation(source["emblem"]), vector2d()));

		buttons[BT_PETEQUIP] = button(source["BtPet"]);

		petsprites.push_back(texture(petsource["backgrnd"]));
		petsprites.push_back(texture(petsource["backgrnd2"]));
		petsprites.push_back(texture(petsource["backgrnd3"]));

		look = plc->getlook();
		invent = plc->getinventory();
		stats = plc->getstats();

		app.getimgcache()->unlock();

		loadicons();

		position = config.getconfig()->equipsinvpos;
		dimensions = vector2d(184, 290);
		active = true;
		dragged = false;
		buttoncd = 0;
		showpet = false;
	}

	void equipinventory::modify(short slot, char mode, short arg)
	{
		if (mode == 0 || icons.contains(slot))
		{
			switch (mode)
			{
			case 0:
				addicon(slot);
				break;
			case 2:
				icons.changekey(slot, arg);
				icons.get(arg)->setposition(iconpositions[arg]);
				break;
			case 3:
				icons.removekey(slot);
				break;
			}
		}
	}

	void equipinventory::draw()
	{
		uielement::draw();

		if (active)
		{
			if (showpet)
			{
				vector2d petpos = position + vector2d(184, 0);
				for (vector<texture>::iterator petit = petsprites.begin(); petit != petsprites.end(); ++petit)
				{
					petit->draw(petpos);
				}
			}
		}
	}

	void equipinventory::buttonpressed(short id)
	{
		switch (id)
		{
		case BT_PETEQUIP:
			showpet = !showpet;
			buttons[BT_PETEQUIP].setstate(BTS_MOUSEOVER);
			break;
		}
	}

	void equipinventory::oninfo(icon* ico)
	{
		if (ico)
		{
			dragitemicon* dgi = reinterpret_cast<dragitemicon*>(ico);
			app.getui()->showequipinfo(dgi->getid(), dgi->getslot(), true);
		}
		else
		{
			app.getui()->showequipinfo(0, 0, false);
		}
	}

	void equipinventory::sendicon(icon* ico, vector2d pos)
	{
		if (bounds().contains(pos))
		{
			cache.getsounds()->play(MSN_MSENDGRAB);
			ico->resetdrag();
		}
		else
		{
			dragitemicon* dgi = reinterpret_cast<dragitemicon*>(ico);
			char slot = (dgi->getslot() > 0) ? -dgi->getslot() : dgi->getslot();
			packet_c.moveitem(IVT_EQUIPPED, slot, 0, 1);
		}
	}

	void equipinventory::addicon(short slot)
	{
		mapleequip* equip = invent->getequip(IVT_EQUIPPED, slot);
		if (equip)
		{
			int id = equip->getid();
			clothing* cloth = cache.getequips()->getcloth(id);
			if (cloth)
			{
				icons.add(slot, new dragitemicon(IICT_EQUIP, cloth->geticons(), id, slot, 0, iconpositions[slot]));
			}
		}
	}

	void equipinventory::loadicons()
	{
		for (spmit<short, mapleitem*> eqit = invent->getinventory(IVT_EQUIPPED); eqit.belowtop(); ++eqit)
		{
			addicon(eqit.getkey());
		}
	}

	rectangle2d equipinventory::dragarea()
	{
		return rectangle2d(position, position + vector2d(184, 20));
	}
}
