#include "Rocket.h"
#include "WeaponType.h"

namespace TP3Prog
{	
	Rocket::Rocket() : Projectile(200, 9, false, 8)
	{
	}


	Rocket::~Rocket()
	{
	}

	void Rocket::loadTexture()
	{
		setTexture(projectileTextures[ROCKETLAUNCHER]);
	}
}
