#include "WatcherWeapon.h"
#include "WatcherProjectile.h"

namespace TP3Prog
{
	WatcherWeapon::WatcherWeapon() : Weapon(60, 0, WATCHER_WEAPON, 0, false)
	{
		projectiles = new WatcherProjectile[maxProjectileCount];

		for (int i = 0; i < maxProjectileCount; ++i)
		{
			projectiles[i].loadTexture();
		}
	}


	WatcherWeapon::~WatcherWeapon()
	{

	}
}
