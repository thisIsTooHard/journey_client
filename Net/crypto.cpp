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
#include "crypto.h"

namespace net
{
	crypto::crypto(char ver, char* recv, char* send, char loc)
	{
		recvIv = recv;
		sendIv = send;
		version = ver;
		localisation = loc;
	}

	void crypto::clear() 
	{
		delete recvIv;
		delete sendIv;
	}

	char* crypto::sendencrypt(char* bytes, int length)
	{
		char* ret = new char[length + 4];

		int a = (sendIv[3] << 8) | sendIv[2];
		char* header = new char[4];
		a ^= (version);
		int b = a ^ length;
		header[0] = (char)(a % 0x100);
		header[1] = (char)(a / 0x100);
		header[2] = (char)(b % 0x100);
		header[3] = (char)(b / 0x100);

		memcpy(ret, header, 4);
		delete header;

		memcpy(ret + 4, bytes, length);

		updateiv();
		return ret;
	}

	void crypto::updateiv()
	{
		char jrbytes[4] = { 69, 42, 13, 124 };

		for (byte i = 0; i < 4; i++) {
			int value = jrbytes[i] + jrkey[abs(sendIv[3 - i]) / 12];
			value = value - sendIv[i];
			jrbytes[i] = (char)abs((char)value);
			if (jrbytes[i] < 0)
				jrbytes[i] += 128;
		}

		memcpy(sendIv, jrbytes, 4);
	}
}