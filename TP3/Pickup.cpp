#include "Pickup.h"

namespace TP3Prog
{
	Pickup::Pickup(sf::Vector2f position, WeaponType pickupType, sf::Texture& pickupTexture, int ammoYield)
	{
		setPosition(position);
		this->weaponType = pickupType;
		this->ammoYield = ammoYield;
		setTexture(pickupTexture);
		activate();
	}


	Pickup::~Pickup()
	{
	}

	bool Pickup::getIsActive() const
	{
		return isActive;
	}

	WeaponType Pickup::getWeaponType() const
	{
		return weaponType;
	}

	int Pickup::getAmmoYield() const
	{
		return ammoYield;
	}

	void Pickup::activate()
	{
		isActive = true;
	}

	void Pickup::deactivate()
	{
		isActive = false;
	}
}
