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
			layer = EQL_CAP;
			type = "HAT";
			catname = "Cap";
			break;
		case 101:
			category = CL_FACEACC;
			layer = EQL_FACEACC;
			type = "FACE ACCESSORY";
			catname = "Accessory";
			break;
		case 102:
			category = CL_EYEACC;
			layer = EQL_EYEACC;
			type = "EYE ACCESSORY";
			catname = "Accessory";
			break;
		case 103:
			category = CL_EARRINGS;
			layer = EQL_EARRINGS;
			type = "EARRINGS";
			catname = "Accessory";
			break;
		case 104:
			category = CL_TOP;
			layer = EQL_COAT;
			type = "TOP";
			catname = "Coat";
			break;
		case 105:
			category = CL_MAIL;
			layer = EQL_LONGCOAT;
			type = "OVERALL";
			catname = "Longcoat";
			break;
		case 106:
			category = CL_PANTS;
			layer = EQL_PANTS;
			type = "BOTTOM";
			catname = "Pants";
			break;
		case 107:
			category = CL_SHOES;
			layer = EQL_SHOES;
			type = "SHOES";
			catname = "Shoes";
			break;
		case 108:
			category = CL_GLOVE;
			layer = EQL_GLOVES;
			type = "GLOVES";
			catname = "Glove";
			break;
		case 109:
			category = CL_SHIELD;
			layer = EQL_SHIELD;
			type = "SHIELD";
			catname = "Shield";
			break;
		case 110:
			category = CL_CAPE;
			layer = EQL_CAPE;
			type = "CAPE";
			catname = "Cape";
			break;
		case 111:
			category = CL_RING;
			layer = EQL_RING;
			type = "RING";
			catname = "Ring";
			break;
		case 112:
			category = CL_PENDANT;
			layer = EQL_PENDANT;
			type = "PENDANT";
			catname = "Accessory";
			break;
		case 113:
			category = CL_BELT;
			layer = EQL_BELT;
			type = "BELT";
			catname = "Accessory";
			break;
		case 114:
			category = CL_MEDAL;
			layer = EQL_MEDAL;
			type = "MEDAL";
			catname = "Accessory";
			break;
		default:
			if (prefix >= 130 && prefix <= 170)
			{
				category = CL_WEAPON;
				layer = EQL_WEAPON;
				catname = "Weapon";
				
				weptype = static_cast<weapontype>(prefix);
				twohanded = (prefix == 138) || (prefix >= 140 && prefix <= 144);

				switch (prefix)
				{
				case 130:
					type = "ONE-HANDED SWORD";
					break;
				case 131:
					type = "ONE-HANDED AXE";
					break;
				case 132:
					type = "ONE-HANDED MACE";
					break;
				case 133:
					type = "DAGGER";
					break;
				case 137:
					type = "WAND";
					break;
				case 138:
					type = "STAFF";
					break;
				case 140:
					type = "TWO-HANDED SWORD";
					break;
				case 141:
					type = "TWO-HANDED AXE";
					break;
				case 142:
					type = "TWO-HANDED MACE";
					break;
				case 143:
					type = "SPEAR";
					break;
				case 144:
					type = "POLEARM";
					break;
				case 145:
					type = "BOW";
					break;
				case 146:
					type = "CROSSBOW";
					break;
				case 147:
					type = "CLAW";
					break;
				case 148:
					type = "KNUCKLE";
					break;
				case 149:
					type = "GUN";
					break;
				}
			}
			else
			{
				return;
			}
		}

		node equipnode = nx::nodes["Character"].resolve(catname + "/0" + to_string(equipid) + ".img");

		for (node statenode = equipnode.begin(); statenode != equipnode.end(); ++statenode)
		{
			string state = statenode.name();

			if (state == "info")
			{
				icon[false] = texture(statenode["icon"]);
				icon[true] = texture(statenode["iconRaw"]);

				cash = statenode["cash"].get_bool();
				tradeable = statenode["tradeBlock"].istype(integernode) ? !statenode["tradeBlock"].get_bool() : true;
				price = statenode["price"].istype(integernode) ? statenode["price"] : 0;
				slots = statenode["tuc"].istype(integernode) ? static_cast<byte>(statenode["tuc"]) : 0;

				reqstats[MS_LEVEL] = statenode["reqLevel"];
				reqstats[MS_JOB] = statenode["reqJob"];
				reqstats[MS_STR] = statenode["reqSTR"];
				reqstats[MS_DEX] = statenode["reqDEX"];
				reqstats[MS_INT] = statenode["reqINT"];
				reqstats[MS_LUK] = statenode["reqLUK"];

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
								if (mapnode.istype(vectornode))
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

		name = nx::nodes["String"]["Eqp.img"]["Eqp"][catname][to_string(equipid)]["name"];
		desc = nx::nodes["String"]["Eqp.img"]["Eqp"][catname][to_string(equipid)]["desc"];
		itemid = equipid;

		txtargs descargs;
		descargs.text = desc;
		descargs.color = TXC_WHITE;
		desctext = itemtext(descargs, DWF_12LL, vector2d(200, 0));
		hasdesc = desc.size() > 0;

		transparent = (itemid == 1002186);
	}

	clothing::clothing()
	{
		itemid = 0;
		layer = EQL_NONE;
		name = "";
		desc = "";
		type = "";
		hasdesc = false;
		transparent = true;
	}

	float clothing::getwmultiplier()
	{
		if (layer == EQL_WEAPON)
		{
			switch (weptype)
			{
			case WEP_1H_SWORD:
				return 4.0f;
			case WEP_1H_AXE:
			case WEP_1H_MACE:
			case WEP_WAND:
			case WEP_STAFF:
				return 4.4f;
			case WEP_DAGGER:
			case WEP_CROSSBOW:
			case WEP_CLAW:
			case WEP_GUN:
				return 3.6f;
			case WEP_2H_SWORD:
				return 4.6f;
			case WEP_2H_AXE:
			case WEP_2H_MACE:
			case WEP_KNUCKLE:
				return 4.8f;
			case WEP_SPEAR:
			case WEP_POLEARM:
				return 5.0f;
			case WEP_BOW:
				return 3.4f;
			}
		}
		return 0.0f;
	}

	rectangle2d clothing::getrange()
	{
		if (layer == EQL_WEAPON)
		{
			switch (weptype)
			{
			case WEP_1H_SWORD:
			case WEP_1H_AXE:
			case WEP_1H_MACE:
			case WEP_KNUCKLE:
				return rectangle2d(-75, -5, -50, 0);
			case WEP_2H_SWORD:
			case WEP_2H_AXE:
			case WEP_2H_MACE:
				return rectangle2d(-100, -5, -50, 0);
			case WEP_SPEAR:
			case WEP_POLEARM:
				return rectangle2d(-130, -5, -50, 0);
			}
		}
		return rectangle2d();
	}

	string clothing::getdisplayspeed()
	{
		if (isweapon())
		{
			switch (attackspeed)
			{
			case 1:
				return "FAST (1)";
			case 2:
				return "FAST (2)";
			case 3:
				return "FAST (3)";
			case 4:
				return "FAST (4)";
			case 5:
				return "NORMAL (5)";
			case 6:
				return "NORMAL (6)";
			case 7:
				return "SLOW (7)";
			case 8:
				return "SLOW (8)";
			case 9:
				return "SLOW (9)";
			}
		}
		return "";
	}

	string clothing::getdisplaystat(equipstat es)
	{
		switch (es)
		{
		case ES_STR:
			return "STR";
		case ES_DEX:
			return "DEX";
		case ES_INT:
			return "INT";
		case ES_LUK:
			return "LUK";
		case ES_WATK:
			return "WEAPON ATT";
		case ES_WDEF:
			return "WEAPON DEFENSE";
		case ES_MAGIC:
			return "MAGIC ATT";
		case ES_MDEF:
			return "MAGIC DEFENSE";
		case ES_ACC:
			return "ACCURACY";
		case ES_AVOID:
			return "AVOID";
		case ES_HP:
			return "MAX HP";
		case ES_MP:
			return "MAX MP";
		case ES_HANDS:
			return "HANDS";
		case ES_SPEED:
			return "SPEED";
		case ES_JUMP:
			return "JUMP";
		}
		return "";
	}
}
