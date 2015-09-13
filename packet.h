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
#include "vector2d.h"

using namespace std;
using namespace util;

namespace net
{
	class packet
	{
	public:
		packet(short op) { writesh(op); }
		packet() {}
		~packet() {}
		void skip(size_t);
		string readascii();
		string readntascii();
		string readpadascii(int16_t);
		vector2d readpoint();
		void writebytes(const char*, int);
		void writeheader(const char*);
		void writestr(string);
		int32_t length() { return static_cast<int32_t>(bytes.size()); }
		char* getbytes() { return bytes.data(); }
		bool readbool() { return read<int8_t>() == 1; }
		int8_t readbyte() { return read<int8_t>(); }
		int16_t readshort() { return read<int16_t>(); }
		int32_t readint() { return read<int32_t>(); }
		int64_t readlong() { return read<int64_t>(); }
		void writech(int8_t c) { bytes.push_back(c); }
		void writesh(int16_t s) { write<int16_t>(s); }
		void writeint(int32_t i) { write<int32_t>(i); }
		void writelg(int64_t l) { write<int64_t>(l); }
	private:
		vector<char> bytes;

		template <class T>
		T read()
		{
			size_t all = 0;

			int8_t size = sizeof(T) / sizeof(int8_t);
			if (bytes.size() < size)
			{
				throw new runtime_error("packet error: stack underflow");
			}
			else
			{
				for (int8_t i = 0; i < size; i++)
				{
					all += static_cast<uint8_t>(bytes.back()) * static_cast<size_t>(pow(256, i));
					bytes.pop_back();
				}
			}

			return static_cast<T>(all);
		}

		template <class T>
		void write(T num)
		{
			int8_t size = sizeof(T) / sizeof(int8_t);

			for (int8_t i = 0; i < size; i++)
			{
				bytes.push_back(static_cast<int8_t>(num));
				num = num >> 8;
			}
		}
	};
}
