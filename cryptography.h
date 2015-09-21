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
#include "packet.h"
#include "AES.h"

using namespace std;

namespace net
{
	const bool MAPLECRYPTO = true;

	class cryptography
	{
	public:
		cryptography() {}
		~cryptography() {}
		void init(vector<byte>, vector<byte>, byte, byte);
		void sendencrypt(packet*);
		void recvdecrypt(char*, int, bool);
		int getlength(char*);
		void mapleencrypt(char*, int);
		void mapledecrypt(char*, int);
		void aescrypt(char*, int, bool);
		char rollleft(char, int);
		char rollright(char, int);
		void updateiv(bool);
	private:
		vector<byte> recviv;
		vector<byte> sendiv;
		byte version;
		byte localisation;
		AES cipher;
		mutex decryptlock;
	};
}

