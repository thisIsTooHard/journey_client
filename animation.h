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
#include "texture.h"

using namespace std;

namespace graphics
{
	const short DPF = 16;
	const short DEF_DELAY = 60;

	class animation
	{
	public:
		animation() {}
		animation(node);
		~animation() {}
		void draw(byte, vector2d);
		void draw(byte, float, vector2d);
		void draw(ID2D1HwndRenderTarget*, vector2d);
		void draw(ID2D1HwndRenderTarget*, vector2d, float);
		void setframe(byte);
		short gettotaldelay();
		short getdelay(byte f) { return delays[f]; }
		float getalpha(byte f) { return static_cast<float>(alphablends[f].second) / 255; }
		byte prevframe(byte f) { return (f > 0) ? f - 1 : last_f; }
		byte nextframe(byte f) { return (f == last_f) ? 0 : f + 1; }
		vector2d getdimension(byte);
		bool update(short);
		bool update() { return update(DPF); }
		bool isloaded() { return textures[0].isloaded(); }
		bool isanimated() { return last_f > 0; }
		bool hasblending(byte f) { return alphablends.count(f) > 0; }
		texture* gettexture(byte f) { return textures.count(f) ? &textures[f] : 0; }
	protected:
		map<byte, texture> textures;
		map<byte, short> delays;
		map<byte, pair<byte, byte>> alphablends;
		byte frame;
		byte last_f;
		bool blending;
		short elapsed;
		float alphastep;
		float alpha;
	};
}

