#include "Scattershot.h"
#include "Scatter.h"

namespace TP3Prog
{
	Scattershot::Scattershot() : 
	Weapon(SCATTERSHOT_PROJECTILE_COUNT, SCATTERSHOT_SHOOT_INTERVAL, SCATTERSHOT, SCATTERSHOT_REQUIRED_AMMO)
	{
		projectiles = new Scatter[maxProjectileCount];

		for (int i = 0; i < maxProjectileCount; ++i)
		{
			projectiles[i].loadTexture();
		}
	}

	Scattershot::~Scattershot()
	{

	}

	void Scattershot::shoot(Entity& entity)
	{
		int bulletCount = 3;

		for (int i = 0; i < maxProjectileCount; ++i)
		{
			if (!projectiles[i].getIsActive())
			{
				projectiles[i].initialise(entity.getPosition(),
					-20 + entity.getRotation() + (bulletCount * 20));

				--ammoCount;

				if(--bulletCount <= 0)
				{
					break;
				}
			}
		}

		currentShootInterval = shootInterval;
	}
}
