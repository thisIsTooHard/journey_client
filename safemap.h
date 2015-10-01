/////////////////////////////////////////////////////////////////////////////
// This file is part of the Journey MMORPG client                           //
// Copyright � 2015 SYJourney                                               //
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
	class smit
	{
	public:
		smit(map<K, V>* std, vector<K>* ky, SRWLOCK* lock, int32_t t)
		{
			stdmap = std;
			keys = ky;
			maplock = lock;
			top = t;
			index = 0;
		}

		~smit()
		{
			ReleaseSRWLockShared(maplock);
		}

		V* operator -> ()
		{
			return &stdmap->at(keys->at(index));
		}

		V* get()
		{
			return &stdmap->at(keys->at(index));
		}

		void operator ++ ()
		{
			index++;
		}

		bool belowtop()
		{
			return index < top;
		}

		int32_t getindex()
		{
			return index;
		}

		int32_t getkey()
		{
			return keys->at(index);
		}
	private:
		map<K, V>* stdmap;
		vector<K>* keys;
		SRWLOCK* maplock;
		int32_t index;
		int32_t top;
	};

	template <typename K, typename V>
	class safemap
	{
	public:
		safemap() 
		{ 
			top = 0; 
			maplock = SRWLOCK_INIT;
		}
		
		~safemap() {}
		
		V* get(K key) 
		{ 
			return &stdmap[key]; 
		}

		smit<K, V> getit()
		{
			AcquireSRWLockShared(&maplock);
			return smit<K, V>(&stdmap, &keys, &maplock, top);
		}

		int32_t getend() 
		{ 
			return top; 
		}

		bool contains(K k) 
		{ 
			return stdmap.count(k) > 0; 
		}

		void add(K key, V value)
		{
			if (stdmap.count(key))
			{
				removekey(key);
			}
			AcquireSRWLockExclusive(&maplock);
			stdmap[key] = value;
			keys.push_back(key);
			top += 1;
			ReleaseSRWLockExclusive(&maplock);
		}

		void remove(int32_t i)
		{
			if (top > 0 && i < top)
			{
				if (stdmap.count(keys[i]))
				{
					AcquireSRWLockExclusive(&maplock);
					top -= 1;
					stdmap.erase(keys[i]);
					keys.erase(keys.begin() + i);
					ReleaseSRWLockExclusive(&maplock);
				}
			}
		}

		void removekey(K key)
		{
			if (stdmap.count(key))
			{
				AcquireSRWLockShared(&maplock);
				int32_t index = -1;
				for (int32_t i = 0; i < top; i++)
				{
					if (keys[i] == key)
					{
						index = i;
						break;
					}
				}
				ReleaseSRWLockShared(&maplock);

				if (index >= 0)
				{
					remove(index);
				}
			}
		}

		void removeall(vector<int32_t> toremove)
		{
			AcquireSRWLockExclusive(&maplock);
			for (vector<int32_t>::iterator rmit = toremove.begin(); rmit != toremove.end(); ++rmit)
			{
				int32_t index = *rmit;

				if (top > 0 && index < top)
				{
					if (stdmap.count(keys[index]))
					{
						top -= 1;
						stdmap.erase(keys[index]);
						keys.erase(keys.begin() + index);
					}
				}
			}
			ReleaseSRWLockExclusive(&maplock);
		}

		void clear()
		{
			AcquireSRWLockExclusive(&maplock);
			top = 0;
			stdmap.clear();
			keys.clear();
			ReleaseSRWLockExclusive(&maplock);
		}
	private:
		vector<K> keys;
		map<K, V> stdmap;
		int32_t top;
		SRWLOCK maplock;
	};
}

