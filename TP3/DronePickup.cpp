#include "DronePickup.h"


namespace TP3Prog
{
	DronePickup::DronePickup(sf::Vector2f position, sf::Texture& pickupTexture) : 
	Pickup(position, WeaponType::None, pickupTexture, 0)
	{
	}

	DronePickup::~DronePickup()
	{
	}
}
