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
HANDLE hTimer = NULL;
HANDLE hTimerQueue = NULL;

packetcreator packet_c;
winapp app;
//window app;
session server;
datacache cache;
settings config;

int result = 0;
byte mapleversion = 0;

void quit()
{
	result = 1;
	PostQuitMessage(0);
}

void CALLBACK Update(PVOID lpParam, BOOLEAN TimerOrWaitFired) {
	if (result == 0)
	{
		app.getui()->update();
		SetEvent(gTimerDoneEvent);
	}
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	result = server.init();

	if (result > 0)
	{
		mapleversion = result;
		packet_c.init(&server, mapleversion);

		HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

		gTimerDoneEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
		hTimerQueue = CreateTimerQueue();

		result = CoInitialize(NULL);

		if (result == 0)
		{
			result = app.init();

			if (result == 0)
			{
				CreateTimerQueueTimer(&hTimer, hTimerQueue, (WAITORTIMERCALLBACK)Update, NULL, 60, DPF, 0);

				MSG winmsg;
				while (result == 0)
				{
					if (WaitForSingleObject(gTimerDoneEvent, DPF) == WAIT_OBJECT_0)
					{
						server.receive();
						//app.draw();

						if (GetMessage(&winmsg, NULL, 0, 0))
						{
							TranslateMessage(&winmsg);
							DispatchMessage(&winmsg);
						}
					}
				}

				WaitForSingleObject(gTimerDoneEvent, 1000);
			}
			else
			{
				MessageBox(NULL, (LPCSTR)"Failed to initialize windows app.", NULL, MB_OK);
			}

			CoUninitialize();
		}

		server.close();
	}
	else
	{
		string error = "Connection failure:\n";
		switch (result)
		{
		case -1:
			error.append("The server seems to be offline.");
			break;
		case -2:
			error.append("Unsupported version.");
			break;
		}
		MessageBox(NULL, error.c_str(), NULL, MB_OK);
	}

	return 0;
}