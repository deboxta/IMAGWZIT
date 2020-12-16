#pragma once
#include "Pickup.h"
#include "Entity.h"
#include "Subject.h"

namespace TP3Prog
{
	class ShieldPickup : public Pickup
	{
	public:
		ShieldPickup(sf::Vector2f position, sf::Texture& pickupTexture, Entity::DamageableType shieldType);
		~ShieldPickup();
		Entity::DamageableType getShieldType() const;
	private:
		Entity::DamageableType shieldType;
	};
}