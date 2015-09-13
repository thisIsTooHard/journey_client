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
#include "fontcache.h"

namespace program
{
	void fontcache::init(IDWriteFactory* w_f)
	{
		fontfactory = unique_ptr<IDWriteFactory>(w_f);

		fontfactory->CreateTextFormat(L"Calibri", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 12.0f, L"en-us", &fonts[DWF_12L]);
		fonts[DWF_12L]->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		fonts[DWF_12L]->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);

		fontfactory->CreateTextFormat(L"Calibri", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 12.0f, L"en-us", &fonts[DWF_12C]);
		fonts[DWF_12C]->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		fonts[DWF_12C]->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);

		fontfactory->CreateTextFormat(L"Calibri", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 12.0f, L"en-us", &fonts[DWF_12R]);
		fonts[DWF_12R]->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
		fonts[DWF_12R]->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);

		fontfactory->CreateTextFormat(L"Times New Roman", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 14.0f, L"en-us", &fonts[DWF_14L]);
		fonts[DWF_14L]->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		fonts[DWF_14L]->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);

		fontfactory->CreateTextFormat(L"Calibri", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 14.0f, L"en-us", &fonts[DWF_14C]);
		fonts[DWF_14C]->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		fonts[DWF_14C]->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);

		fontfactory->CreateTextFormat(L"Calibri", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 14.0f, L"en-us", &fonts[DWF_14R]);
		fonts[DWF_14R]->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
		fonts[DWF_14R]->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);

		fontfactory->CreateTextFormat(L"Calibri", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 20.0f, L"en-us", &fonts[DWF_20C]);
		fonts[DWF_20C]->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		fonts[DWF_20C]->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
	}

	fontcache::~fontcache()
	{
		for (map<dwfonts, IDWriteTextFormat*>::iterator fnit = fonts.begin(); fnit != fonts.end(); ++fnit)
		{
			fnit->second->Release();
		}
	}

	IDWriteTextFormat* fontcache::getfont(dwfonts type)
	{
		return fonts[type];
	}
}
