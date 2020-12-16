#include "Entity.h"
#include <complex>
#include <random>
#include "Subject.h"

namespace TP3Prog
{

	Entity::Entity(int speed) : Entity(speed, None, 0)
	{
	}

	Entity::Entity(int speed, DamageableType entityType, int health) : Damageable(health, entityType)
	{
		this->speed = speed;
	}

	void Entity::alignTo(sf::Vector2f position)
	{
		const sf::Vector2f delta = position - getPosition();
		double angle;


		if (delta.x >= 0)
		{
			angle = std::atan(delta.y / delta.x) * 180 / std::_Pi;
		}
		else
		{
			angle = std::atan(delta.y / delta.x) * 180 / std::_Pi + 180;
		}

		setRotation(angle);
	}

	void Entity::alignToDelta(sf::Vector2f delta)
	{
		double angle = 0;


		if (delta.x >= 0)
		{
			angle = std::atan(delta.y / delta.x) * 180 / std::_Pi;
		}
		else
		{
			angle = std::atan(delta.y / delta.x) * 180 / std::_Pi + 180;
		}

		setRotation(angle);
	}

	int Entity::getSpeed() const
	{
		return speed;
	}

	void Entity::activate()
	{
		isActive = true;
	}

	void Entity::deactivate()
	{
		isActive = false;
	}

	bool Entity::getIsActive() const
	{
		return isActive;
	}
}
