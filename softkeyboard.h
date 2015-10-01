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
#include "uielement.h"
#include "randomizer.h"

namespace io
{
	enum sftkb_buttons
	{
		BT_SOFTKEY_0,
		BT_SOFTKEY_1,
		BT_SOFTKEY_2,
		BT_SOFTKEY_3,
		BT_SOFTKEY_4,
		BT_SOFTKEY_5,
		BT_SOFTKEY_6,
		BT_SOFTKEY_7,
		BT_SOFTKEY_8,
		BT_SOFTKEY_9,
		BT_SOFTKEY_NEXT,
		BT_SOFTKEY_BACK,
		BT_SOFTKEY_CANCEL,
		BT_SOFTKEY_OK
	};

	enum sftkb_mode
	{
		SFTKB_REGISTER,
		SFTKB_CHARSELECT,
		SFTKB_CHARDEL,
		SFTKB_MERCHANT
	};

	class softkeyboard : public uielement
	{
	public:
		softkeyboard(char);
		~softkeyboard() {}
		void draw();
		void buttonpressed(short);
		void shufflekeys();
		vector2d keypos(char);
	private:
		textlabel entry;
		string entered;
		randomizer random;
		sftkb_mode mode;
	};
}

