#pragma once
#include "Pickup.h"
#include "Entity.h"
#include "Subject.h"

namespace TP3Prog
{
	class HealPickup : public Pickup
	{
	public:
		HealPickup(sf::Vector2f position, sf::Texture& pickupTexture);
		~HealPickup();
	private:
	};
}
