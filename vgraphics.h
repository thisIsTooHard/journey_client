#pragma once
#include "vector2d.h"

using namespace util;

namespace graphics
{
	class vgraphics
	{
	public:
		vgraphics() {}
		virtual ~vgraphics() {}
		virtual void draw(vector2d) =0;
		virtual bool update() =0;
	};
}

