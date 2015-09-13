#pragma once
#include "animation.h"

namespace graphics
{
	class effect
	{
	public:
		effect(animation, vector2d, bool);
		effect() {}
		~effect() {}
		void draw(ID2D1HwndRenderTarget*, vector2d);
		bool update();
	private:
		animation ani;
		vector2d position;
		bool flipped;
	};
}

