#pragma once
#include "Weapon.h"

namespace TP3Prog
{

	class Flamethrower : public Weapon
	{
	public:
		Flamethrower();
		virtual ~Flamethrower();

	private:
		static const int FLAMETHROWER_SHOOT_INTERVAL = 4;
		static const int FLAMETHROWER_PROJECTILE_COUNT = 60;
	};
}
