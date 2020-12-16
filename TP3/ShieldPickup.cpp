#include "ShieldPickup.h"

namespace TP3Prog
{
	ShieldPickup::ShieldPickup(sf::Vector2f position, sf::Texture& pickupTexture, Entity::DamageableType shieldType)
		:Pickup(position, WeaponType::None, pickupTexture, 0)
	{
		this->shieldType = shieldType;
	}

	ShieldPickup::~ShieldPickup()
	{

	}

	Entity::DamageableType ShieldPickup::getShieldType() const
	{
		return shieldType;
	}

}