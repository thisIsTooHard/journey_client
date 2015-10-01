#pragma once
#include "rectangle2d.h"

using namespace util;

namespace io
{
	enum icontype
	{
		ICN_KEY,
		ICN_SKILLKEY,
		ICN_ITEMKEY,
		ICN_SKILL,
		ICN_ITEM
	};

	class icon
	{
	public:
		icon() {}
		virtual ~icon() {}
		virtual void draw(vector2d) = 0;
		virtual void dragdraw(vector2d) = 0;
		virtual void onmouseover() = 0;
		virtual void ondrop() = 0;
		virtual void setposition(vector2d) = 0;
		virtual void setdrag(vector2d, vector2d) = 0;
		virtual void resetdrag() = 0;
		virtual bool candrag() = 0;
		virtual rectangle2d bounds(vector2d) = 0;
		virtual icontype gettype() = 0;
	};
}

