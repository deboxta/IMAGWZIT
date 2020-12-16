#include "WatcherProjectile.h"
#include "WeaponType.h"

namespace TP3Prog
{
	WatcherProjectile::WatcherProjectile() : Projectile(60, 12)
	{
	}


	WatcherProjectile::~WatcherProjectile()
	{
	}

	void WatcherProjectile::loadTexture()
	{
		setTexture(projectileTextures[WATCHER_WEAPON]);
	}
}
