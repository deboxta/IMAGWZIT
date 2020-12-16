#include "Minigun.h"
#include "MinigunProjectile.h"

namespace TP3Prog
{
	Minigun::Minigun() : Weapon(200, 3, MINIGUN, 1)
	{
		projectiles = new MinigunProjectile[maxProjectileCount];
		for (int i = 0; i < maxProjectileCount; ++i)
		{
			projectiles[i].loadTexture();
		}
	}


	Minigun::~Minigun()
	{
	}
}
