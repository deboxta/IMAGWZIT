#include "MinigunProjectile.h"
#include "WeaponType.h"

namespace TP3Prog
{
	MinigunProjectile::MinigunProjectile() : Projectile(60, 40, false, 1)
	{
	}


	MinigunProjectile::~MinigunProjectile()
	{
	}

	void MinigunProjectile::loadTexture()
	{
		setTexture(projectileTextures[MINIGUN]);
	}
}
