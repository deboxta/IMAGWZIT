#include "Flame.h"
#include "WeaponType.h"

namespace TP3Prog
{
	Flame::Flame() : Projectile(20, 15,false, 1)
	{
	}


	Flame::~Flame()
	{
	}

	void Flame::loadTexture()
	{
		setTexture(projectileTextures[FLAMETHROWER]);
	}
}
