#include "LaserGun.h"
#include "LaserProjectile.h"

namespace TP3Prog
{
	LaserGun::LaserGun() : Weapon(1, 200, LASER_GUN)
	{
		projectiles = new LaserProjectile[maxProjectileCount];
		for (int i = 0; i < maxProjectileCount; ++i)
		{
			projectiles[i].loadTexture();
		}
	}


	LaserGun::~LaserGun()
	{
	}
}
