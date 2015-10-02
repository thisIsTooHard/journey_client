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
#include "audioplayerbass.h"

namespace program
{
	bool audioplayerbass::init(HWND hwnd)
	{
		return BASS_Init(1, 44100, 0, hwnd, 0) == TRUE;
	}

	void audioplayerbass::close()
	{
		if (bgm != 0)
		{
			BASS_ChannelStop(bgm);
			BASS_StreamFree(bgm);
		}
		for (map<size_t, HSAMPLE>::iterator snit = soundcache.begin(); snit != soundcache.end(); ++snit)
		{
			BASS_SampleStop(snit->second);
			BASS_SampleFree(snit->second);
		}
		BASS_Free();
	}

	void audioplayerbass::playbgm(void* data, size_t length)
	{
		if (bgm != 0)
		{
			BASS_ChannelStop(bgm);
			BASS_StreamFree(bgm);
		}
		bgm = BASS_StreamCreateFile(true, data, 82, length, BASS_SAMPLE_FLOAT | BASS_SAMPLE_LOOP);
		BASS_ChannelPlay(bgm, true);
	}

	void audioplayerbass::cachesound(void* data, size_t length, size_t id)
	{
		if (!soundcache.count(id))
		{
			soundcache[id] = BASS_SampleLoad(true, data, 82, length, 4, BASS_SAMPLE_OVER_POS);
		}
	}

	void audioplayerbass::playsound(size_t id)
	{
		if (soundcache.count(id))
		{
			HCHANNEL channel = BASS_SampleGetChannel(soundcache[id], false);
			BASS_ChannelPlay(channel, true);
		}
	}

	void audioplayerbass::setvolume0(int v0)
	{
		BASS_SetConfig(BASS_CONFIG_GVOL_STREAM, v0 * 100);
	}

	void audioplayerbass::setvolume1(int v1)
	{
		BASS_SetConfig(BASS_CONFIG_GVOL_SAMPLE, v1 * 100);
	}
}
