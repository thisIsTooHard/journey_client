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
#include "packethandler.h"
#include "Journey.h"

namespace net
{
	class login_result_h : public vhandler
	{
		void login_result_h::handle(packet recv)
		{
			app.getui()->remove(UI_LOGINWAIT);
			int reason = recv.readint();
			if (reason > 0)
			{
				switch (reason)
				{
				case 2:
					app.getui()->add(UI_LOGINNOTICE, 16);
					app.getui()->enableactions();
					return;
				case 7:
					app.getui()->add(UI_LOGINNOTICE, 17);
					app.getui()->enableactions();
					return;
				default:
					app.getui()->add(UI_LOGINNOTICE, reason - 1);
					app.getui()->enableactions();
					return;
				}
			}
			recv.readshort();
			int accid = recv.readint();
			bool female = recv.readbool();
			bool admin = recv.readbool();
			char gmlevel = recv.readbyte();
			if (mapleversion != 62)
			{
				recv.readbyte();
			}
			string accname = recv.readascii();
			recv.readbyte();
			bool muted = recv.readbool();
			int64_t mutedtill = recv.readlong();
			int64_t created = recv.readlong();
			recv.readint();
			short pin = 0;
			if (mapleversion != 62)
			{
				pin = recv.readshort();
			}
			app.getui()->getfield()->getaccount()->init(accid, accname, gmlevel, female, muted, pin);
			packet_c.serverlrequest();
		}
	};

	class ping_h : public vhandler
	{
		void ping_h::handle(packet recv)
		{
			packet_c.pong();
		}
	};

	class serverl_h : public vhandler
	{
		void serverl_h::handle(packet recv)
		{
			char id = recv.readbyte();
			if (id != -1)
			{
				string name = recv.readascii();
				char flag = recv.readbyte();
				string svrmsg = recv.readascii();
				recv.readbyte();
				recv.readbyte();
				recv.readbyte();
				recv.readbyte();
				recv.readbyte();
				char channels = recv.readbyte();
				vector<char> chloads;
				for (char i = 0; i < channels; i++)
				{
					recv.readascii();
					recv.readint();
					chloads.push_back(recv.readbyte());
					recv.readshort();
				}
				app.getui()->getfield()->getworlds()->insert(make_pair(id, world(id, name, flag, svrmsg, channels, chloads)));
				app.getui()->remove(UI_LOGIN);
				app.getui()->add(UI_WORLDSELECT);
				app.getui()->enableactions();
			}
		}
	};

	maplestats getmstats(packet* recv)
	{
		int id = recv->readint();
		string name = recv->readpadascii(13);
		bool female = recv->readbool();
		char skin = recv->readbyte();
		int face = recv->readint();
		int hair = recv->readint();
		vector<int64_t> pets;
		for (char i = 0; i < 3; i++)
		{
			pets.push_back(recv->readlong());
		}

		map<maplestat, short> stats;
		stats[LEVEL] = static_cast<short>(static_cast<byte>(recv->readbyte()));
		stats[JOB] = recv->readshort();
		stats[STR] = recv->readshort();
		stats[DEX] = recv->readshort();
		stats[INT_] = recv->readshort();
		stats[LUK] = recv->readshort();
		stats[HP] = recv->readshort();
		stats[MAXHP] = recv->readshort();
		stats[MP] = recv->readshort();
		stats[MAXMP] = recv->readshort();
		stats[AP] = recv->readshort();
		stats[SP] = recv->readshort();

		int exp = recv->readint();
		short fame = recv->readshort();
		int gachaexp = recv->readint();
		int mapid = recv->readint();
		char spawnp = recv->readbyte();
		recv->readint();
		return maplestats(id, name, female, skin, face, hair, exp, fame, stats, make_pair(mapid, spawnp), pets);
	}

	maplelook getmlook(packet* recv)
	{
		lookinfo info;
		info.female = recv->readbool();
		info.skin = recv->readbyte();
		info.faceid = recv->readint();
		bool mega = recv->readbool();
		info.hairid = recv->readint();

		byte slot = recv->readbyte();
		while (slot != 0xFF)
		{
			info.equips[slot] = recv->readint();
			slot = recv->readbyte();
		}

		slot = recv->readbyte();
		while (slot != 0xFF)
		{
			info.maskedequips[slot] = recv->readint();
			slot = recv->readbyte();
		}

		info.maskedequips[-111] = recv->readint();

		for (char i = 0; i < 3; i++)
		{
			info.petids.push_back(recv->readint());
		}

		return maplelook(info);
	}

	void addcharentry(packet* recv)
	{
		maplestats mstats = getmstats(recv);
		maplelook mlook = getmlook(recv);
		maplechar mchar = maplechar(mstats, mlook);

		bool rankinfo = (mapleversion == 62) ? true : recv->readbool();
		bool notgm = recv->readbool();
		if (notgm)
		{
			int rank = recv->readint();
			int rankmv = recv->readint();
			int jobrank = recv->readint();
			int jobrankmv = recv->readint();
			char rankmc = (rankmv > 0) ? '+' : (rankmv < 0) ? '-' : '=';
			char jobrankmc = (jobrankmv > 0) ? '+' : (jobrankmv < 0) ? '-' : '=';
			mchar.setrankinfo(rank, rankmc, jobrank, jobrankmc);
		}
		app.getui()->getfield()->getaccount()->addchar(mchar);
	}

	class charlist_h : public vhandler
	{
		void charlist_h::handle(packet recv)
		{
			recv.readbyte();
			char numchars = recv.readbyte();
			for (char i = 0; i < numchars; i++)
			{
				addcharentry(&recv);
			}
			char pic = (mapleversion == 62) ? 2 : recv.readbyte();
			char slots = static_cast<char>(recv.readint());
			app.getui()->getfield()->getaccount()->setpicslots(pic, slots);
			app.getui()->remove(UI_WORLDSELECT);
			app.getui()->add(UI_CHARSEL);
			app.getui()->enableactions();
		}
	};

	class charname_response_h : public vhandler
	{
		void charname_response_h::handle(packet recv)
		{
			string name = recv.readascii();
			bool used = recv.readbool();
			app.getui()->getelement(UI_CREATECHAR)->sendbool(used);
			if (used)
			{
				app.getui()->add(UI_LOGINNOTICE, 5);
			}
			app.getui()->enableactions();
		}
	};

	class add_newchar_entry_h : public vhandler
	{
		void add_newchar_entry_h::handle(packet recv)
		{
			char stuff = recv.readbyte();
			if (stuff == 0)
			{
				addcharentry(&recv);
				app.getui()->getelement(UI_CREATECHAR)->deactivate();
				app.getui()->remove(UI_CREATECHAR);
				app.getui()->add(UI_CHARSEL);
				app.getui()->enableactions();
			}
		}
	};
	
	class delchar_response_h : public vhandler
	{
		void delchar_response_h::handle(packet recv)
		{
			int cid = recv.readint();
			bool success = recv.readbool();
			if (success)
			{
				app.getui()->add(io::UI_LOGINNOTICE, 55);
			}
			else
			{
				app.getui()->add(io::UI_LOGINNOTICE, 93);
			}
		}
	};

	class server_ip_h : public vhandler
	{
		void server_ip_h::handle(packet recv)
		{
			recv.readshort();
			vector<byte> addr;
			for (char i = 0; i < 4; i++)
			{
				addr.push_back(recv.readbyte());
			}
			short port = recv.readshort();
			int clientid = recv.readint();
			server.reconnect(addr, port);
			packet_c.playerlogin(clientid);
		}
	};

	class server_message_h : public vhandler
	{
		void server_message_h::handle(packet recv)
		{
			char type = recv.readbyte();
			bool server = recv.readbool();
			if (server)
			{

			}
			else
			{
				recv.writech(server);
				string msg = recv.readascii();
				if (type == 3)
				{
					char channel = recv.readbyte() + 1;
					bool mega = recv.readbool();
				}
				//to do
			}
		}
	};

	class set_field_h : public vhandler
	{
		void set_field_h::handle(packet recv)
		{
			int channel = recv.readint();

			char mode1 = recv.readbyte();
			char mode2 = recv.readbyte();
			if (mode1 == 0 && mode2 == 0)
			{
				recv.readshort();
				recv.readbyte();
				int mapid = recv.readint();
				char portalid = recv.readbyte();
				int64_t timestamp = recv.readlong();
				if (channel == app.getui()->getfield()->getchannel())
				{
					app.getimgcache()->clearcache(ict_map);
					app.getui()->getfield()->setfield(mapid, portalid);
				}
				else
				{
					app.getui()->getfield()->changechannel(channel);
				}
				app.getui()->enableactions();
				return;
			}

			recv.readshort();
			recv.readint();
			recv.readint();
			recv.readint();

			recv.readlong();
			recv.readbyte();

			getmstats(&recv);

			char buddycap = recv.readbyte();
			if (recv.readbool())
			{
				string lname = recv.readascii();
			}
			int meso = recv.readint();

			inventory inv = getinventory(&recv);

			map<int, int> levels;
			map<int, int> m_levels;
			map<int, int> cooldowns;
			map<int, int64_t> expirations;

			short size = recv.readshort();
			for (short i = 0; i < size; i++)
			{
				int skillid = recv.readint();
				levels[skillid] = recv.readint();
				expirations[skillid] = recv.readlong();

				bool fourthjob = ((skillid % 100000) / 10000 == 2);
				if (fourthjob)
				{
					m_levels[skillid] = recv.readint();
				}
				else
				{
					m_levels[skillid] = -1;
				}
			}
			size = recv.readshort();
			for (short i = 0; i < size; i++)
			{
				int skillid = recv.readint();
				cooldowns[skillid] = recv.readshort();
			}
			skillbook skills = skillbook(levels, m_levels, cooldowns, expirations);

			map<short, string> started;
			map<short, pair<short, string>> progress;
			size = recv.readshort();
			for (short i = 0; i < size; i++)
			{
				short qid = recv.readshort();
				string qdata = recv.readascii();
				if (started.count(qid))
				{
					map<short, string>::iterator qend = started.end();
					qend--;
					progress[qend->first] = make_pair(qid, qdata);
					i--;
				}
				else
				{
					started[qid] = qdata;
				}
			}
			map<short, int64_t> completed;
			size = recv.readshort();
			for (short i = 0; i < size; i++)
			{
				short qid = recv.readshort();
				completed[qid] = recv.readlong();
			}
			questlog quests = questlog(started, progress, completed);

			size = recv.readshort();
			for (short i = 0; i < size; i++)
			{
				//minigameinfo, odin doesn't have it
			}

			size = recv.readshort(); //ring info, don't care
			for (short i = 0; i < size; i++)
			{
				recv.readint();
				recv.readpadascii(13);
				recv.readint();
				recv.readint();
				recv.readint();
				recv.readint();
			}
			size = recv.readshort(); //ring info, don't care
			for (short i = 0; i < size; i++)
			{
				recv.readint();
				recv.readpadascii(13);
				recv.readint();
				recv.readint();
				recv.readint();
				recv.readint();
				recv.readint();
			}
			size = recv.readshort(); //ring info, don't care
			for (short i = 0; i < size; i++)
			{
				recv.readint();
				recv.readint();
				recv.readint();
				recv.readshort();
				recv.readint();
				recv.readint();
				recv.readpadascii(13);
				recv.readpadascii(13);
			}

			pair<vector<int>, vector<int>> trockmaps;
			for (char i = 0; i < 15; i++)
			{
				int trmap = recv.readint();
				if (i < 5)
				{
					trockmaps.first.push_back(trmap);
				}
				else
				{
					trockmaps.second.push_back(trmap);
				}
			}

			int bookcover = recv.readint();
			recv.readbyte();
			map<short, char> bookcards;
			size = recv.readshort();
			char mblv;
			for (short i = 0; i < size; i++)
			{
				short qid = recv.readshort();
				mblv = recv.readbyte();
				bookcards.insert(make_pair(qid, mblv));
			}

			size = recv.readshort();
			for (short i = 0; i < size; i++)
			{
				//newyearsinfo, odin doesn't have it
			}

			map<short, string> areainfo;
			size = recv.readshort();
			for (short i = 0; i < size; i++)
			{
				short area = recv.readshort();
				areainfo[area] = recv.readascii();
			}

			recv.readshort();
			int64_t timestamp = recv.readlong();
			app.getui()->remove(UI_CHARSEL);
			app.getimgcache()->clearcache(ict_login);
			app.getui()->getfield()->setplayer(player(app.getui()->getfield()->getaccount()->getplayer(), inv, meso, skills, quests, trockmaps, bookcover, bookcards, areainfo));
			app.getui()->add(UI_STATUSBAR);
			pair<int, char> spawninfo = app.getui()->getfield()->getplayer()->getstats()->getspawninfo();
			app.getui()->getfield()->setfield(spawninfo.first, spawninfo.second);
			app.getui()->enableactions();
		}

		inventory set_field_h::getinventory(packet* recv)
		{
			vector<char> slots;
			for (char i = 0; i < 5; i++)
			{
				slots.push_back(recv->readbyte());
			}
			recv->readlong();
			map<short, mapleequip> equipped;
			map<short, mapleequip> equippedcash;
			map<short, mapleequip> equips;
			for (char i = 0; i < 3; i++)
			{
				short pos = recv->readshort();
				while (pos != 0)
				{
					char type = recv->readbyte();
					int id = recv->readint();
					bool cash = recv->readbool();
					int64_t uniqueid = -1;
					if (cash)
					{
						uniqueid = recv->readlong();
					}
					int64_t expire = recv->readlong();

					char slots = recv->readbyte();
					char level = recv->readbyte();
					map<equipstat, short> stats;
					for (equipstat e = ES_STR; e <= ES_JUMP; e = (equipstat)(e + 1))
					{
						stats[e] = recv->readshort();
					}
					string owner = recv->readascii();
					short flag = recv->readshort();

					char itemlevel = 0;
					short itemexp = 0;
					int vicious = 0;
					if (cash)
					{
						recv->readlong();
						recv->readshort();
					}
					else 
					{
						recv->readbyte();
						itemlevel = recv->readbyte();
						recv->readshort();
						itemexp = recv->readshort();
						vicious = recv->readint();
						recv->readlong();
					}
					recv->readlong();
					recv->readint();

					mapleequip equip = mapleequip(pos, type, id, cash, uniqueid, expire, slots, level, stats, owner, flag, itemlevel, itemexp, vicious);
					switch (i)
					{
					case 0:
						equipped.insert(make_pair(pos, equip));
						break;
					case 1:
						equippedcash.insert(make_pair(pos, equip));
						break;
					case 2:
						equips.insert(make_pair(pos, equip));
						break;
					}

					pos = recv->readshort();
				}
			}
			recv->readshort();

			map<char, mapleitem> useitems;
			map<char, mapleitem> setupitems;
			map<char, mapleitem> etcitems;
			map<char, mapleitem> cashitems;
			for (char i = 0; i < 4; i++)
			{
				char pos = recv->readbyte();
				while (pos != 0)
				{
					char type = recv->readbyte();
					int id = recv->readint();
					bool cash = recv->readbool();
					bool pet = (id >= 5000000 && id <= 5000102);
					int64_t uniqueid = -1;
					if (cash)
					{
						uniqueid = recv->readlong();
					}
					int64_t expire = recv->readlong();

					mapleitem item;
					if (pet)
					{
						string petname = recv->readpadascii(13);
						char petlevel = recv->readbyte();
						short closeness = recv->readshort();
						char fullness = recv->readbyte();
						recv->readlong();
						recv->readint();
						recv->readshort();
						recv->readint();
						item = mapleitem(id, pos, type, cash, uniqueid, expire, petname, petlevel, closeness, fullness);
					}
					else
					{
						short count = recv->readshort();
						string owner = recv->readascii();
						short flag = recv->readshort();
						item = mapleitem(id, count, pos, type, cash, uniqueid, expire, owner, flag);
						if (item.canrecharge())
						{
							recv->readint();
							recv->readint();
						}
					}

					switch (i)
					{
					case 0:
						useitems.insert(make_pair(pos, item));
						break;
					case 1:
						setupitems.insert(make_pair(pos, item));
						break;
					case 2:
						etcitems.insert(make_pair(pos, item));
						break;
					case 3:
						cashitems.insert(make_pair(pos, item));
						break;
					}

					pos = recv->readbyte();
				}
			}
			return inventory(slots, equipped, equippedcash, equips, useitems, setupitems, etcitems, cashitems);
		}
	};

	class keymap_h : public vhandler
	{
		void keymap_h::handle(packet recv)
		{
			recv.readbyte();
			map<char, pair<char, int>> keymap;
			for (char i = 0; i < 90; i++)
			{
				char type = recv.readbyte();
				int action = recv.readint();
				keymap[i] = make_pair(type, action);
			}
			app.getui()->getkeyboard()->init(keymap);
		}
	};

	class skill_macros_h : public vhandler
	{
		void skill_macros_h::handle(packet recv)
		{
			map<string, pair<char, vector<int>>> macros;
			char size = recv.readbyte();
			for (char i = 0; i < size; i++)
			{
				string name = recv.readascii();
				char shout = recv.readbyte();
				vector<int> skills;
				skills.push_back(recv.readint());
				skills.push_back(recv.readint());
				skills.push_back(recv.readint());
				macros.insert(make_pair(name, make_pair(shout, skills)));
			}
			app.getui()->getkeyboard()->addmacros(macros);
		}
	};

	class unhandled : public vhandler
	{
		void unhandled::handle(packet recv)
		{
			//To Do
		}
	};

	class spawn_npc_h : public vhandler
	{
		void spawn_npc_h::handle(packet recv)
		{
			int oid = recv.readint();
			int id = recv.readint();
			short posx = recv.readshort();
			short cy = recv.readshort();
			bool f = recv.readbool();
			short fh = recv.readshort();
			short rx = recv.readshort();
			short ry = recv.readshort();
			app.getui()->getfield()->getmapobjects()->addnpc(oid, npc(id, oid, f, fh, vector2d(posx, cy)));
		}
	};

	class spawn_npc_c_h : public vhandler
	{
		void spawn_npc_c_h::handle(packet recv)
		{
			char mode = recv.readbyte();
			int oid = recv.readint();
			if (mode == 0)
			{

			}
			else
			{
				int id = recv.readint();
				short posx = recv.readshort();
				short cy = recv.readshort();
				bool f = recv.readbool();
				short fh = recv.readshort();
				short rx = recv.readshort();
				short ry = recv.readshort();
				bool minimap = recv.readbool();
				app.getui()->getfield()->getmapobjects()->addnpc(oid, npc(id, oid, f, fh, vector2d(posx, cy)));
			}
		}
	};

	class buddylist_h : public vhandler
	{
		void buddylist_h::handle(packet recv)
		{
			//To Do
		}
	};

	class family_plist_h : public vhandler
	{
		void family_plist_h::handle(packet recv)
		{
			//To Do
		}
	};

	class memo_result_h : public vhandler
	{
		void memo_result_h::handle(packet recv)
		{
			//To Do
		}
	};

	class enable_report_h : public vhandler
	{
		void enable_report_h::handle(packet recv)
		{
			bool report = recv.readbool();
			//do whatever
		}
	};

	class update_skills_h : public vhandler
	{
		void update_skills_h::handle(packet recv)
		{
			recv.readbyte();
			recv.readshort();
			int skillid = recv.readint();
			int level = recv.readint();
			int masterlevel = recv.readint();
			int64_t expire = (mapleversion == 62) ? -1 : recv.readlong();
			app.getui()->getfield()->getplayer()->getskills()->updateskill(skillid, level, masterlevel, expire);
		}
	};

	class week_event_messsage_h : public vhandler
	{
		void week_event_messsage_h::handle(packet recv)
		{
			//To do
		}
	};

	class modify_inventory_h : public vhandler
	{
		void modify_inventory_h::handle(packet recv)
		{
			bool updatetick = recv.readbool();
			char size = recv.readbyte();
			for (char i = 0; i < size; i++)
			{
				char mode = recv.readbyte();
				char invtype = recv.readbyte();
				short pos = recv.readshort(); //if move: oldposition, else position
				short arg;
				char addmove;
				
				if (mode == 1 || mode == 2)
				{
					arg = recv.readshort();
				}

				if ((mode == 2 && (pos < 0 || arg < 0)) || mode == 3 && pos < 0)
				{
					addmove = recv.readbyte();
				}

				switch (mode)
				{
				case 0:
					//additem
					break;
				case 1:
					//quantity
					break;
				case 2:
					//move
					break;
				case 3:
					app.getui()->getfield()->getplayer()->getinventory()->removeitem(static_cast<inventorytype>(invtype), pos);
					break;
				}
			}
		}
	};

	class spawn_mob_h : public vhandler
	{
		void spawn_mob_h::handle(packet recv)
		{
			int oid = recv.readint();
			bool hascontrol = recv.readbool();
			int id = recv.readint();
			vector2d pos = recv.readpoint();
			char stance = recv.readbyte();
			short fh = recv.readshort();
			bool haseffect = recv.readbool();
			char effect = 0;
			if (haseffect)
			{
				effect = recv.readbyte();
			}
			bool fadein = recv.readbool();
			char team = recv.readbyte();
			app.getui()->getfield()->getmobs()->addmob(oid, id, hascontrol, pos, stance, fh, effect, fadein, team);
		}
	};

	class spawn_mob_c_h : public vhandler
	{
		void spawn_mob_c_h::handle(packet recv)
		{
			char aggro = recv.readbyte();
			int oid = recv.readint();
			if (aggro == 0)
			{
				return;
			}
			recv.readbyte();
			int id = recv.readint();
			vector2d pos = recv.readpoint();
			char stance = recv.readbyte();
			short fh = recv.readshort();
			bool haseffect = recv.readbool();
			char effect = 0;
			if (haseffect)
			{
				effect = recv.readbyte();
			}
			bool fadein = recv.readbool();
			char team = recv.readbyte();
			app.getui()->getfield()->getmobs()->addmob(oid, id, true, pos, stance, fh, effect, fadein, team);
		}
	};

	class stats_changed_h : public vhandler
	{
		void stats_changed_h::handle(packet recv)
		{
			bool itemreaction = recv.readbool();
			int updatemask = recv.readint();
			if (updatemask > 0)
			{
				for (char i = 0; i < 20; i++)
				{
					maplestat stat = app.getui()->getfield()->getplayer()->getstats()->statvalue(i);

					if ((updatemask & stat) != 0)
					{
						switch (stat)
						{
						case SKIN:
							app.getui()->getfield()->getplayer()->getstats()->setskin(recv.readshort());
							break;
						case FACE:
							app.getui()->getfield()->getplayer()->getstats()->setface(recv.readint());
							break;
						case HAIR:
							app.getui()->getfield()->getplayer()->getstats()->sethair(recv.readint());
							break;
						case LEVEL:
							app.getui()->getfield()->getplayer()->getstats()->setstat(LEVEL, static_cast<byte>(recv.readbyte()));
							break;
						case EXP:
							app.getui()->getfield()->getplayer()->getstats()->setexp(recv.readint());
							break;
						case FAME:
							app.getui()->getfield()->getplayer()->getstats()->setfame(recv.readint());
							break;
						case MESO:
							app.getui()->getfield()->getplayer()->getstats()->setmeso(recv.readint());
							break;
						default:
							app.getui()->getfield()->getplayer()->getstats()->setstat(stat, recv.readshort());
							break;
						}
					}
				}
			}
			else
			{
				app.getui()->enableactions();
			}
		}
	};

	class clock_h : public vhandler
	{
		void clock_h::handle(packet recv)
		{
			char ctype = recv.readbyte();
			if (ctype == 1)
			{
				char hour = recv.readbyte();
				char minute = recv.readbyte();
				char second = recv.readbyte();
			}
			else if (ctype == 2)
			{
				int time = recv.readint();
			}
			//TO DO
		}
	};

	class toggle_ui_h : public vhandler
	{
		void toggle_ui_h::handle(packet recv)
		{
			bool enable = recv.readbool();
			//app.getui()->setactive(enable);
		}
	};

	void getpet(packet* recv, bool show) //TO DO
	{
		char byte2 = show ? recv->readbyte() : 0;
		int petid = recv->readint();
		string name = recv->readascii();
		int uqid = recv->readint();
		recv->readint();
		vector2d pos = recv->readpoint();
		char stance = recv->readbyte();
		int fh = recv->readint();
	}

	void getring(packet* recv) //TO DO, don't really care
	{
		bool hasring = recv->readbool();
		if (hasring)
		{
			int ringid = recv->readint();
			recv->readint();
			int partnerid = recv->readint();
			recv->readint();
			int itemid = recv->readint();
		}
	}

	void getmarriagering(packet* recv) //TO DO, don't really care
	{
		bool hasring = recv->readbool();
		if (hasring)
		{
			int charid = recv->readint();
			int partnerid = recv->readint();
			int ringid = recv->readint();
		}
	}

	class spawn_player_h : public vhandler
	{
		void spawn_player_h::handle(packet recv)
		{
			int chrid = recv.readint();
			byte level = recv.readbyte();
			string name = recv.readascii();
			string guild = recv.readascii();
			short glogobg = recv.readshort();
			char glogobgcolor = recv.readbyte();
			short glogo = recv.readshort();
			char glogocolor = recv.readbyte();

			recv.skip(8);

			bool morphed = recv.readint() == 2;
			int buffmask1 = recv.readint();
			short buffvalue = 0;
			if (buffmask1 != 0)
			{
				buffvalue = morphed ? recv.readshort() : recv.readbyte();
			}
			int buffmask2 = recv.readint();

			recv.skip(43);

			int mount = recv.readint();

			recv.skip(61);

			short job = recv.readshort();
			maplelook mlook = getmlook(&recv); //for now use only this

			int itemcount = recv.readint(); //count of 5110000, idk 
			int itemeffect = recv.readint();
			int chair = recv.readint();
			vector2d pos = recv.readpoint();
			char stance = recv.readbyte();

			recv.skip(3);

			for (char i = 0; i < 3; i++)
			{
				char available = recv.readbyte();
				if (available == 1)
				{
					getpet(&recv, false);
				}
				else
				{
					break;
				}
			}

			int mtlevel = recv.readint();
			int mtexp = recv.readint();
			int mttired = recv.readint();

			//shop stuff, TO DO
			recv.readbyte();
			//shop stuff end

			bool chalkboard = recv.readbool();
			string chalktext = chalkboard ? recv.readascii() : "";

			recv.skip(3);
			char team = recv.readbyte();

			app.getimgcache()->setmode(ict_sys);
			app.getlookfactory()->loadcharlook(&mlook);
			app.getimgcache()->unlock();

			app.getui()->getfield()->getchars()->addchar(chrid, mlook, level, job, name, pos);
		}
	};

	class remove_player_h : public vhandler
	{
		void remove_player_h::handle(packet recv)
		{
			int cid = recv.readint();
			app.getui()->getfield()->getchars()->removechar(cid);
		}
	};

	vector<movefragment> parsemovement(packet* recv)
	{
		vector<movefragment> movements;
		byte length = recv->readbyte();
		for (byte i = 0; i < length; i++)
		{
			movefragment fragment;
			fragment.command = recv->readbyte();
			switch (fragment.command)
			{
			case 0:
			case 5:
			case 17:
				fragment.type = MVT_ABSOLUTE;
				fragment.xpos = recv->readshort();
				fragment.ypos = recv->readshort();
				fragment.xpps = recv->readshort();
				fragment.ypps = recv->readshort();
				fragment.unk = recv->readshort();
				fragment.newstate = recv->readbyte();
				fragment.duration = recv->readshort();
				break;
			case 1:
			case 2:
			case 6:
			case 12:
			case 13:
			case 16:
				fragment.type = MVT_RELATIVE;
				fragment.xpos = recv->readshort();
				fragment.ypos = recv->readshort();
				fragment.newstate = recv->readbyte();
				fragment.duration = recv->readshort();
				break;
			case 11:
				fragment.type = MVT_CHAIR;
				fragment.xpos = recv->readshort();
				fragment.ypos = recv->readshort();
				fragment.unk = recv->readshort();
				fragment.newstate = recv->readbyte();
				fragment.duration = recv->readshort();
				break;
			case 15:
				fragment.type = MVT_JUMPDOWN;
				fragment.xpos = recv->readshort();
				fragment.ypos = recv->readshort();
				fragment.xpps = recv->readshort();
				fragment.ypps = recv->readshort();
				fragment.unk = recv->readshort();
				fragment.fh = recv->readshort();
				fragment.newstate = recv->readbyte();
				fragment.duration = recv->readshort();
				break;
			case 3:
			case 4:
			case 7:
			case 8:
			case 9:
			case 14: //seems to be unhanded by server so idk
				fragment.type = MVT_NONE;
				break;
			case 10:
				fragment.type = MVT_NONE;
				//change equip
				break;
			}

			if (fragment.type != MVT_NONE)
			{
				movements.push_back(fragment);
			}
		}
		return movements;
	}

	class player_moved_h : public vhandler
	{
		void player_moved_h::handle(packet recv)
		{
			int cid = recv.readint();
			recv.readint();
			vector<movefragment> movements = parsemovement(&recv);
			app.getui()->getfield()->getchars()->movechar(cid, movements);
		}
	};

	class spawn_reactor_h : public vhandler
	{
		void spawn_reactor_h::handle(packet recv)
		{
			int oid = recv.readint();
			int id = recv.readint();
			char state = recv.readbyte();
			vector2d pos = recv.readpoint();
			//app.getui()->getfield()->getmap()->addreactor(oid, id, state, pos);
		}
	};

	class show_mob_hp_h : public vhandler
	{
		void show_mob_hp_h::handle(packet recv)
		{
			int oid = recv.readint();
			char hppercent = recv.readbyte();
			app.getui()->getfield()->getmobs()->sendmobhp(oid, hppercent);
		}
	};

	class kill_mob_h : public vhandler
	{
		void kill_mob_h::handle(packet recv)
		{
 			int oid = recv.readint();
			char animation = recv.readbyte();
			app.getui()->getfield()->getmobs()->killmob(oid, animation);
		}
	};

	class drop_item_from_mapobject_h : public vhandler
	{
		void drop_item_from_mapobject_h::handle(packet recv)
		{
			char mod = recv.readbyte();
			int oid = recv.readint();
			bool meso = recv.readbool();
			int itemid = recv.readint();
			int owner = recv.readint();
			char pickuptype = recv.readbyte();
			vector2d dropto = recv.readpoint();
			vector2d dropfrom;
			recv.readint();
			if (mod != 2)
			{
				dropfrom = recv.readpoint();
				recv.readshort();
			}
			else
			{
				dropfrom = dropto;
			}

			if (!meso)
			{
				int64_t expire = recv.readlong();
			}
			bool playerdrop = recv.readbool();
			app.getui()->getfield()->getdrops()->adddrop(oid, itemid, meso, owner, dropfrom, dropto, pickuptype, playerdrop);
		}
	};

	class remove_mapitem_h : public vhandler
	{
		void remove_mapitem_h::handle(packet recv)
		{
			char anim = recv.readbyte();
			int oid = recv.readint();
			if (anim > 1)
			{
				int cid = recv.readint();
			}
			app.getui()->getfield()->getdrops()->removedrop(oid, anim);
		}
	};

	class move_mob_h : public vhandler
	{
		void move_mob_h::handle(packet recv)
		{
			int oid = recv.readint();
			recv.readbyte();
			char useskill = recv.readbyte();
			char skill = recv.readbyte();
			char skill1 = recv.readbyte();
			char skill2 = recv.readbyte();
			char skill3 = recv.readbyte();
			char skill4 = recv.readbyte();
			vector2d startpos = recv.readpoint();
			//app.getui()->getfield()->getmapobjects()->movemob(oid, movement, fleft);
		}
	};

	class show_status_info_h : public vhandler
	{
		void show_status_info_h::handle(packet recv)
		{
			char mode = recv.readbyte();
			if (mode == 3) //exp
			{
				bool white = recv.readbool();
				int gain = recv.readint();
				bool inchat = recv.readbool();
				int bonus1 = recv.readint();
				recv.readshort();
				int bonus2 = recv.readint();
				bool eventorparty = recv.readbool();
				int bonus3 = recv.readint();
				int bonus4 = recv.readint();
				int bonus5 = recv.readint();
				if (inchat)
				{

				}
				else
				{
					app.getui()->getbase()->addstatusinfo(white, "You have gained experience (+" + to_string(gain) + ")");
				}
			}
		}
	};

	class give_buff_h : public vhandler
	{
		void give_buff_h::handle(packet recv)
		{
			int64_t mask = recv.readlong();
			bool debuff = mask == 0;
			if (debuff)
			{
				mask = recv.readlong();
			}
			//TO DO
		}
	};

	class field_effect_h : public vhandler
	{
		void field_effect_h::handle(packet recv)
		{
			char mode = recv.readbyte();
			if (mode == 1)
			{
				//tremble effect
			}
			else if (mode == 3)
			{
				//show effect
			}
			else if (mode == 4)
			{
				//play sound
			}
			else if (mode == 5)
			{
				//boss hp bar
			}
			else if (mode == 6)
			{
				//play music
			}
		}
	};

	packethandler::packethandler()
	{
		handlers[LOGIN_RESULT] = unique_ptr<vhandler>(new login_result_h());
		handlers[SERVERLIST] = unique_ptr<vhandler>(new serverl_h());
		handlers[CHARLIST] = unique_ptr<vhandler>(new charlist_h());
		handlers[CHARNAME_RESPONSE] = unique_ptr<vhandler>(new charname_response_h());
		handlers[ADD_NEWCHAR_ENTRY] = unique_ptr<vhandler>(new add_newchar_entry_h());
		handlers[DELCHAR_RESPONSE] = unique_ptr<vhandler>(new delchar_response_h());
		handlers[SERVER_IP] = unique_ptr<vhandler>(new server_ip_h());
		handlers[PING] = unique_ptr<vhandler>(new ping_h());
		handlers[SELECT_WORLD] = unique_ptr<vhandler>(new unhandled()); //commonly unused
		handlers[RECOMMENDED_WORLDS] = unique_ptr<vhandler>(new unhandled()); //commonly unused
		handlers[MODIFY_INVENTORY] = unique_ptr<vhandler>(new modify_inventory_h());
		handlers[STATS_CHANGED] = unique_ptr<vhandler>(new stats_changed_h());
		handlers[GIVE_BUFF] = unique_ptr<vhandler>(new give_buff_h());
		handlers[FORCED_STAT_RESET] = unique_ptr<vhandler>(new unhandled()); // recalcstats?
		handlers[UPDATE_SKILLS] = unique_ptr<vhandler>(new update_skills_h());
		handlers[SHOW_STATUS_INFO] = unique_ptr<vhandler>(new show_status_info_h());
		handlers[MEMO_RESULT] = unique_ptr<vhandler>(new memo_result_h());
		handlers[ENABLE_REPORT] = unique_ptr<vhandler>(new enable_report_h());
		handlers[UPDATE_GENDER] = unique_ptr<vhandler>(new unhandled()); //completely useless
		handlers[BUDDY_LIST] = unique_ptr<vhandler>(new buddylist_h());
		handlers[GUILD_OPERATION] = unique_ptr<vhandler>(new unhandled()); //TO DO
		handlers[SERVER_MESSAGE] = unique_ptr<vhandler>(new server_message_h());
		handlers[WEEK_EVENT_MESSAGE] = unique_ptr<vhandler>(new week_event_messsage_h());
		handlers[FIELD_SET_VARIABLE] = unique_ptr<vhandler>(new unhandled()); //odin doesn't have it
		handlers[FAMILY_PRIV_LIST] = unique_ptr<vhandler>(new family_plist_h());
		handlers[CANCEL_RENAME_BY_OTHER] = unique_ptr<vhandler>(new unhandled()); //odin doesn't have it
		handlers[SCRIPT_PROGRESS_MESSAGE] = unique_ptr<vhandler>(new unhandled()); //TO DO
		handlers[SKILL_MACROS] = unique_ptr<vhandler>(new skill_macros_h());
		handlers[SET_FIELD] = unique_ptr<vhandler>(new set_field_h());
		handlers[FIELD_EFFECT] = unique_ptr<vhandler>(new field_effect_h());
		handlers[CLOCK] = unique_ptr<vhandler>(new clock_h());
		handlers[SPAWN_PLAYER] = unique_ptr<vhandler>(new spawn_player_h());
		handlers[REMOVE_PLAYER] = unique_ptr<vhandler>(new remove_player_h());
		handlers[SPAWN_PET] = unique_ptr<vhandler>(new unhandled()); //TO DO
		handlers[PLAYER_MOVED] = unique_ptr<vhandler>(new player_moved_h());
		handlers[SHOW_ITEM_EFFECT] = unique_ptr<vhandler>(new unhandled()); //TO DO
		handlers[SHOW_CHAIR] = unique_ptr<vhandler>(new unhandled()); //TO DO
		handlers[SHOW_FOREIGN_EFFECT] = unique_ptr<vhandler>(new unhandled()); //TO DO
		handlers[LOCK_UI] = unique_ptr<vhandler>(new unhandled()); //not sure what this does
		handlers[TOGGLE_UI] = unique_ptr<vhandler>(new toggle_ui_h());
		handlers[SPAWN_MOB] = unique_ptr<vhandler>(new spawn_mob_h());
		handlers[KILL_MOB] = unique_ptr<vhandler>(new kill_mob_h());
		handlers[SPAWN_MOB_C] = unique_ptr<vhandler>(new spawn_mob_c_h());
		handlers[MOVE_MOB] = unique_ptr<vhandler>(new move_mob_h());
		handlers[SHOW_MOB_HP] = unique_ptr<vhandler>(new show_mob_hp_h());
		handlers[SPAWN_NPC] = unique_ptr<vhandler>(new spawn_npc_h());
		handlers[SPAWN_NPC_C] = unique_ptr<vhandler>(new spawn_npc_c_h());
		handlers[MAKE_NPC_SCRIPTED] = unique_ptr<vhandler>(new unhandled()); // odin doesn't have it so idk
		handlers[DROP_ITEM_FROMOBJECT] = unique_ptr<vhandler>(new drop_item_from_mapobject_h());
		handlers[REMOVE_MAPITEM] = unique_ptr<vhandler>(new remove_mapitem_h());
		handlers[SPAWN_REACTOR] = unique_ptr<vhandler>(new spawn_reactor_h());
		handlers[KEYMAP] = unique_ptr<vhandler>(new keymap_h());
	}

	packethandler::~packethandler() 
	{
		for (map<short, unique_ptr<vhandler>>::iterator hit = handlers.begin(); hit != handlers.end(); hit++)
		{
			hit->second.release();
		}
	}

	void packethandler::process(packet recv)
	{
		short opcode = recv.readshort();
		if (handlers.count(opcode))
		{
			handlers[opcode]->handle(recv);
		}
		else
		{
			throw new runtime_error("packet error: unhandled packet.");
		}
	}
}
