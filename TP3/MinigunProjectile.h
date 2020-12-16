#pragma once
#include "Projectile.h"

namespace TP3Prog
{
	class MinigunProjectile :
		public Projectile
	{
	public:
		MinigunProjectile();
		~MinigunProjectile();
		void loadTexture() override;
	};
}

