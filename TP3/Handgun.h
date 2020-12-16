#pragma once
#include "Weapon.h"

namespace TP3Prog
{
	class Handgun :
		public Weapon
	{
	public:
		Handgun();
		~Handgun();

		static const int HANDGUN_PROJECTILE_COUNT = 40;

	private:
		static const int HANDGUN_SHOOT_INTERVAL = 10;
	};
}

