#pragma once
#include "Projectile.h"

namespace TP3Prog
{

	/// <summary>
	/// Class of the SCATTERSHOT Projectile.
	/// </summary>
	/// <seealso cref="Projectile" />
	class Scatter :
		public Projectile
	{
	public:
		Scatter();
		~Scatter();
		void loadTexture() override;
	};

}

