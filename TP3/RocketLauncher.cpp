#include "RocketLauncher.h"
#include "Rocket.h"

namespace TP3Prog
{

	RocketLauncher::RocketLauncher() : 
	Weapon(ROCKETLAUNCHER_PROJECTILE_COUNT, ROCKETLAUNCHER_SHOOT_INTERVAL, ROCKETLAUNCHER)
	{
		projectiles = new Rocket[maxProjectileCount];

		for (int i = 0; i < maxProjectileCount; ++i)
		{
			projectiles[i].loadTexture();
		}
	}

	RocketLauncher::~RocketLauncher()
	{
	}
}
