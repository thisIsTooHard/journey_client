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

namespace graphics
{
	textlabel::textlabel(dwfonts f, textcolor c, string s, vector2d b)
	{
		init();

		getfont(f);
		settext(s, b);

		color = c;
	}

	textlabel::textlabel(dwfonts f, textcolor c, string s)
	{
		init();

		getfont(f);
		settext(s);

		color = c;
	}

	void textlabel::init()
	{
		font = 0;
		brush = 0;
		bgbrush = 0;

		text = "";
		wtext = wstring();
		alpha = 1.0f;
		height = 0;
		width = 0;
		back = TXB_NONE;
	}

	void textlabel::getfont(dwfonts f)
	{
		font = app.getfonts()->getfont(f);
	}

	void textlabel::drawline(string txt, vector2d parentpos)
	{
		width = SCREENW;
		wtext = wstring(txt.begin(), txt.end());
		draw(parentpos);
	}

	void textlabel::drawover(string txt, vector2d parentpos)
	{
		string temp = text;
		settext(txt);
		text = temp;
		draw(parentpos);
	}

	void textlabel::draw(string txt, vector2d parentpos)
	{
		if (text != txt)
		{
			settext(txt);
			text = txt;
		}
		draw(parentpos);
	}

	void textlabel::draw(vector2d parentpos)
	{
		ID2D1RenderTarget* target = app.getimgcache()->gettarget();

		if (target && font)
		{
			vector2d absp = parentpos + vector2d(0, 5);

			int32_t lrwidth = width + 5;

			if (absp.x() + width >= 0 && absp.x() - width <= SCREENW && absp.y() + height >= 0 && absp.y() - height <= SCREENH && wtext.size() > 0)
			{
				D2D1_RECT_F layrect;
				switch (font->GetTextAlignment())
				{
				case DWRITE_TEXT_ALIGNMENT_LEADING:
					layrect = D2D1::RectF(
						static_cast<float_t>(absp.x()),
						static_cast<float_t>(absp.y()),
						static_cast<float_t>(absp.x() + lrwidth),
						static_cast<float_t>(absp.y() + height)
						);
					break;
				case DWRITE_TEXT_ALIGNMENT_TRAILING:
					layrect = D2D1::RectF(
						static_cast<float_t>(absp.x() - lrwidth),
						static_cast<float_t>(absp.y()),
						static_cast<float_t>(absp.x()),
						static_cast<float_t>(absp.y() + height)
						);
					break;
				case DWRITE_TEXT_ALIGNMENT_CENTER:
					layrect = D2D1::RectF(
						static_cast<float_t>(absp.x() - lrwidth / 2),
						static_cast<float_t>(absp.y()),
						static_cast<float_t>(absp.x() + lrwidth / 2),
						static_cast<float_t>(absp.y() + height)
						);
					break;
				default:
					return;
				}

				if (!brush)
				{
					switch (color)
					{
					case TXC_WHITE:
						target->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &brush);
						break;
					case TXC_BLACK:
						target->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &brush);
						break;
					case TXC_YELLOW:
						target->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Yellow), &brush);
						break;;
					case TXC_RED:
						target->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &brush);
						break;
					case TXC_BLUE:
						target->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Blue), &brush);
						break;
					case TXC_BROWN:
						target->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Brown), &brush);
						break;
					case TXC_GREY:
						target->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Gray), &brush);
						break;
					case TXC_ORANGE:
						target->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Orange), &brush);
						break;
					case TXC_MBLUE:
						target->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::SkyBlue), &brush);
						break;
					case TXC_VIOLET:
						target->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Violet), &brush);
						break;
					}
				}

				if (!bgbrush)
				{
					switch (back)
					{
					case TXB_NAMETAG:
						target->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &bgbrush);
						bgbrush->SetOpacity(0.6f);
						break;
					case TXB_GMCHAT:
						target->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::WhiteSmoke), &bgbrush);
						bgbrush->SetOpacity(0.8f);
						break;
					}
				}

				if (bgbrush)
				{
					if (back == TXB_NAMETAG)
					{
						float_t hwidth = static_cast<float_t>(lrwidth) / 2;
						float_t space = font->GetFontSize() + 2.0f;

						D2D1_RECT_F bglayout = D2D1::RectF(
							static_cast<float_t>(absp.x() - hwidth),
							static_cast<float_t>(absp.y() + 2),
							static_cast<float_t>(absp.x() + hwidth),
							static_cast<float_t>(absp.y() + space)
							);

						D2D1_ROUNDED_RECT rect = { bglayout, 1.5f, 1.5f };

						target->DrawRoundedRectangle(&rect, bgbrush);
						target->FillRoundedRectangle(&rect, bgbrush);
					}
				}

				if (brush && target)
				{
					brush->SetOpacity(alpha);

					target->DrawText(
						wtext.c_str(),
						static_cast<uint32_t>(wtext.size()),
						font,
						layrect,
						brush
						);
				}
			}
		}
	}

	void textlabel::setcolor(textcolor txc)
	{
		if (brush)
		{
			brush->Release();
		}
		color = txc;
	}

	void textlabel::settext(string txt, vector2d bounds)
	{
		if (font)
		{
			wtext = wstring(txt.begin(), txt.end());
			text = txt;

			int32_t totlen = createlayout(bounds);
			int32_t parlen = bounds.x();

			float space = font->GetFontSize() * 1.25f;

			if (totlen > parlen && parlen > 0)
			{
				width = parlen;
				height = static_cast<int32_t>(space) * ((totlen / parlen) + 1);
				endpos = vector2d(totlen % parlen, height - static_cast<int32_t>(font->GetFontSize()));
			}
			else
			{
				width = totlen;
				height = static_cast<int32_t>(space);
				endpos = vector2d(totlen, 0);
			}
		}
	}

	int textlabel::createlayout(vector2d bounds)
	{
		IDWriteFactory* dwrite_f = app.getfonts()->getdwrite_f();

		if (dwrite_f && text.size() > 0)
		{
			if (bounds.x() < 1)
			{
				bounds.setx(SCREENW);
			}

			if (bounds.y() < 1)
			{
				bounds.sety(SCREENH);
			}

			IDWriteTextLayout* layout = 0;

			uint32_t textlen = static_cast<uint32_t>(wtext.length());

			dwrite_f->CreateTextLayout(
				wtext.c_str(),
				textlen,
				font,
				bounds.x(),
				bounds.y(),
				&layout  
				);

			if (layout)
			{
				DWRITE_CLUSTER_METRICS* metrics = new DWRITE_CLUSTER_METRICS[textlen];

				uint32_t reslen;
				HRESULT result = layout->GetClusterMetrics(metrics, textlen, &reslen);

				if (result != 0)
				{
					result = layout->GetClusterMetrics(metrics, reslen, &reslen);

					if (result != 0)
					{
						return 0;
					}
				}

				float_t tadv = 0.0f;
				advances.clear();

				for (uint32_t i = 0; i < reslen; i++)
				{
					advances[i] = tadv;
					tadv += metrics[i].width;
				}
				advances[reslen] = tadv;

				delete[] metrics;

				return static_cast<int32_t>(tadv);
			}
			else
			{
				return 0;
			}
		}
		else
		{
			return 0;
		}
	}

	int textlabel::getadvance(short pos)
	{
		if (advances.count(pos))
		{
			return advances[pos];
		}
		else
		{
			return 0;
		}
	}

	textlabel::~textlabel()
	{
		if (brush)
		{
			brush->Release();
		}
		if (bgbrush)
		{
			bgbrush->Release();
		}
	}
}
