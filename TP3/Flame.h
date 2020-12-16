#pragma once
#include "Projectile.h"

namespace TP3Prog
{
	/// <summary>
	/// Class of the Flamethrower projectile
	/// </summary>
	/// <seealso cref="Projectile" />
	class Flame :
		public Projectile
	{
	public:
		Flame();
		virtual ~Flame();
		void loadTexture() override;
	};
}

