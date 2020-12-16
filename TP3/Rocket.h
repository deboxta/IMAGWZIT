#pragma once
#include "Projectile.h"


namespace TP3Prog
{
	/// <summary>
	/// Class of the Rocket Launcher Projectile.
	/// As a matter of fact, this projectile isn't invulnerable anymore.
	/// Instead, it deals tons of damage.
	/// </summary>
	/// <seealso cref="Projectile" />
	class Rocket :
		public Projectile
	{
	public:
		Rocket();
		~Rocket();
		void loadTexture() override;
	};

}
