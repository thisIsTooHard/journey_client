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
#include "Journey.h"

namespace program
{
	winapp::~winapp()
	{ 
		SafeRelease(&d2d_factory); 
	}

	long winapp::init()
	{
		long result;

		result = initfactories();

		imgcache.init(image_factory);
		fonts.init(dwrite_factory);

		fullscreen = false;
		screencd = 0;

		scralpha = 1.0f;
		trans = TRS_NONE;

		if (result == 0)
		{
			LPCSTR title = (LPCSTR)"Journey";

			WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
			wcex.style = CS_HREDRAW | CS_VREDRAW;
			wcex.lpfnWndProc = winapp::WndProc;
			wcex.cbClsExtra = 0;
			wcex.cbWndExtra = sizeof(LONG_PTR);
			wcex.hInstance = HINST_THISCOMPONENT;
			wcex.hbrBackground = NULL;
			wcex.lpszMenuName = NULL;
			wcex.hCursor = LoadCursor(NULL, IDI_APPLICATION);
			wcex.lpszClassName = title;

			RegisterClassEx(&wcex);

			d2d_factory->GetDesktopDpi(&dpiX, &dpiY);

			window = CreateWindow(
				title,
				title,
				WS_OVERLAPPED,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				static_cast<int>(ceil(816.f * dpiX / 96.f)),
				static_cast<int>(ceil(628.f * dpiY / 96.f)),
				NULL,
				NULL,
				HINST_THISCOMPONENT,
				this
				);

			if (window)
			{
				if (audio_pb.init(window))
				{
					uinterface.init();

					SetPriorityClass(window, REALTIME_PRIORITY_CLASS);
					SetFocus(window);
					ShowWindow(window, SW_SHOWNORMAL);
					UpdateWindow(window);
					return JRE_NONE;
				}
				else
				{
					return JRE_AUDIOERROR;
				}
			}
			else
			{
				return JRE_WINAPP_FAILURE;
			}
		}
		else
		{
			return JRE_WINAPP_FAILURE;
		}
	}

	long winapp::initfactories()
	{
		long result = 0;

		CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

		if (result == 0)
		{
			result = CoCreateInstance(
				CLSID_WICImagingFactory,
				NULL,
				CLSCTX_INPROC_SERVER,
				IID_PPV_ARGS(&image_factory)
				);

			if (result == 0)
			{
				result = D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &d2d_factory);

				if (result == 0)
				{
					result = DWriteCreateFactory(
						DWRITE_FACTORY_TYPE_SHARED,
						__uuidof(IDWriteFactory),
						reinterpret_cast<IUnknown**>(&dwrite_factory)
						);

					return 0;
				}
			}
		}

		return 1;
	}

	LRESULT CALLBACK winapp::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		LRESULT result = 0;
		UINT width, height;

		if (message == WM_CREATE)
		{
			LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
			winapp* app = (winapp *)pcs->lpCreateParams;

			::SetWindowLongPtrW(
				hwnd,
				GWLP_USERDATA,
				(long long)app
				);

			result = 1;
		}
		else
		{
			winapp* app = reinterpret_cast<winapp*>(::GetWindowLongPtrW(hwnd, GWLP_USERDATA));

			bool wasHandled = false;

			if (app)
			{
				switch (message)
				{
				case WM_SIZE:
					width = LOWORD(lParam);
					height = HIWORD(lParam);
					result = 0;
					wasHandled = true;
					break;
				case WM_DISPLAYCHANGE:
					InvalidateRect(hwnd, NULL, FALSE);
					result = 0;
					wasHandled = true;
					break;
				case WM_PAINT:
					app->render();
					result = 0;
					wasHandled = true;
					break;
				case WM_DESTROY:
					result = 1;
					wasHandled = true;
					break;
				case WM_QUIT:
					result = 1;
					wasHandled = true;
					break;
				case WM_MOUSEMOVE:
					app->getui()->sendmouse(vector2d(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
					result = 0;
					wasHandled = true;
					break;
				case WM_SETCURSOR:
					SetCursor(NULL);
					result = 1;
					wasHandled = true;
					break;
				case WM_LBUTTONDOWN:
					switch (wParam)
					{
					case MK_LBUTTON:
						app->getui()->sendmouse(MST_CLICKING, vector2d(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
						break;
					}
					result = 0;
					wasHandled = true;
					break;
				case WM_LBUTTONUP:
					if (wParam != MK_LBUTTON)
					{
						app->getui()->sendmouse(MST_IDLE, vector2d(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
					}
					result = 0;
					wasHandled = true;
					break;
				case WM_KEYDOWN:
					app->getui()->sendkey(wParam, true);
					result = 0;
					wasHandled = true;
					break;
				case WM_KEYUP:
					app->getui()->sendkey(wParam, false);
					result = 0;
					wasHandled = true;
					break;
				}
			}

			if (!wasHandled)
			{
				result = DefWindowProc(hwnd, message, wParam, lParam);
			}
		}

		return result;
	}

	void winapp::togglefullscreen()
	{
		if (screencd <= 0)
		{
			if (fullscreen)
			{
				SetWindowPos(
					window, 
					HWND_TOP, 0, 0, 
					static_cast<int>(ceil(816.f * dpiX / 96.f)),
					static_cast<int>(ceil(624.f * dpiX / 96.f)),
					SWP_FRAMECHANGED);

				fullscreen = false;
			}
			else
			{
				float factor = static_cast<float>(GetSystemMetrics(SM_CXSCREEN)) / 816.f;

				SetWindowPos(
					window,
					HWND_TOPMOST, 0, 0,
					static_cast<int>(ceil(816.f * factor * dpiX / 96.f)),
					static_cast<int>(ceil(624.f * factor * dpiY / 96.f)),
					SWP_FRAMECHANGED);

				fullscreen = true;
			}

			screencd = 500;
		}
	}

	void winapp::maptransition(int channel, int mapid, char portalid)
	{
		fadeout();
		tinfo.channel = channel;
		tinfo.mapid = mapid;
		tinfo.portalid = portalid;
		trans = TRS_MAP;
	}

	void wupdate(HWND hwnd)
	{
		winapp* app = reinterpret_cast<winapp*>(::GetWindowLongPtrW(hwnd, GWLP_USERDATA));
		app->update();
	}

	void winapp::update()
	{
		uinterface.update();

		bool trans_done = false;

		if (alphastep.size() > 0)
		{
			scralpha += alphastep[0];

			if (scralpha >= 1.0f)
			{
				scralpha = 1.0f;
				trans_done = true;
			}
			else if (scralpha <= 0.0f)
			{
				scralpha = 0.0f;
				trans_done = true;
			}
		}

		if (trans_done)
		{
			alphastep.erase(alphastep.begin());

			switch (trans)
			{
			case TRS_MAP:
				uinterface.getfield()->setfield(tinfo.mapid, tinfo.portalid);
				uinterface.enableactions();
				trans = TRS_NONE;
				break;
			}
		}
	}

	void winapp::render()
	{
		long result = 0;

		if (!d2d_rtarget)
		{
			RECT rc;
			GetClientRect(window, &rc);

			D2D1_SIZE_U size = D2D1::SizeU(
				rc.right - rc.left,
				rc.bottom - rc.top
				);

			result = d2d_factory->CreateHwndRenderTarget(
				D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE)),
				D2D1::HwndRenderTargetProperties(window, size),
				&d2d_rtarget
				);

			d2d_rtarget->CreateCompatibleRenderTarget(&back_rtarget);

			d2d_rtarget->SetAntialiasMode(D2D1_ANTIALIAS_MODE_ALIASED);
			back_rtarget->SetAntialiasMode(D2D1_ANTIALIAS_MODE_ALIASED);

			imgcache.settarget(back_rtarget);
		}

		if (d2d_rtarget)
		{
			RECT rc;
			GetClientRect(window, &rc);
			D2D1_RECT_F drc = D2D1::RectF(rc.left, rc.top, rc.right, rc.bottom);

			app.update();

			bool updatescr = alphastep.size() > 0 ? alphastep[0] > 0.0f : true;

			if (updatescr)
			{
				if (scene)
				{
					scene->Release();
					scene = 0;
				}

				back_rtarget->BeginDraw();
				back_rtarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
				uinterface.draw();
				back_rtarget->EndDraw();

				back_rtarget->GetBitmap(&scene);
			}
			else if (!scene)
			{
				back_rtarget->GetBitmap(&scene);
			}

			if (scene)
			{
				d2d_rtarget->BeginDraw();
				d2d_rtarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));
				d2d_rtarget->DrawBitmap(scene, drc, scralpha);
				d2d_rtarget->EndDraw();
			}
		}
		else
		{
			SafeRelease(&d2d_rtarget);
		}

		screencd -= DPF;
	}
}
