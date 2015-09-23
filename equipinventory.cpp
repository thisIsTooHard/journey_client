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
	const vector2d iconpositions[18] = {
		vector2d(10, 24), vector2d(43, 24), vector2d(43, 91), vector2d(109, 91), vector2d(109, 91), vector2d(43, 124), vector2d(43, 157), vector2d(76, 190), vector2d(10, 157), 
		vector2d(142, 124), vector2d(10, 124), vector2d(109, 124), vector2d(76, 124), vector2d(76, 157), vector2d(10, 58), vector2d(10, 24), vector2d(10, 24), vector2d(76, 124)
	};

	equipinventory::equipinventory(player* plc)
	{
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

		for (spmit<short, mapleitem*> eqit = invent->getinventory(IVT_EQUIPPED); eqit.belowtop(); ++eqit)
		{
			short slot = eqit.getkey();
			if (slot >= 0)
			{
				mapleequip* equip = reinterpret_cast<mapleequip*>(eqit.get());
				int id = equip->getid();
				clothing* cloth = cache.getequips()->getcloth(id);
				dragicons.push_back(dragicon(DIT_ITEM, itemicon(cloth->geticons(), false, 1), texture(), iconpositions[slot], slot, id));
			}
		}

		app.getimgcache()->unlock();

		position = config.geteqspos();
		dimensions = vector2d(184, 290);
		active = true;
		dragged = false;
		buttoncd = 0;
		showpet = false;
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
			buttons[BT_PETEQUIP].setstate("mouseOver");
			break;
		}
	}

	void equipinventory::oniteminfo(dragicon* dgi)
	{
		if (dgi)
		{
			app.getui()->showequipinfo(dgi->getaction(), dgi->getkey());
		}
		else
		{
			app.getui()->showequipinfo(0, 0);
		}
	}

	rectangle2d equipinventory::dragarea()
	{
		return rectangle2d(position, position + vector2d(184, 20));
	}
}
