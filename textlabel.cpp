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
	textlabel::textlabel(dwfonts f, textcolor c, string s, textbg bg)
	{
		font = app.getfonts()->getfont(f);
		color = c;
		back = bg;
		text = s;
		marker = false;
		position = vector2d(0, 5);
		alpha = 1.0f;
		brush = 0;
		bgbrush = 0;
	}

	textlabel::textlabel(dwfonts f, textcolor c, string s)
	{
		font = app.getfonts()->getfont(f);
		color = c;
		back = TXB_NONE;
		text = s;
		marker = false;
		position = vector2d(0, 5);
		alpha = 1.0f;
		brush = 0;
		bgbrush = 0;
	}

	void textlabel::draw(vector2d parentpos)
	{
		draw(text, parentpos);
	}

	void textlabel::draw(string txt, vector2d parentpos)
	{
		ID2D1HwndRenderTarget* target = app.getimgcache()->gettarget();

		if (target)
		{
			vector2d absp = position + parentpos;

			string temp = txt;

			if (marker)
			{
				temp.append("|");
			}

			float space = font->GetFontSize() + 2.0f;
			float length = font->GetFontSize() * temp.length();

			if (absp.x() + length >= 0 && absp.x() - length <= SCREENW && absp.y() + space >= 0 && absp.y() - space <= SCREENH && temp != "")
			{
				D2D1_RECT_F layout;
				switch (font->GetTextAlignment())
				{
				case DWRITE_TEXT_ALIGNMENT_LEADING:
					layout = D2D1::RectF(
						static_cast<FLOAT>(absp.x()),
						static_cast<FLOAT>(absp.y()),
						static_cast<FLOAT>(absp.x() + length),
						static_cast<FLOAT>(absp.y() + space)
						);
					break;
				case DWRITE_TEXT_ALIGNMENT_TRAILING:
					layout = D2D1::RectF(
						static_cast<FLOAT>(absp.x() - length),
						static_cast<FLOAT>(absp.y()),
						static_cast<FLOAT>(absp.x()),
						static_cast<FLOAT>(absp.y() + space)
						);
					break;
				case DWRITE_TEXT_ALIGNMENT_CENTER:
					layout = D2D1::RectF(
						static_cast<FLOAT>(absp.x() - length / 2),
						static_cast<FLOAT>(absp.y()),
						static_cast<FLOAT>(absp.x() + length / 2),
						static_cast<FLOAT>(absp.y() + space)
						);
					break;
				default:
					return;
				}

				wstring wide_string(temp.begin(), temp.end());

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
					}
				}

				if (bgbrush)
				{
					float rlength = (font->GetFontSize() / 2.4f) * temp.length() + font->GetFontSize() + 3.0f;
					D2D1_RECT_F bglayout = D2D1::RectF(
						static_cast<FLOAT>(absp.x() - rlength / 2),
						static_cast<FLOAT>(absp.y()),
						static_cast<FLOAT>(absp.x() + rlength / 2),
						static_cast<FLOAT>(absp.y() + space)
						);
					D2D1_ROUNDED_RECT rect = { bglayout, 2.0f, 2.0f };
					target->DrawRoundedRectangle(&rect, bgbrush);
					target->FillRoundedRectangle(&rect, bgbrush);
				}

				brush->SetOpacity(alpha);

				target->DrawText(
					wide_string.c_str(),
					static_cast<UINT32>(wide_string.length()),
					font,
					layout,
					brush
					);
			}
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
