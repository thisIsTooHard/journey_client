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
#include "Journey.h"

namespace net
{
	void packetcreator::init(session* srv, byte ver)
	{
		server = srv;
		version = ver;
	}

	void packetcreator::send(packet* tosend)
	{
		int sendok = server->dispatch(tosend);
		if (sendok == SOCKET_ERROR)
		{
			//throw new runtime_error("Unexpected Disconnect");
			//quit();
		}
	}

	void packetcreator::c_login(string account, string pass)
	{
		packet p = packet(LOGIN);
		p.writestr(account);
		p.writestr(pass);
		send(&p);
	}

	void packetcreator::accept_tos()
	{
		packet p = packet(ACCEPT_TOS);
		p.writech(1);
		send(&p);
	}

	void packetcreator::pong()
	{
		packet p = packet(PONG);
		send(&p);
	}

	void packetcreator::serverlrequest()
	{
		packet p = packet(SERVER_REQUEST);
		send(&p);
	}

	void packetcreator::charlrequest(char world, char channel)
	{
		packet p = packet(CHARL_REQ);
		p.writech(0);
		p.writech(world);
		p.writech(channel);
		send(&p);
	}

	void packetcreator::deletechar(string pic, int cid)
	{
		packet p = packet(DELETE_CHAR);
		p.writestr(pic);
		p.writeint(cid);
		send(&p);
	}

	void packetcreator::selectchar(int cid)
	{
		packet p = packet(SELECT_CHAR);
		p.writeint(cid);
		p.writestr("68-5D-43-F8-B8-6C, 7A-79-19-8B-31-3F");
		p.writestr("685D43F8_B86C7A79");
		send(&p);
	}

	void packetcreator::registerpic(int cid, string pic)
	{
		packet p = packet(REGISTER_PIC);
		p.writeint(cid);
		p.writestr("68-5D-43-F8-B8-6C, 7A-79-19-8B-31-3F");
		p.writestr("685D43F8_B86C7A79");
		p.writestr(pic);
		send(&p);
	}

	void packetcreator::selectcharpic(int cid, string pic)
	{
		packet p = packet(SELECT_CHAR_PIC);
		p.writestr(pic);
		p.writeint(cid);
		p.writestr("68-5D-43-F8-B8-6C, 7A-79-19-8B-31-3F");
		p.writestr("685D43F8_B86C7A79");
		send(&p);
	}

	void packetcreator::playerlogin(int cid)
	{
		packet p = packet(PLAYER_LOGIN);
		p.writeint(cid);
		send(&p);
	}

	void packetcreator::checkcharname(string name)
	{
		packet p = packet(CHECK_CHARNAME);
		p.writestr(name);
		send(&p);
	}

	void packetcreator::createchar(string name, int job, int face, int hair, int hairc, int skin, int top, int bot, int shoes, int weapon, bool female)
	{
		packet p = packet(CREATE_CHAR);
		p.writestr(name);
		p.writeint(job);
		p.writeint(face);
		p.writeint(hair);
		p.writeint(hairc);
		p.writeint(skin);
		p.writeint(top);
		p.writeint(bot);
		p.writeint(shoes);
		p.writeint(weapon);
		p.writech(female);
		send(&p);
	}

	void packetcreator::writemoves(packet* p, vector<movefragment> moves)
	{
		p->writech(moves.size());

		for (vector<movefragment>::iterator mvit = moves.begin(); mvit != moves.end(); ++mvit)
		{
			p->writech(mvit->command);

			switch (mvit->type)
			{
			case MVT_ABSOLUTE:
				p->writesh(mvit->xpos);
				p->writesh(mvit->ypos);
				p->writesh(mvit->xpps);
				p->writesh(mvit->ypps);
				p->writesh(mvit->unk);
				p->writech(mvit->newstate);
				p->writesh(mvit->duration);
				break;
			case MVT_RELATIVE:
				p->writesh(mvit->xpos);
				p->writesh(mvit->ypos);
				p->writech(mvit->newstate);
				p->writesh(mvit->duration);
				break;
			case MVT_CHAIR:
				p->writesh(mvit->xpos);
				p->writesh(mvit->ypos);
				p->writesh(mvit->unk);
				p->writech(mvit->newstate);
				p->writesh(mvit->duration);
				break;
			case MVT_JUMPDOWN:
				p->writesh(mvit->xpos);
				p->writesh(mvit->ypos);
				p->writesh(mvit->xpps);
				p->writesh(mvit->ypps);
				p->writesh(mvit->unk);
				p->writesh(mvit->fh);
				p->writech(mvit->newstate);
				p->writesh(mvit->duration);
				break;
			}
		}
	}

	void packetcreator::moveplayer(vector<movefragment> moves)
	{
		packet p = packet(MOVE_PLAYER);
		p.writelg(0);
		p.writech(0);
		writemoves(&p, moves);
		send(&p);
	}

	void packetcreator::changemap(bool died, int targetid, string targetpname, bool usewheel)
	{
		packet p = packet(CHANGEMAP);
		p.writech(died);
		p.writeint(targetid);
		p.writestr(targetpname);
		p.writech(0);
		p.writesh(usewheel ? 1 : 0);
		send(&p);
	}

	void packetcreator::close_attack(attackinfo attack)
	{
		packet p = packet(CLOSE_ATTACK);
		p.writech(0);

		char numattdmg = 0;
		numattdmg = attack.numattacked;
		numattdmg = numattdmg << 4;
		numattdmg = numattdmg | attack.numdamage;
		p.writech(numattdmg);

		p.writeint(attack.skill);
		if (attack.charge > 0)
		{
			p.writeint(attack.charge);
		}
		p.writelg(0);
		p.writech(attack.display);
		p.writech(attack.direction);
		p.writech(attack.stance);
		p.writech(0);
		p.writech(attack.speed);
		p.writeint(0);

		for (map<int, vector<int>>::iterator attit = attack.mobsdamaged.begin(); attit != attack.mobsdamaged.end(); ++attit)
		{
			p.writeint(attit->first);
			p.writelg(0);
			p.writeint(0);
			p.writesh(0);

			for (vector<int>::iterator dmgit = attit->second.begin(); dmgit != attit->second.end(); ++dmgit)
			{
				p.writeint(*dmgit);
			}

			if (attack.skill != 5221004) {
				p.writeint(0);
			}
		}

		send(&p);
	}

	void packetcreator::general_chat(string text, bool show)
	{
		packet p = packet(GENERAL_CHAT);
		p.writestr(text);
		p.writech(show ? 1 : 0);
		send(&p);
	}

	void packetcreator::moveitem(inventorytype type, short slot, char action, short qty)
	{
		packet p = packet(MOVE_ITEM);
		p.writeint(0);
		p.writech(type);
		p.writesh(slot);
		p.writesh(action);
		p.writesh(qty);
		send(&p);
	}

	void packetcreator::useitem(short slot, int itemid)
	{
		packet p = packet(USE_ITEM);
		p.writeint(0);
		p.writesh(slot);
		p.writeint(itemid);
		send(&p);
	}

	void packetcreator::spendap(maplestat stat)
	{
		packet p = packet(SPEND_AP);
		p.writeint(0);
		p.writeint(static_cast<int32_t>(stat));
		send(&p);
	}

	void packetcreator::movemonster(int oid, short type, byte skillb, byte skill0, byte skill1, byte skill2, byte skill3, byte skill4, vector2d startpos, vector<movefragment> movements)
	{
		packet p = packet(MOVE_MONSTER);
		p.writeint(oid);
		p.writesh(type);
		p.writech(skillb);
		p.writech(skill0);
		p.writech(skill1);
		p.writech(skill2);
		p.writech(skill3);
		p.writech(skill4);
		p.writelg(0);
		p.writech(0);
		p.writeint(0);
		p.writesh(startpos.x());
		p.writesh(startpos.y());
		writemoves(&p, movements);
		send(&p);
	}

	void packetcreator::pickupitem(int32_t oid, vector2d pos)
	{
		packet p = packet(PICKUP_ITEM);
		p.writeint(0);
		p.writech(0);
		p.writesh(static_cast<int16_t>(pos.x()));
		p.writesh(static_cast<int16_t>(pos.y()));
		p.writeint(oid);
		send(&p);
	}
}