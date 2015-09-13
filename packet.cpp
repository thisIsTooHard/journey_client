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
	void packet::skip(size_t count)
	{
		bytes.resize(bytes.size() - count);
	}

	string packet::readascii()
	{
		int16_t length = read<int16_t>();
		return readpadascii(length);
	}

	string packet::readntascii()
	{
		string ret;

		bool cont;
		do
		{
			char letter = bytes.back();
			bytes.pop_back();

			cont = letter != '\0';
			if (cont)
			{
				ret.push_back(letter);
			}
		} while (cont);

		return ret;
	}

	string packet::readpadascii(int16_t length)
	{
		string ret;

		if (length > bytes.size())
		{
			throw new runtime_error("packet error: stack underflow");
		}
		else
		{
			for (int16_t i = 0; i < length; i++)
			{
				char letter = bytes.back();
				if (letter != '\0')
				{
					ret.push_back(letter);
				}
				bytes.pop_back();
			}
		}

		return ret;
	}

	vector2d packet::readpoint()
	{
		short x = read<int16_t>();
		short y = read<int16_t>();
		return vector2d(x, y);
	}

	void packet::writeheader(const char* recv)
	{
		for (int8_t i = 3; i >= 0; i--)
		{
			bytes.insert(bytes.begin(), recv[i]);
		}
	}

	void packet::writebytes(const char* recv, int32_t length)
	{
		for (int32_t i = length - 1; i >= 0; i--)
		{
			bytes.push_back(recv[i]);
		}
	}

	void packet::writestr(string str)
	{
		int16_t len = static_cast<int16_t>(str.length());

		write<int16_t>(len);
		for (int16_t i = 0; i < len; i++)
		{
			bytes.push_back(str[i]);
		}
	}
}