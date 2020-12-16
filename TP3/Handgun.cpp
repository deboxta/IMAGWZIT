#include "Handgun.h"

namespace TP3Prog
{

	Handgun::Handgun() : Weapon(HANDGUN_PROJECTILE_COUNT, HANDGUN_SHOOT_INTERVAL)
	{
			projectiles = new Projectile[maxProjectileCount];

			for (int i = 0; i < maxProjectileCount; ++i)
			{
				projectiles[i].loadTexture();
			}
	}


	Handgun::~Handgun()
	{
	}

}
