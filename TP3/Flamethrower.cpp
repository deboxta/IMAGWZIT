#include "Flamethrower.h"
#include "Flame.h"


namespace TP3Prog
{

	Flamethrower::Flamethrower(): 
	Weapon(FLAMETHROWER_PROJECTILE_COUNT, FLAMETHROWER_SHOOT_INTERVAL, FLAMETHROWER)
	{
		projectiles = new Flame[maxProjectileCount];

		for (int i = 0; i < maxProjectileCount; ++i)
		{
			projectiles[i].loadTexture();
		}
	}

	Flamethrower::~Flamethrower()
	{
	}
}
