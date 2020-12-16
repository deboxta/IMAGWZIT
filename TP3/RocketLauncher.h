#pragma once
#include "Weapon.h"

namespace TP3Prog
{

	class RocketLauncher : public Weapon
	{
	public:
		RocketLauncher();
		~RocketLauncher();

	private:
		static const int ROCKETLAUNCHER_SHOOT_INTERVAL = 60;
		static const int ROCKETLAUNCHER_PROJECTILE_COUNT = 30;
	};

}