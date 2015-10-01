//////////////////////////////////////////////////////////////////////////////
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
#include "Journey.h"

HANDLE gTimerDoneEvent;
HANDLE audio_closed;
HANDLE hTimer = NULL;
HANDLE hTimerQueue = NULL;

packetcreator packet_c;
winapp app;
session server;
datacache cache;
settings config;

int result = JRE_NONE;

void quit()
{
	result = JRE_EXIT;
	PostQuitMessage(0);
}

void CALLBACK Update(PVOID lpParam, BOOLEAN TimerOrWaitFired) {
	if (result == JRE_NONE)
	{
		if (WaitForSingleObject(gTimerDoneEvent, DPF) == WAIT_OBJECT_0)
		{
			//ResetEvent(gTimerDoneEvent);
			//app.update();
		}
	}
	SetEvent(gTimerDoneEvent);
}

void CALLBACK CloseAudio()
{
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	result = nx::load_all() ? JRE_NONE : JRE_MISSING_FILES;

	if (result == JRE_NONE)
	{
		result = server.init();

		if (result == 0)
		{
			packet_c.init(&server, 83);

			HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);
			CoInitialize(NULL);

			result = app.init();

			if (result == 0)
			{
				gTimerDoneEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
				hTimerQueue = CreateTimerQueue();
				CreateTimerQueueTimer(&hTimer, hTimerQueue, (WAITORTIMERCALLBACK)Update, 0, 60, DPF, 0);

				MSG winmsg;
				while (result == 0)
				{
					if (WaitForSingleObject(gTimerDoneEvent, DPF) == WAIT_OBJECT_0)
					{
						server.receive();

						if (GetMessage(&winmsg, 0, 0, 0))
						{
							TranslateMessage(&winmsg);
							DispatchMessage(&winmsg);
						}
					}
				}

				WaitForSingleObject(gTimerDoneEvent, 1000);
			}

			CoUninitialize();
		}

		server.close();
	}
	
	if (result != JRE_EXIT)
	{
		string error;
		switch (result)
		{
		case JRE_SERVER_OFFLINE:
			error = "Connection failure:\nThe server seems to be offline.";
			break;
		case JRE_WRONG_VERSION:
			error = "Unsupported server version.";
			break;
		case JRE_MISSING_FILES:
			error = "Could not find .nx files.";
			break;
		case JRE_WINAPP_FAILURE:
			error = "Could not initialize winapi.";
			break;
		case JRE_AUDIOERROR:
			error = "Could not initialize audio.";
			break;
		default:
			error = "Unknown error.";
			break;
		}
		MessageBox(NULL, error.c_str(), NULL, MB_OK);
	}

	return 0;
}