#pragma once
#include "Projectile.h"

namespace TP3Prog
{
	class WatcherProjectile :
		public Projectile
	{
	public:
		WatcherProjectile();
		virtual ~WatcherProjectile();
		void loadTexture() override;
	};
}

