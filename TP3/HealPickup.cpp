#include "HealPickup.h"

namespace TP3Prog
{
	HealPickup::HealPickup(sf::Vector2f position, sf::Texture& pickupTexture)
		:Pickup(position, WeaponType::None, pickupTexture, 0)
	{
	}

	HealPickup::~HealPickup()
	{
	}
}