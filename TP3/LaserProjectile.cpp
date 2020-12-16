#include "LaserProjectile.h"
#include "WeaponType.h"

namespace TP3Prog
{
	LaserProjectile::LaserProjectile() : Projectile(ANIM_SIZE * ANIM_REFRESH_RATE, 0, true, LASER_DAMAGE), 
	intRects(nullptr)
	{
	}


	LaserProjectile::~LaserProjectile()
	{
		delete[] intRects;
	}

	void LaserProjectile::visualAdjustments()
	{
		intRects = new sf::IntRect[ANIM_SIZE];

		for (int i = 0; i < ANIM_SIZE; ++i)
		{
			intRects[i].left = 0;
			intRects[i].width = ANIMRECT_SIZE_X;

			intRects[i].top = ANIMRECT_SIZE_Y * i;
			intRects[i].height = ANIMRECT_SIZE_Y;
		}

		setOrigin(0, ANIMRECT_SIZE_Y / 2);
	}

	void LaserProjectile::loadTexture()
	{
		setTexture(projectileTextures[LASER_GUN]);
		visualAdjustments();
	}

	void LaserProjectile::update()
	{
		Projectile::update();
		handleAnimation();
	}

	void LaserProjectile::handleAnimation()
	{
		setTextureRect(intRects[++frameCount / ANIM_REFRESH_RATE % ANIM_SIZE]);
	}

	void LaserProjectile::initialise(sf::Vector2f position, float angle)
	{
		Projectile::initialise(position, angle);
		frameCount = 0;
	}
}
