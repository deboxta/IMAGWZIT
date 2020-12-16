#include "FollowerWeapon.h"

namespace TP3Prog
{

	FollowerWeapon::FollowerWeapon() : Weapon(4, 400, FOLLOWER_WEAPON, 0, false)
	{
		projectiles = new Projectile[maxProjectileCount];

		for (int i = 0; i < maxProjectileCount; ++i)
		{
			projectiles[i].loadTexture();
		}
	}


	FollowerWeapon::~FollowerWeapon()
	{

	}

}
