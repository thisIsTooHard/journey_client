#include "attackfactory.h"

namespace gameplay
{
	attackfactory::attackfactory()
	{
	}

	skill* attackfactory::getskill(int id)
	{
		if (!skills.count(id))
		{
			skills[id] = skill(id);
		}
		return &skills[id];
	}

	const rectangle2d attackfactory::getnormalrange(regularattack att)
	{
		switch (att)
		{
		case RGA_1HWEP:
			return rectangle2d(-75, 0, -5, 0);
		case RGA_2HWEP:
			return rectangle2d(-100, 0, -5, 0);
		case RGA_SPEAR_PA:
			return rectangle2d(-130, 0, -5, 0);
		}
		return rectangle2d();
	}
}
