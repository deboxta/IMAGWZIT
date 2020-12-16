#pragma once
#include "Pickup.h"
#include "Entity.h"

namespace TP3Prog
{
	class DronePickup :
		public Pickup
	{
	public:
		DronePickup(sf::Vector2f position, sf::Texture& pickupTexture);
		~DronePickup();
	};
}

