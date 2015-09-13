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
#include "clothing.h"
#include "nxfile.h"

namespace character
{
	clothing::clothing(int equipid, map<string, map<byte, map<charlayer, map<string, vector2d>>>>* bodyheadmap)
	{
		charlayer category;
		string catname;
		int prefix = equipid / 10000;

		switch (prefix)
		{
		case 100:
			category = CL_HAT;
			catname = "Cap";
			break;
		case 101:
			category = CL_FACEACC;
			catname = "Accessory";
			break;
		case 102:
			category = CL_EYEACC;
			catname = "Accessory";
			break;
		case 103:
			category = CL_EARRINGS;
			catname = "Accessory";
			break;
		case 104:
			category = CL_TOP;
			catname = "Coat";
			break;
		case 105:
			category = CL_MAIL;
			catname = "Longcoat";
			break;
		case 106:
			category = CL_PANTS;
			catname = "Pants";
			break;
		case 107:
			category = CL_SHOES;
			catname = "Shoes";
			break;
		case 108:
			category = CL_GLOVE;
			catname = "Glove";
			break;
		case 109:
			category = CL_SHIELD;
			catname = "Shield";
			break;
		case 110:
			category = CL_CAPE;
			catname = "Cape";
			break;
		default:
			if (prefix >= 130 && prefix <= 170)
			{
				category = CL_WEAPON;
				catname = "Weapon";

				twohanded = (prefix == 138) || (prefix >= 140 && prefix <= 144);
			}
			else
			{
				return;
			}
		}

		string layername;
		switch (category)
		{
		case CL_EARRINGS:
			layername = "Earrings";
			break;
		case CL_FACEACC:
			layername = "FaceAcc";
			break;
		case CL_EYEACC:
			layername = "EyeAcc";
			break;
		default:
			layername = catname;
		}

		node equipnode = nx::nodes["Character"].resolve(catname + "/0" + to_string(equipid) + ".img");

		for (node statenode = equipnode.begin(); statenode != equipnode.end(); ++statenode)
		{
			string state = statenode.name();

			if (state == "info")
			{
				icon.first = texture(statenode["icon"]);
				icon.second = texture(statenode["iconRaw"]);

				cash = statenode["cash"].get_bool();
				tradeable = statenode["tradeBlock"].istype(integernode) ? !statenode["tradeBlock"].get_bool() : true;
				price = statenode["price"].istype(integernode) ? statenode["price"] : 0;
				slots = statenode["tuc"].istype(integernode) ? static_cast<byte>(statenode["tuc"]) : 0;

				reqlevel = statenode["reqLevel"];
				reqjob = statenode["reqJob"];
				reqstr = statenode["reqSTR"];
				reqdex = statenode["reqDEX"];
				reqint = statenode["reqINT"];
				reqluk = statenode["reqLUK"];

				defstats[ES_STR] = statenode["incSTR"].istype(integernode) ? static_cast<short>(statenode["incSTR"]) : 0;
				defstats[ES_DEX] = statenode["incDEX"].istype(integernode) ? static_cast<short>(statenode["incDEX"]) : 0;
				defstats[ES_INT] = statenode["incINT"].istype(integernode) ? static_cast<short>(statenode["incINT"]) : 0;
				defstats[ES_LUK] = statenode["incLUK"].istype(integernode) ? static_cast<short>(statenode["incLUK"]) : 0;
				defstats[ES_WATK] = statenode["incPAD"].istype(integernode) ? static_cast<short>(statenode["incPAD"]) : 0;
				defstats[ES_WDEF] = statenode["incPDD"].istype(integernode) ? static_cast<short>(statenode["incPDD"]) : 0;
				defstats[ES_MAGIC] = statenode["incMAD"].istype(integernode) ? static_cast<short>(statenode["incMAD"]) : 0;
				defstats[ES_MDEF] = statenode["incMDD"].istype(integernode) ? static_cast<short>(statenode["incMDD"]) : 0;
				defstats[ES_HP] = statenode["incMHP"].istype(integernode) ? static_cast<short>(statenode["incMHP"]) : 0;
				defstats[ES_MP] = statenode["incMMP"].istype(integernode) ? static_cast<short>(statenode["incMMP"]) : 0;
				defstats[ES_ACC] = statenode["incACC"].istype(integernode) ? static_cast<short>(statenode["incACC"]) : 0;
				defstats[ES_AVOID] = statenode["incEVA"].istype(integernode) ? static_cast<short>(statenode["incEVA"]) : 0;
				defstats[ES_HANDS] = statenode["incHANDS"].istype(integernode) ? static_cast<short>(statenode["incHANDS"]) : 0;
				defstats[ES_SPEED] = statenode["incSPEED"].istype(integernode) ? static_cast<short>(statenode["incSPEED"]) : 0;
				defstats[ES_JUMP] = statenode["incJUMP"].istype(integernode) ? static_cast<short>(statenode["incJUMP"]) : 0;

				if (catname == "Weapon")
				{
					sfx = statenode["sfx"];
					afterimage = statenode["afterImage"];
					attackspeed = static_cast<byte>(statenode["attackSpeed"]);
					attack = static_cast<byte>(statenode["attack"]);
				}
			}
			else if (state == "default" || state == "backDefault")
			{
				continue;
			}
			else
			{
				for (node framenode = statenode.begin(); framenode != statenode.end(); ++framenode)
				{
					char frame = static_cast<char>(stoi(framenode.name()));

					for (node partnode = framenode.begin(); partnode != framenode.end(); ++partnode)
					{
						string part = partnode.name();

						if (partnode.istype(bitmapnode))
						{
							charlayer z = category;
							if (part == "mailArm")
							{
								z = CL_MAILARM;
							}

							string zs = partnode.resolve("z").get_string();
							if (z == CL_WEAPON)
							{
								if (zs == "weaponOverHand")
									z = CL_WEAPONOHAND;
								else if (zs == "weaponOverGlove")
									z = CL_WEAPONOGLOVE;
								else if (zs == "backWeaponOverShield")
									z = CL_BACKWEAPON;
							}
							else if (z == CL_SHIELD)
							{
								if (zs == "shieldOverHair")
									z = CL_SHIELDOHAIR;
								else if (zs == "shieldBelowBody")
									z = CL_SHIELDBBODY;
								else if (zs == "backShield")
									z = CL_BACKSHIELD;
							}


							vector<string> parentpos;
							vector<vector2d> shiftmap;
							node map = partnode.resolve("map");
							for (node mapnode = map.begin(); mapnode != map.end(); mapnode++)
							{
								if (mapnode.data_type() == node::type::vector)
								{
									parentpos.push_back(mapnode.name());
									shiftmap.push_back(vector2d(mapnode.x(), mapnode.y()));
								}
							}

							vector2d shf;

							switch (z)
							{
							case CL_FACEACC:
								shf = vector2d() - shiftmap[0];
								break;
							case CL_TOP:
							case CL_PANTS:
							case CL_CAPE:
							case CL_SHOES:
							case CL_MAIL:
							case CL_MAILARM:
							case CL_GLOVE:
							case CL_BACKWEAPON:
							case CL_BACKSHIELD:
								shf = bodyheadmap->at(state)[frame][CL_BODY]["navel"] - shiftmap[0];
								break;
							case CL_HAT:
							case CL_EARRINGS:
							case CL_EYEACC:
								shf = bodyheadmap->at(state)[frame][CL_HEAD]["brow"] - bodyheadmap->at(state)[frame][CL_HEAD]["neck"] + bodyheadmap->at(state)[frame][CL_BODY]["neck"] - shiftmap[0];
								break;
							case CL_SHIELD:
							case CL_SHIELDOHAIR:
							case CL_WEAPON:
							case CL_WEAPONOHAND:
							case CL_WEAPONOGLOVE:
								for (vector<string>::iterator it = parentpos.begin(); it != parentpos.end(); it++)
								{
									if (!it->compare("hand"))
									{
										if (bodyheadmap->at(state)[frame].count(CL_ARM))
											shf = shf + bodyheadmap->at(state)[frame][CL_ARM]["hand"] - bodyheadmap->at(state)[frame][CL_ARM]["navel"];
										else if (bodyheadmap->at(state)[frame].count(CL_ARMOHAIR))
											shf = shf + bodyheadmap->at(state)[frame][CL_ARMOHAIR]["hand"] - bodyheadmap->at(state)[frame][CL_ARMOHAIR]["navel"];
									}
									else if (!it->compare("handMove"))
										shf = shf + bodyheadmap->at(state)[frame][CL_LHAND]["handMove"];
								}
								shf = shf + bodyheadmap->at(state)[frame][CL_BODY]["navel"] - shiftmap[0];
								break;
							}

							textures[z][state][frame] = texture(partnode);
							textures[z][state][frame].shift(shf);
						}
					}
				}
			}
		}

		type = layername;
		name = nx::nodes["String"]["Eqp.img"]["Eqp"][catname][to_string(equipid)]["name"];
		desc = nx::nodes["String"]["Eqp.img"]["Eqp"][catname][to_string(equipid)]["desc"];
	}
}
