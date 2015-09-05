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

using namespace std;

namespace util
{
	template <typename K, typename V>
	class safeptrmap
	{
	public:
		safeptrmap()
		{
			top = 0;
		}

		~safeptrmap() {}

		V get(K key)
		{
			return stdmap[key];
		}

		V getnext(int i)
		{
			if (i > top)
			{
				return 0;
			}
			else
			{
				K key = keys[i];
				return stdmap[key];
			}
		}

		int getend()
		{
			return top;
		}

		bool contains(K k)
		{
			return stdmap.count(k) > 0;
		}

		void add(K key, V value)
		{
			if (value)
			{
				if (stdmap.count(key))
				{
					removekey(key);
					stdmap[key] = value;
					keys.push_back(key);
					top += 1;
				}
				else
				{
					stdmap[key] = value;
					keys.push_back(key);
					top += 1;
				}
			}
		}

		void remove(int i)
		{
			if (top > 0 && i < top)
			{
				top -= 1;
				delete stdmap[keys[i]];
				stdmap.erase(keys[i]);
				keys.erase(keys.begin() + i);
			}
		}

		void removekey(K key)
		{
			int toremove = -1;
			for (int i = 0; i < top; i++)
			{
				if (keys[i] == key)
				{
					toremove = i;
				}
			}
			if (toremove >= 0)
			{
				remove(toremove);
			}
		}

		void pushtotop(K key)
		{
			int toremove = -1;
			for (int i = 0; i < top; i++)
			{
				if (keys[i] == key)
				{
					toremove = i;
				}
			}
			if (toremove >= 0)
			{
				keys.erase(keys.begin() + toremove);
				keys.push_back(key);
			}
		}

		void clear()
		{
			top = 0;
			for (int i = 0; i < top; i++)
			{
				delete stdmap[keys[i]];
			}
			stdmap.clear();
			keys.clear();
		}
	private:
		vector<K> keys;
		map<K, V> stdmap;
		int top;
	};
}

