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
#include <random>

using namespace std;

namespace util
{
	class randomizer
	{
	public:
		randomizer() {}
		~randomizer() {}
		bool nextbool();
		bool below(float);

		template <class T>
		T nextreal(T high)
		{
			return nextreal<T>(0, high);
		}

		template <class T>
		T nextreal(T low, T high)
		{
			uniform_real_distribution<T> range(low, high);
			return range(chance());
		}

		template <class T>
		T nextint(T high)
		{
			return nextint<T>(0, high);
		}

		template <class T>
		T nextint(T low, T high)
		{
			uniform_int_distribution<T> range(low, high);
			return range(chance());
		}
	private:
		default_random_engine chance();
	};
}

