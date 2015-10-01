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
#include "equipcache.h"
#include "Journey.h"

namespace data
{
	void equipcache::init()
	{
		initbodyinfo();
	}

	void equipcache::initbodyinfo()
	{
		node bodynode = nx::nodes["Character"].resolve("00002000.img");
		node headnode = nx::nodes["Character"].resolve("00012000.img");

		for (node animnode = bodynode.begin(); animnode != bodynode.end(); animnode++)
		{
			string state = animnode.name();

			if (animnode.resolve("0").size() > 0)
			{
				for (node framenode = animnode.begin(); framenode != animnode.end(); framenode++)
				{
					byte frame = static_cast<byte>(stoi(framenode.name()));

					short delay = framenode["delay"].istype(integernode) ? framenode["delay"] : 50;

					node actionnode = framenode.resolve("action");
					if (actionnode.istype(stringnode))
					{
						bodyaction action;

						action.state = actionnode.get_string();
						action.delay = (delay < 0) ? -delay : delay;
						action.frame = static_cast<byte>(framenode["frame"]);

						bodyinfo.actions[state][frame] = action;
					}
					else
					{
						bodyinfo.delays[state][frame] = delay;

						for (node partnode = framenode.begin(); partnode != framenode.end(); partnode++)
						{
							string part = partnode.name();
							if (part != "delay" && part != "face")
							{
								charlayer z;
								string zs = partnode.resolve("z").get_string();
								if (zs == "armOverHair")
									z = CL_ARMOHAIR;
								else if (zs == "handOverHair")
									z = CL_RHAND;
								else if (zs == "body" || zs == "backBody")
									z = CL_BODY;
								else if (zs == "handBelowWeapon")
									z = CL_LHAND;
								else if (zs == "arm")
									z = CL_ARM;
								else
									continue;

								node bodymap = partnode["map"];
								for (node mapnode = bodymap.begin(); mapnode != bodymap.end(); mapnode++)
								{
									vector2d shift = vector2d(mapnode.x(), mapnode.y());

									if (mapnode.name() == "neck")
									{
										bodyinfo.facepos[state][frame] = shift;
									}

									bodyinfo.posmap[state][frame][z][mapnode.name()] = shift;
								}
							}
						}

						node headmap = headnode[state][to_string(frame)]["head"]["map"];
						for (node mapnode = headmap.begin(); mapnode != headmap.end(); mapnode++)
						{
							vector2d shift = vector2d(mapnode.x(), mapnode.y());

							if (mapnode.name() == "neck")
								bodyinfo.facepos[state][frame] = bodyinfo.facepos[state][frame] - shift;
							else if (mapnode.name() == "brow")
								bodyinfo.facepos[state][frame] = bodyinfo.facepos[state][frame] + shift;

							bodyinfo.posmap[state][frame][CL_HEAD][mapnode.name()] = shift;
						}
					}
				}
			}
		}
	}

	void equipcache::loadcharlook(maplelook* plook)
	{
		if (!(plook->isloaded()))
		{
			lookinfo* info = plook->getinfo();

			for (map<char, int>::iterator equip = info->equips.begin(); equip != info->equips.end(); equip++)
			{
				int equipid = equip->second;

				if (equipid != 0)
				{
					plook->addcloth(getcloth(equipid));
				}
			}

			for (equiplayer l = EQL_CAP; l <= EQL_MEDAL; l = static_cast<equiplayer>(l + 1))
			{
				if (!plook->getcloth(l))
				{
					plook->addcloth(&emptycloth, l);
				}
			}

			plook->setbody(getbody(info->skin));
			plook->setface(getface(info->faceid));
			plook->sethair(gethair(info->hairid));
			plook->init(&bodyinfo);
		}
	}

	bodytype* equipcache::getbody(char sk)
	{
		if (!bodytypes.count(sk))
		{
			app.getimgcache()->setmode(ict_sys);
			bodytypes[sk] = bodytype(sk, &bodyinfo.posmap);
			app.getimgcache()->unlock();
		}
		return &bodytypes[sk];
	}

	facetype* equipcache::getface(int fid)
	{
		if (!faces.count(fid))
		{
			app.getimgcache()->setmode(ict_sys);
			faces[fid] = facetype(fid);
			app.getimgcache()->unlock();
		}
		return &faces[fid];
	}

	hairstyle* equipcache::gethair(int hid)
	{
		if (!hairstyles.count(hid))
		{
			app.getimgcache()->setmode(ict_sys);
			hairstyles[hid] = hairstyle(hid, &bodyinfo.posmap);
			app.getimgcache()->unlock();
		}
		return &hairstyles[hid];
	}
	
	clothing* equipcache::getcloth(int iid)
	{
		if (!clothes.count(iid))
		{
			app.getimgcache()->setmode(ict_sys);
			clothes[iid] = clothing(iid, &bodyinfo.posmap);
			app.getimgcache()->unlock();
		}
		return &clothes[iid];
	}
}
