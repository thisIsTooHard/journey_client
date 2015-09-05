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
#include "packet.h"

namespace net
{
	packet::packet(short opc)
	{
		writesh(opc);
	}

	packet::packet(char* recv, int len)
	{
		for (int i = len - 1; i >= 0; i--)
		{
			bytes.push_back(recv[i]);
		}
		opcode = readshort();
	}

	template<class T>
	T packet::readbytes()
	{
		char size = sizeof(T) / sizeof(char);
		if (bytes.size() < size)
			throw new runtime_error("packet error: stack underflow");

		size_t all = 0;
		for (char i = 0; i < size; i++)
		{
			all += static_cast<byte>(bytes.back()) * pow(256, i);
			bytes.pop_back();
		}

		return static_cast<T>(all);
	}

	char packet::readbyte()
	{
		return readbytes<char>();
	}

	bool packet::readbool()
	{
		return readbytes<char>() == 1;
	}

	short packet::readshort()
	{
		return readbytes<short>();
	}

	int packet::readint()
	{
		return readbytes<int>();
	}

	int64_t packet::readlong()
	{
		return readbytes<int64_t>();
	}

	string packet::readascii()
	{
		short length = readshort();
		if (length > bytes.size())
			throw new runtime_error("packet error: stack underflow");
		string ret;
		for (char i = 0; i < length; i++)
		{
			ret.push_back(bytes.back());
			bytes.pop_back();
		}
		return ret;
	}

	string packet::readntascii()
	{
		string ret;

		char letter = bytes.back();
		bytes.pop_back();
		while (letter != '\0')
		{
			ret.push_back(letter);
			letter = bytes.back();
			bytes.pop_back();
		}
		return ret;
	}

	string packet::readpadascii(char length)
	{
		if (length > bytes.size())
			throw new runtime_error("packet error: stack underflow");
		string ret;
		for (char i = 0; i < length; i++)
		{
			ret.push_back(bytes.back());
			bytes.pop_back();
		}
		return ret;
	}

	vector2d packet::readpoint()
	{
		short x = readbytes<short>();
		short y = readbytes<short>();
		return vector2d(x, y);
	}

	char* packet::getbytes()
	{
		return bytes.data();
	}


	int packet::length()
	{
		return bytes.size();
	}


	short packet::getopc()
	{
		return opcode;
	}

	void packet::writebytes(const char* recv, int length)
	{
		for (int i = length - 1; i >= 0; i--)
		{
			bytes.push_back(recv[i]);
		}
	}

	void packet::writelg(int64_t lg)
	{
		for (char i = 0; i < 4; i++)
		{
			bytes.push_back(static_cast<char>(lg));
			lg = lg >> 8;
		}
	}

	void packet::writeint(int integer)
	{
		for (char i = 0; i < 4; i++)
		{
			bytes.push_back(static_cast<char>(integer));
			integer = integer >> 8;
		}
	}

	void packet::writesh(short sh)
	{
		for (char i = 0; i < 2; i++)
		{
			bytes.push_back(static_cast<char>(sh));
			sh = sh >> 8;
		}
	}

	void packet::writebl(bool bl)
	{
		bytes.push_back(bl);
	}

	void packet::writech(char ch)
	{
		bytes.push_back(ch);
	}

	void packet::writestr(string str)
	{
		writesh(str.length());
		for (int i = 0; i < str.length(); i++)
		{
			bytes.push_back(str[i]);
		}
	}
}