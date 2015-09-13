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
#include "stdfax.h"
#include "packet.h"
#include "session.h"

using namespace std;

namespace net
{
	enum sendops : short {
		LOGIN = 1,
		SERVER_REREQ = 4,
		CHARL_REQ = 5,
		STATUS_REQ = 6,
		ACCEPT_TOS = 7,
		SET_GENDER = 8,
		AFTER_LOGIN = 9,
		REG_PIN = 10,
		SERVER_REQUEST = 11,
		SELECT_CHAR = 19,
		PLAYER_LOGIN = 20,
		CHECK_CHARNAME = 21,
		CREATE_CHAR = 22,
		DELETE_CHAR = 23,
		PONG = 24,
		REGISTER_PIC = 29,
		CHARSEL_WITH_PIC = 30,
		CHANGEMAP = 38,
		MOVE_PLAYER = 41,
		CLOSE_ATTACK = 44,
		USE_ITEM = 72
	};

	class packetcreator
	{
	public:
		packetcreator() {}
		~packetcreator() {}
		void init(session*, byte);
		void c_login(string, string);
		void pong();
		void serverlrequest();
		void banme();
		void charlrequest(char, char);
		void deletechar(string, int);
		void registerpic(int, string);
		void selectcharpic(int, string);
		void selectchar(int);
		void playerlogin(int);
		void checkcharname(string);
		void createchar(string, int, int, int, int, int, int, int, int, int, bool);
		void moveplayer(movefragment);
		void changemap(bool, int, string, bool);
		void close_attack(attackinfo);
		void useitem(short, int);
	private:
		void send(packet*);
		unique_ptr<session> server;
		byte version;
	};
}

