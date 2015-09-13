#pragma once
#include "skill.h"

using namespace action;

namespace gameplay
{
	enum attacktype
	{
		ATT_NONE,
		ATT_CLOSE,
		ATT_MAGIC,
		ATT_RANGED
	};

	enum regularattack
	{
		RGA_NONE,
		RGA_1HWEP,
		RGA_SPEAR_PA,
		RGA_BOW,
		RGA_XBOW,
		RGA_2HWEP,
		RGA_STAFF_WAND,
		RGA_CLAW,
		RGA_KNUCKLE,
		RGA_GUN
	};

	class attackfactory
	{
	public:
		attackfactory();
		~attackfactory() {}
		skill* getskill(int);
		const rectangle2d getnormalrange(regularattack);
	private:
		map<int, skill> skills;
	};
}

