#include "Scatter.h"
#include "WeaponType.h"

namespace TP3Prog
{
	Scatter::Scatter() : Projectile(60, 20,false,2)
	{
	}


	Scatter::~Scatter()
	{
	}

	void Scatter::loadTexture()
	{
		setTexture(projectileTextures[SCATTERSHOT]);
	}
}
