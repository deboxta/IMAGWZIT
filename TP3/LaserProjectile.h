#pragma once
#include "Projectile.h"

namespace TP3Prog
{
	class LaserProjectile :
		public Projectile
	{
	public:
		LaserProjectile();
		~LaserProjectile();
		void visualAdjustments();

		void loadTexture() override;
		void update() override;

		void handleAnimation();
		void initialise(sf::Vector2f position, float angle) override;
	private:
		sf::IntRect* intRects;
		int frameCount = 0;
		static const int LASER_DAMAGE = 999;

		static const int ANIMRECT_SIZE_X = 233 * 20;
		static const int ANIMRECT_SIZE_Y = 25 * 20;
		static const int ANIM_SIZE = 4;
		static const int ANIM_REFRESH_RATE = 12;

	public:
		static const int LASER_PROJECTILE_TIMEOUT = ANIM_REFRESH_RATE * ANIM_SIZE;
	};
}

