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
	class spmit
	{
	public:
		spmit(map<K, V>* std, vector<K>* ky, SRWLOCK* lock, int t)
		{
			stdmap = std;
			keys = ky;
			maplock = lock;
			top = t;
			index = 0;
		}

		~spmit()
		{
			ReleaseSRWLockShared(maplock);
		}

		V operator -> ()
		{
			return stdmap->at(keys->at(index));
		}

		V get()
		{
			return stdmap->at(keys->at(index));
		}

		void operator ++ ()
		{
			index++;
		}

		bool belowtop()
		{
			return index < top;
		}

		int getindex()
		{
			return index;
		}

		K getkey()
		{
			return keys->at(index);
		}
	private:
		map<K, V>* stdmap;
		vector<K>* keys;
		SRWLOCK* maplock;
		int index;
		int top;
	};

	template <typename K, typename V>
	class safeptrmap
	{
	public:
		safeptrmap()
		{
			top = 0;
			maplock = SRWLOCK_INIT;
		}

		~safeptrmap() 
		{
			clear();
		}

		V get(K key)
		{
			return contains(key) ? stdmap[key] : 0;
		}

		K getnextkey(int i)
		{
			if (i >= top)
			{
				return keys[0];
			}
			else
			{
				return keys[i];
			}
		}

		int getend()
		{
			return top;
		}

		spmit<K, V> getit()
		{
			AcquireSRWLockShared(&maplock);
			return spmit<K, V>(&stdmap, &keys, &maplock, top);
		}

		bool contains(K k)
		{
			return stdmap.count(k) > 0;
		}

		void add(K key, V value)
		{
			if (value != 0)
			{
				if (contains(key))
				{
					removekey(key);
					AcquireSRWLockExclusive(&maplock);
					stdmap[key] = value;
					keys.push_back(key);
					top += 1;
					ReleaseSRWLockExclusive(&maplock);
				}
				else
				{
					AcquireSRWLockExclusive(&maplock);
					stdmap[key] = value;
					keys.push_back(key);
					top += 1;
					ReleaseSRWLockExclusive(&maplock);
				}
			}
		}

		void remove(int i)
		{
			if (top > 0 && i < top)
			{
				AcquireSRWLockExclusive(&maplock);
				top -= 1;
				delete stdmap[keys[i]];
				stdmap.erase(keys[i]);
				keys.erase(keys.begin() + i);
				ReleaseSRWLockExclusive(&maplock);
			}
		}

		int findkey(K key)
		{
			int ret = -1;
			AcquireSRWLockShared(&maplock); 
			for (int i = 0; i < top; i++)
			{
				if (keys[i] == key)
				{
					ret = i;
				}
			}
			ReleaseSRWLockShared(&maplock);
			return ret;
		}

		void removekey(K key)
		{
			int toremove = findkey(key);
			if (toremove >= 0)
			{
				remove(toremove);
			}
		}

		void pushtotop(K key)
		{
			int toreplace = findkey(key);
			if (toreplace >= 0)
			{
				AcquireSRWLockExclusive(&maplock);
				keys.erase(keys.begin() + toreplace);
				keys.push_back(key);
				ReleaseSRWLockExclusive(&maplock);
			}
		}

		void changekey(K from, K to)
		{
			if (contains(from))
			{
				if (contains(to))
				{
					removekey(to);
				}

				AcquireSRWLockExclusive(&maplock);
				stdmap[to] = stdmap[from];
				stdmap[from] = 0;
				ReleaseSRWLockExclusive(&maplock);
			}
		}

		void clear()
		{
			AcquireSRWLockExclusive(&maplock);
			for (int i = 0; i < top; i++)
			{
				delete stdmap[keys[i]];
			}
			top = 0;
			stdmap.clear();
			keys.clear();
			ReleaseSRWLockExclusive(&maplock);
		}
	private:
		vector<K> keys;
		map<K, V> stdmap;
		int top;
		SRWLOCK maplock;
	};
}

