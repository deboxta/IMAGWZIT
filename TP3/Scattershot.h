#pragma once
#include "Weapon.h"

namespace TP3Prog
{

	class Scattershot : public Weapon
	{
	public:
		Scattershot();
		~Scattershot();
		void shoot(Entity& entity) override;

	private:
		static const int SCATTERSHOT_SHOOT_INTERVAL = 15;
		static const int SCATTERSHOT_PROJECTILE_COUNT = 40;
		static const int SCATTERSHOT_REQUIRED_AMMO = 3;
	};

}
