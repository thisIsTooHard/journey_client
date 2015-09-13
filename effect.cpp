#include "effect.h"

namespace graphics
{
	effect::effect(animation a, vector2d pos, bool flp)
	{
		ani = a;
		position = pos;
		flipped = flp;
	}

	void effect::draw(ID2D1HwndRenderTarget* target, vector2d parentpos)
	{
		vector2d absp = position + parentpos;

		if (flipped)
		{
			target->SetTransform(
				D2D1::Matrix3x2F::Scale(
				D2D1::Size(-1.0f, 1.0f),
				D2D1::Point2F(
				(float)absp.x(),
				(float)absp.y())));
		}

		ani.draw(target, absp);

		if (flipped)
		{
			target->SetTransform(
				D2D1::Matrix3x2F::Scale(
				D2D1::Size(1.0f, 1.0f),
				D2D1::Point2F(
				(float)absp.x(),
				(float)absp.y())));
		}
	}

	bool effect::update()
	{
		return ani.update();
	}
}
