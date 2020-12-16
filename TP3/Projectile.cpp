#include "Projectile.h"
#include <random>
#include "WeaponType.h"

namespace TP3Prog
{
	sf::Texture* Projectile::projectileTextures;

	Projectile::Projectile() : Projectile(DEFAULT_PROJECTILE_INTERVAL, DEFAULT_PROJECTILE_SPEED, false, DEFAULT_PROJECTILE_DAMAGE)
	{
	}

	Projectile::Projectile(int projectileTimeout, float speed, bool isInvulnerable, int projectileDamage) : 
	Entity(speed), projectileDamage(projectileDamage)
	{
		this->isActive = false;
		this->projectileTimeout = projectileTimeout;
		this->defaultProjectileTimeout = projectileTimeout;
		this->isInvulnerable = isInvulnerable;
		this->angle = 0; //this value is originally changed in the initialise method.
	}


	Projectile::~Projectile()
	{
	}

	void Projectile::setProjectileTextures(sf::Texture* textures)
	{
		projectileTextures = textures;
	}

	void Projectile::unloadProjectileTextures()
	{
		delete[] projectileTextures;
	}

	void Projectile::loadTexture()
	{
		setTexture(projectileTextures[DEFAULT]);
	}

	void Projectile::initialise(sf::Vector2f position, float angle)
	{
		projectileTimeout = defaultProjectileTimeout;
		alignToDelta(sf::Vector2f(cos(angle * std::_Pi / 180), sin(angle * std::_Pi / 180)));
		setPosition(position);
		activate();
	}

	void Projectile::update()
	{
		if (!isActive)
			return;

		projectileTimeout--;

		if (projectileTimeout <= 0)
			deactivate();

		move(cos(getRotation() * std::_Pi / 180) * speed, sin(getRotation() * std::_Pi / 180) * speed);
	}

	bool Projectile::getIsInvulnerable() const
	{
		return isInvulnerable;
	}

	CollisionCircle Projectile::getCollider() const
	{
		return CollisionCircle(getLocalBounds().width, getPosition().x, getPosition().y);
	}

	int Projectile::getDamage() const
	{
		return projectileDamage;
	}
	void Projectile::notify(Subject * subject)
	{
	}
}
